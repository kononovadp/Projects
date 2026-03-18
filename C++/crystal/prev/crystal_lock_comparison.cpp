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

using namespace std;

class CrystalSimulation {
private:
    struct Cell {
        int atomCount = 0;
        mutex mtx;
        // Padding to prevent false sharing
        char pad[64 - sizeof(int) - sizeof(mutex)] = {};
        
        Cell() = default;
        Cell(const Cell&) = delete;
        Cell& operator=(const Cell&) = delete;
        Cell(Cell&&) = delete;
        Cell& operator=(Cell&&) = delete;
    };

    int crystalSize;
    int totalAtoms;
    vector<unique_ptr<Cell>> crystal;
    vector<thread> atomThreads;
    vector<atomic<long long>> positionChanges;
    atomic<bool> running{true};
    
    // Global lock for whole-array locking strategy
    mutex globalCrystalMutex;
    
    // Statistics
    chrono::high_resolution_clock::time_point startTime;
    atomic<long long> totalOperations{0};
    atomic<long long> successfulMoves{0};
    atomic<long long> blockedMoves{0};

public:
    CrystalSimulation(int size, int atoms) 
        : crystalSize(size), totalAtoms(atoms) {
        crystal.reserve(crystalSize);
        for (int i = 0; i < crystalSize; ++i) {
            crystal.emplace_back(make_unique<Cell>());
        }
        crystal[0]->atomCount = totalAtoms;
        positionChanges.resize(totalAtoms);
    }

    // Strategy 1: Global lock - locks entire crystal for each move
    void atomTaskGlobalLock(int atomId) {
        thread_local int position = 0;
        thread_local mt19937 rng(random_device{}() + atomId);
        thread_local uniform_int_distribution<int> dist(0, 1);
        
        while (running) {
            bool moveRight = dist(rng);
            int newPosition = position;
            bool canMove = false;
            
            // Determine desired move
            if (moveRight && position < crystalSize - 1) {
                newPosition = position + 1;
                canMove = true;
            } else if (!moveRight && position > 0) {
                newPosition = position - 1;
                canMove = true;
            }
            
            if (canMove) {
                // GLOBAL LOCK - entire crystal is locked
                lock_guard<mutex> globalLock(globalCrystalMutex);
                
                // Simulate some computational work
                volatile double dummy = 0.0;
                for (int k = 0; k < 100; ++k) {
                    dummy += sin(k * 0.001) * cos(k * 0.002);
                }
                
                // Perform the move
                crystal[position]->atomCount--;
                crystal[newPosition]->atomCount++;
                position = newPosition;
                
                successfulMoves++;
            } else {
                blockedMoves++;
            }
            
            positionChanges[atomId]++;
            totalOperations++;
            
            // Small delay to prevent busy waiting
            this_thread::sleep_for(chrono::microseconds(1));
        }
    }

    // Strategy 2: Fine-grained locks - only locks required cells
    void atomTaskFineLock(int atomId) {
        thread_local int position = 0;
        thread_local mt19937 rng(random_device{}() + atomId);
        thread_local uniform_int_distribution<int> dist(0, 1);
        
        while (running) {
            bool moveRight = dist(rng);
            int newPosition = position;
            bool canMove = false;
            
            // Determine desired move
            if (moveRight && position < crystalSize - 1) {
                newPosition = position + 1;
                canMove = true;
            } else if (!moveRight && position > 0) {
                newPosition = position - 1;
                canMove = true;
            }
            
            if (canMove) {
                // FINE-GRAINED LOCK - only lock the two cells involved
                // Always lock in order to prevent deadlocks
                mutex& firstMutex = crystal[min(position, newPosition)]->mtx;
                mutex& secondMutex = crystal[max(position, newPosition)]->mtx;
                
                lock_guard<mutex> lock1(firstMutex);
                lock_guard<mutex> lock2(secondMutex);
                
                // Simulate some computational work
                volatile double dummy = 0.0;
                for (int k = 0; k < 100; ++k) {
                    dummy += sin(k * 0.001) * cos(k * 0.002);
                }
                
                // Perform the move
                crystal[position]->atomCount--;
                crystal[newPosition]->atomCount++;
                position = newPosition;
                
                successfulMoves++;
            } else {
                blockedMoves++;
            }
            
            positionChanges[atomId]++;
            totalOperations++;
            
            // Small delay to prevent busy waiting
            this_thread::sleep_for(chrono::microseconds(1));
        }
    }

