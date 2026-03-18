#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>
#include <random>
#include <memory>
#include <mutex>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <numeric>

using namespace std;

// Utility functions (replacing accessories.h dependencies)
int GetCountOfDigits(int number) {
    int digits = 0;
    while (number > 0) {
        number /= 10;
        digits++;
    }
    return digits == 0 ? 1 : digits;
}

void InitFloatingPointAndRandomNumbers() {
    // Basic initialization if needed
}

class CrystalClass
{
    int CountOfAtoms, CrystalSize, AtomCountOfDigits, CrystalCountOfDigits;
    
    struct cell
    {
        int AtomsCount = 0;
        mutex mtx;
        char pad[64 - sizeof(int) - sizeof(mutex)] = {};
        
        cell() = default;
        cell(const cell&) = delete;
        cell& operator=(const cell&) = delete;
        cell(cell&&) = delete;
        cell& operator=(cell&&) = delete;
    };
    
    vector<unique_ptr<cell>> crystal;
    vector<long long> PositionChangesPerThread;
    thread LoggerThread;
    vector<thread> AtomThreads;
    vector<int> history;
    mutex CrystalMutex, FileHistoryMutex;
    atomic<bool> running = true;
    atomic<long long> totalOperations{0};
    atomic<long long> successfulMoves{0};
    atomic<long long> contentionEvents{0};

    void AtomTaskCrystalLock(int AtomID, int LineNumber)
    {
        thread_local int position = 0;
        thread_local mt19937 rng(random_device{}() + AtomID);
        thread_local uniform_int_distribution<int> dist(0, 1);
        
        while(running)
        {
            bool moveRight = dist(rng);
            int newPosition = position;
            bool canMove = false;
            
            if (moveRight && position < CrystalSize - 1) {
                newPosition = position + 1;
                canMove = true;
            } else if (!moveRight && position > 0) {
                newPosition = position - 1;
                canMove = true;
            }
            
            if (canMove) {
                // GLOBAL LOCK - entire crystal is locked
                auto startWait = chrono::high_resolution_clock::now();
                lock_guard<mutex> globalLock(CrystalMutex);
                auto endWait = chrono::high_resolution_clock::now();
                
                // Track contention (time spent waiting for lock)
                auto waitTime = chrono::duration_cast<chrono::microseconds>(endWait - startWait);
                if (waitTime.count() > 10) { // If we waited more than 10 microseconds
                    contentionEvents++;
                }
                
                // Simulate more significant computational work
                volatile double dummy = 0.0;
                for (int k = 0; k < 500; ++k) {
                    dummy += sin(k * 0.001) * cos(k * 0.002);
                }
                
                // Perform the move
                crystal[position]->AtomsCount--;
                crystal[newPosition]->AtomsCount++;
                position = newPosition;
                
                successfulMoves++;
            }
            
            totalOperations++;
            history[AtomID] = position;
            PositionChangesPerThread[AtomID]++;
            
            // Reduced sleep to increase contention
            this_thread::sleep_for(chrono::microseconds(1));
        }
    }

