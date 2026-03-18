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
#include "accessories.h"
class CrystalClass
{
	int CountOfAtoms,CrystalSize,AtomCountOfDigits,CrystalCountOfDigits;	
	// int* crystal;
	struct cell
	{
		int AtomsCount=0;
		mutex mtx;
		char pad[64 - sizeof(int) - sizeof(mutex)] = {};
		cell() = default;
		cell(const cell&) = delete;
		cell& operator=(const cell&) = delete;
		cell(cell&&) = delete;
		cell& operator=(cell&&) = delete;
	};
	// vector<cell> crystal;
	vector<std::unique_ptr<cell>> crystal;
	vector<long long> PositionChangesPerThread;
	thread LoggerThread;
	vector<thread> AtomThreads;
	vector<int> history;
	mutex CrystalMutex,FileHistoryMutex;
	vector<mutex> CellMutexs;
	atomic<bool> running=true;
	atomic<long long> totalOperations{0};
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
                lock_guard<mutex> globalLock(CrystalMutex);
                volatile double dummy = 0.0;
                for (int k = 0; k < 500; ++k) {
                    dummy += sin(k * 0.001) * cos(k * 0.002);
                }
                crystal[position]->AtomsCount--;
                crystal[newPosition]->AtomsCount++;
                position = newPosition;
                
            }
            
            totalOperations++;
            history[AtomID] = position;
            PositionChangesPerThread[AtomID]++;
            
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
				std::lock(crystal[position]->mtx, crystal[newPosition]->mtx);
                lock_guard<mutex> lock1(crystal[position]->mtx, adopt_lock);
                lock_guard<mutex> lock2(crystal[newPosition]->mtx, adopt_lock);
                volatile double dummy = 0.0;
                for (int k = 0; k < 500; ++k) {
                    dummy += sin(k * 0.001) * cos(k * 0.002);
                }
                crystal[position]->AtomsCount--;
                crystal[newPosition]->AtomsCount++;
                position = newPosition;
            }
            totalOperations++;
            history[AtomID] = position;
            PositionChangesPerThread[AtomID]++;
            this_thread::sleep_for(chrono::microseconds(1));
        }
    }
	public: CrystalClass(int NewCrystalSize,int NewCountOfAtoms,int SimulationTime,int SnapshotsCount,bool CrystalLockMode):
	CrystalSize(NewCrystalSize),CountOfAtoms(NewCountOfAtoms)
	{
		history.resize(CountOfAtoms);
		AtomCountOfDigits=GetCountOfDigits(CountOfAtoms);
		CrystalCountOfDigits=GetCountOfDigits(CrystalSize-1);
		PositionChangesPerThread.resize(CountOfAtoms);
		// PositionChangesPerThread=0;
		int i,j,LineNumber=CrystalSize/(90/(AtomCountOfDigits+1))+3;
		int LoggingInterval=SimulationTime/SnapshotsCount;
		ofstream file("snapshot.log", ios::trunc);
		for(i=0; i<CountOfAtoms; i++)
		{
			file<<"Atom "<<setw(AtomCountOfDigits)<<i<<": ";
			for(j=0; j<SnapshotsCount; j++)
				file<<setw(CrystalCountOfDigits+1)<<"|";
			file<<endl;
		}
		file.close();
		crystal.reserve(CrystalSize);
		for (i = 0; i < CrystalSize; ++i)
			crystal.emplace_back(std::make_unique<cell>());
		crystal[0]->AtomsCount=CountOfAtoms;
		auto start = chrono::high_resolution_clock::now();
		if(CrystalLockMode)
			for(i=0; i<CountOfAtoms; i++,LineNumber++)
				AtomThreads.emplace_back(&CrystalClass::AtomTaskCrystalLock,this,i,LineNumber);
		else
			for(i=0; i<CountOfAtoms; i++,LineNumber++)
				AtomThreads.emplace_back(&CrystalClass::AtomTaskCellLock,this,i,LineNumber);
		this_thread::sleep_for(chrono::seconds(SimulationTime));
		running = false;
		if (LoggerThread.joinable())
			LoggerThread.join();
		for (auto& t : AtomThreads)
			if (t.joinable())
				t.join();
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		cout << "\nWall-clock duration (s): " << elapsed.count() << std::endl;
	}
	~CrystalClass()
	{
		
		
		int i,RealCountOfAtoms=0;
		// long long TotalPositionChangesPerThread=std::accumulate(PositionChangesPerThread.begin(), PositionChangesPerThread.end(), 0);
		long long TotalPositionChangesPerThread=0;
		for(i=0; i<CrystalSize; i++)		
			RealCountOfAtoms+=crystal[i]->AtomsCount;
		for(i=0; i<CountOfAtoms; i++)
			TotalPositionChangesPerThread+=PositionChangesPerThread[i];		
		double AveragePositionChangesPerThread=TotalPositionChangesPerThread/double(CountOfAtoms);
		cout<<"\nTOTAL COUNT OF ATOM POSITION CHANGES:   "<<TotalPositionChangesPerThread<<";\n"
			<<"AVERAGE COUNT OF ATOM POSITION CHANGES: "<<AveragePositionChangesPerThread<<";\n";
		// for(i=0; i<CountOfAtoms; i++)		
			// cout<<"ATOM "<<setw(AtomCountOfDigits)<<i<<": "<<PositionChangesPerThread[i]<<endl;	
		cout<<"REAL COUNT OF ATOMS: "<<RealCountOfAtoms<<";\n";
		cout<<"totalOperations: "<<totalOperations<<"\n";
		cout<<string(90,'-')<<"\n";
		// delete[] crystal;
	}
};
int main()
{
	InitFloatingPointAndRandomNumbers();
	int CrystalSize=10,CountOfAtoms=100,SimulationTime=10,SnapshotsCount=10;
	int CrystalSizeCountOfDigits=GetCountOfDigits(CrystalSize);
	int CountOfAtomsCountOfDigits=GetCountOfDigits(CountOfAtoms);
	int SimulationTimeCountOfDigits=GetCountOfDigits(SimulationTime);
	int SnapshotsCountCountOfDigits=GetCountOfDigits(SnapshotsCount);	
	CrystalSizeCountOfDigits=(CrystalSizeCountOfDigits>SimulationTimeCountOfDigits)?CrystalSizeCountOfDigits:SimulationTimeCountOfDigits;
	SimulationTimeCountOfDigits=(SimulationTimeCountOfDigits>CrystalSizeCountOfDigits)?SimulationTimeCountOfDigits:CrystalSizeCountOfDigits;
	CountOfAtomsCountOfDigits=(CountOfAtomsCountOfDigits>SnapshotsCountCountOfDigits)?CountOfAtomsCountOfDigits:SnapshotsCountCountOfDigits;
	SnapshotsCountCountOfDigits=(SnapshotsCountCountOfDigits>CountOfAtomsCountOfDigits)?SnapshotsCountCountOfDigits:CountOfAtomsCountOfDigits;
	cout<<"CRYSTAL SIZE: "<<setw(CrystalSizeCountOfDigits+13)<<CrystalSize<<"; "
		<<"COUNT OF ATOMS: "<<setw(CountOfAtomsCountOfDigits+1)<<CountOfAtoms<<";\n"
		<<"SIMULATION TIME (SECONDS): "<<setw(SimulationTimeCountOfDigits)<<SimulationTime<<"; "
		<<"SNAPSHOTS COUNT: "<<setw(SnapshotsCountCountOfDigits)<<SnapshotsCount<<"; "
		<<"CRYSTAL LOCK MODE...";
	CrystalClass* CrystalLockMode=new CrystalClass(CrystalSize,CountOfAtoms,SimulationTime,SnapshotsCount,true);
	delete CrystalLockMode;
	cout<<"CELL LOCK MODE...";
	CrystalClass* CellLockMode=new CrystalClass(CrystalSize,CountOfAtoms,SimulationTime,SnapshotsCount,false);
	delete CellLockMode;
	return 0;
}