    void runSimulation(bool useGlobalLock, int durationSeconds) {
        cout << "\n" << string(60, '=') << "\n";
        cout << "Running " << (useGlobalLock ? "GLOBAL LOCK" : "FINE-GRAINED LOCK") 
             << " simulation for " << durationSeconds << " seconds\n";
        cout << "Crystal size: " << crystalSize << ", Atoms: " << totalAtoms << "\n";
        cout << string(60, '=') << "\n";

        // Reset statistics
        totalOperations = 0;
        successfulMoves = 0;
        blockedMoves = 0;
        for (auto& changes : positionChanges) {
            changes = 0;
        }

        startTime = chrono::high_resolution_clock::now();
        
        // Start atom threads
        atomThreads.clear();
        atomThreads.reserve(totalAtoms);
        
        if (useGlobalLock) {
            for (int i = 0; i < totalAtoms; ++i) {
                atomThreads.emplace_back(&CrystalSimulation::atomTaskGlobalLock, this, i);
            }
        } else {
            for (int i = 0; i < totalAtoms; ++i) {
                atomThreads.emplace_back(&CrystalSimulation::atomTaskFineLock, this, i);
            }
        }

        // Run simulation
        this_thread::sleep_for(chrono::seconds(durationSeconds));
        
        // Stop simulation
        running = false;
        for (auto& thread : atomThreads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        
        auto endTime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        
        // Calculate statistics
        long long totalChanges = 0;
        for (const auto& changes : positionChanges) {
            totalChanges += changes;
        }
        
        double operationsPerSecond = totalOperations.load() / (duration.count() / 1000.0);
        double movesPerSecond = successfulMoves.load() / (duration.count() / 1000.0);
        double throughput = totalChanges / (duration.count() / 1000.0);
        
        // Verify atom conservation
        int totalAtomsInCrystal = 0;
        for (const auto& cell : crystal) {
            totalAtomsInCrystal += cell->atomCount;
        }
        
        // Print results
        cout << "\nRESULTS:\n";
        cout << "Duration: " << duration.count() << " ms\n";
        cout << "Total operations: " << totalOperations.load() << "\n";
        cout << "Successful moves: " << successfulMoves.load() << "\n";
        cout << "Blocked moves: " << blockedMoves.load() << "\n";
        cout << "Total position changes: " << totalChanges << "\n";
        cout << "Operations per second: " << fixed << setprecision(2) << operationsPerSecond << "\n";
        cout << "Successful moves per second: " << movesPerSecond << "\n";
        cout << "Position changes per second: " << throughput << "\n";
        cout << "Move success rate: " << (100.0 * successfulMoves.load() / totalOperations.load()) << "%\n";
        cout << "Atoms conserved: " << (totalAtomsInCrystal == totalAtoms ? "YES" : "NO") 
             << " (" << totalAtomsInCrystal << "/" << totalAtoms << ")\n";
        
        // Reset for next run
        running = true;
        // Reset atom positions
        for (auto& cell : crystal) {
            cell->atomCount = 0;
        }
        crystal[0]->atomCount = totalAtoms;
    }

    void printCrystalState() {
        cout << "\nCrystal state: [";
        for (int i = 0; i < crystalSize; ++i) {
            cout << crystal[i]->atomCount;
            if (i < crystalSize - 1) cout << ", ";
        }
        cout << "]\n";
    }
};

int main() {
    cout << "Crystal Simulation: Comparing Lock Strategies\n";
    cout << "============================================\n";
    
    // Simulation parameters
    const int CRYSTAL_SIZE = 20;
    const int ATOM_COUNT = 50;
    const int SIMULATION_TIME = 10; // seconds
    
    CrystalSimulation sim(CRYSTAL_SIZE, ATOM_COUNT);
    
    cout << "\nThis simulation demonstrates the performance difference between:\n";
    cout << "1. GLOBAL LOCK: One mutex protects the entire crystal\n";
    cout << "2. FINE-GRAINED LOCK: Each cell has its own mutex\n";
    cout << "\nWith " << ATOM_COUNT << " atoms moving in a crystal of " 
         << CRYSTAL_SIZE << " cells.\n";
    
    // Run global lock simulation
    sim.runSimulation(true, SIMULATION_TIME);
    
    // Small delay between simulations
    this_thread::sleep_for(chrono::seconds(1));
    
    // Run fine-grained lock simulation
    sim.runSimulation(false, SIMULATION_TIME);
    
    cout << "\n" << string(60, '=') << "\n";
    cout << "ANALYSIS:\n";
    cout << "The fine-grained locking strategy should show significantly\n";
    cout << "higher throughput because:\n";
    cout << "1. Multiple atoms can move simultaneously if they're in different regions\n";
    cout << "2. Only adjacent cells are locked during a move operation\n";
    cout << "3. Contention is reduced to local cell pairs\n";
    cout << "\nThe global lock forces all atom movements to be sequential,\n";
    cout << "creating a bottleneck even when movements could be independent.\n";
    cout << string(60, '=') << "\n";
    
    return 0;
}