    void AtomTaskCellLock(int AtomID, int LineNumber)
    {
        thread_local int position = 0;
        thread_local mt19937 rng(random_device{}() + AtomID);
        thread_local uniform_int_distribution<int> dist(0, 1);
        
        while(running)
        {
            bool moveRight = dist(rng);
            int newPosition = position;
            bool canMove = false;
            
            if (moveRight && position < CrystalSize - 1) {
                newPosition = position + 1;
                canMove = true;
            } else if (!moveRight && position > 0) {
                newPosition = position - 1;
                canMove = true;
            }
            
            if (canMove) {
                // FINE-GRAINED LOCK - only lock the two cells involved
                auto startWait = chrono::high_resolution_clock::now();
                
                // Use std::lock to acquire both mutexes without deadlock
                // This handles the case where we might be locking the same mutex
                std::lock(crystal[position]->mtx, crystal[newPosition]->mtx);
                
                // Now adopt the locks into lock_guards for RAII
                lock_guard<mutex> lock1(crystal[position]->mtx, adopt_lock);
                lock_guard<mutex> lock2(crystal[newPosition]->mtx, adopt_lock);
                
                auto endWait = chrono::high_resolution_clock::now();
                
                // Track contention
                auto waitTime = chrono::duration_cast<chrono::microseconds>(endWait - startWait);
                if (waitTime.count() > 10) {
                    contentionEvents++;
                }
                
                // Simulate more significant computational work
                volatile double dummy = 0.0;
                for (int k = 0; k < 500; ++k) {
                    dummy += sin(k * 0.001) * cos(k * 0.002);
                }
                
                // Perform the move
                crystal[position]->AtomsCount--;
                crystal[newPosition]->AtomsCount++;
                position = newPosition;
                
                successfulMoves++;
            }
            
            totalOperations++;
            history[AtomID] = position;
            PositionChangesPerThread[AtomID]++;
            
            // Reduced sleep to increase contention
            this_thread::sleep_for(chrono::microseconds(1));
        }
    }

public:
    CrystalClass(int NewCrystalSize, int NewCountOfAtoms, int SimulationTime, int SnapshotsCount, bool CrystalLockMode):
        CrystalSize(NewCrystalSize), CountOfAtoms(NewCountOfAtoms)
    {
        history.resize(CountOfAtoms);
        AtomCountOfDigits = GetCountOfDigits(CountOfAtoms);
        CrystalCountOfDigits = GetCountOfDigits(CrystalSize - 1);
        PositionChangesPerThread.resize(CountOfAtoms);
        
        // Reset counters
        totalOperations = 0;
        successfulMoves = 0;
        contentionEvents = 0;
        
        crystal.reserve(CrystalSize);
        for (int i = 0; i < CrystalSize; ++i)
            crystal.emplace_back(make_unique<cell>());
        crystal[0]->AtomsCount = CountOfAtoms;
        
        auto start = chrono::high_resolution_clock::now();
        
        if(CrystalLockMode) {
            cout << " (Using Global Lock)\n";
            for(int i = 0; i < CountOfAtoms; i++)
                AtomThreads.emplace_back(&CrystalClass::AtomTaskCrystalLock, this, i, 0);
        } else {
            cout << " (Using Fine-Grained Lock)\n";
            for(int i = 0; i < CountOfAtoms; i++)
                AtomThreads.emplace_back(&CrystalClass::AtomTaskCellLock, this, i, 0);
        }
        
        this_thread::sleep_for(chrono::seconds(SimulationTime));
        running = false;
        
        for (auto& t : AtomThreads)
            if (t.joinable())
                t.join();
        
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        
        // Calculate performance metrics
        long long TotalPositionChanges = accumulate(PositionChangesPerThread.begin(), PositionChangesPerThread.end(), 0LL);
        double operationsPerSecond = totalOperations.load() / elapsed.count();
        double movesPerSecond = successfulMoves.load() / elapsed.count();
        double throughput = TotalPositionChanges / elapsed.count();
        
        cout << "Wall-clock duration: " << fixed << setprecision(3) << elapsed.count() << " s\n";
        cout << "Total operations: " << totalOperations.load() << "\n";
        cout << "Successful moves: " << successfulMoves.load() << "\n";
        cout << "Operations/sec: " << fixed << setprecision(0) << operationsPerSecond << "\n";
        cout << "Moves/sec: " << movesPerSecond << "\n";
        cout << "Position changes/sec: " << throughput << "\n";
        cout << "Contention events: " << contentionEvents.load() << "\n";
        cout << "Move success rate: " << fixed << setprecision(1) 
             << (100.0 * successfulMoves.load() / totalOperations.load()) << "%\n";
    }

    ~CrystalClass()
    {
        int RealCountOfAtoms = 0;
        for(int i = 0; i < CrystalSize; i++)
            RealCountOfAtoms += crystal[i]->AtomsCount;
        
        long long TotalPositionChangesPerThread = accumulate(PositionChangesPerThread.begin(), PositionChangesPerThread.end(), 0LL);
        double AveragePositionChangesPerThread = TotalPositionChangesPerThread / double(CountOfAtoms);
        
        cout << "TOTAL POSITION CHANGES: " << TotalPositionChangesPerThread << "\n";
        cout << "AVERAGE POSITION CHANGES: " << fixed << setprecision(2) << AveragePositionChangesPerThread << "\n";
        cout << "ATOMS CONSERVED: " << (RealCountOfAtoms == CountOfAtoms ? "YES" : "NO") 
             << " (" << RealCountOfAtoms << "/" << CountOfAtoms << ")\n";
        cout << string(90, '-') << "\n";
    }
};

int main()
{
    InitFloatingPointAndRandomNumbers();
    
    // Higher contention scenario for better comparison
    int CrystalSize = 10;      // Smaller crystal = more contention
    int CountOfAtoms = 100;    // More atoms = more contention
    int SimulationTime = 5;    // Shorter time for quick testing
    int SnapshotsCount = 10;
    
    cout << "Crystal Simulation Performance Comparison\n";
    cout << "========================================\n";
    cout << "Crystal size: " << CrystalSize << ", Atoms: " << CountOfAtoms 
         << ", Duration: " << SimulationTime << "s\n\n";
    
    cout << "Running CRYSTAL LOCK MODE";
    CrystalClass* CrystalLockMode = new CrystalClass(CrystalSize, CountOfAtoms, SimulationTime, SnapshotsCount, true);
    delete CrystalLockMode;
    
    cout << "\nRunning CELL LOCK MODE";
    CrystalClass* CellLockMode = new CrystalClass(CrystalSize, CountOfAtoms, SimulationTime, SnapshotsCount, false); // FIXED: false!
    delete CellLockMode;
    
    cout << "\nAnalysis:\n";
    cout << "- Fine-grained locking should show higher operations/sec\n";
    cout << "- Lower contention events indicate better parallelism\n";
    cout << "- The difference becomes more pronounced with more atoms and smaller crystals\n";
    
    return 0;
}