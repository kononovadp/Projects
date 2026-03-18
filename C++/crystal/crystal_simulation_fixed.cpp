#include "accessories.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>
#include <random>
#include <memory>
#include <mutex>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

double MIN_RANDOM=5;
double MAX_RANDOM=10;
double SCALE=2;
double THRESHOLD=MIN_RANDOM+(MAX_RANDOM-MIN_RANDOM)/SCALE;
const auto ATOM_TASK_WAIT_DURATION=chrono::milliseconds(100);

class CrystalClass
{
	int CountOfAtoms,CrystalSize,AtomCountOfDigits,CrystalCountOfDigits;
	int *AtomPositions,**CountsOfSteps;
	long long* PositionChangesPerThread;
	vector<unique_ptr<thread>> AtomThreads; // Changed to unique_ptr for better memory management
	struct cell
	{
		atomic<int> AtomsCount{0}; // Made atomic to prevent race conditions
		mutex mtx;
		char no_false_sharing[64]={};
	};
	vector<unique_ptr<cell>> crystal;
	mutex CrystalMutex,FileHistoryMutex;
	atomic<bool> running{true}; // Explicit initialization
	
	void AtomTaskCrystalLock(int AtomID,int LineNumber)
	{
		// Remove thread_local for better GCC compatibility
		mt19937 rng(random_device{}() + AtomID); // Add AtomID for unique seeding
		uniform_real_distribution<> dist(MIN_RANDOM, MAX_RANDOM);
		double choice;
		
		while(running.load()) // Explicit load for atomic
		{			
			choice=dist(rng);
			if(choice<THRESHOLD && AtomPositions[AtomID]>0)
			{
				lock_guard<mutex> lock(CrystalMutex);
				volatile double dummy=0.0;
				for (int k=0; k<1000; k++)
					dummy+=sin(k*0.001)*cos(k*0.002);
				crystal[AtomPositions[AtomID]]->AtomsCount--;					
				crystal[AtomPositions[AtomID]-1]->AtomsCount++;				
				AtomPositions[AtomID]--;
				CountsOfSteps[AtomID][0]++;
			}
			else if(choice>THRESHOLD && AtomPositions[AtomID]<CrystalSize-1)
			{
				lock_guard<mutex> lock(CrystalMutex);
				volatile double dummy=0.0;
				for (int k=0; k<1000; k++)
					dummy+=sin(k*0.001)*cos(k*0.002);
				crystal[AtomPositions[AtomID]]->AtomsCount--;						
				crystal[AtomPositions[AtomID]+1]->AtomsCount++;
				AtomPositions[AtomID]++;
				CountsOfSteps[AtomID][1]++;
			}
			else
				CountsOfSteps[AtomID][2]++;
			PositionChangesPerThread[AtomID]++;
			this_thread::sleep_for(chrono::microseconds(1));
		}
	}
	
	void AtomTaskCellLock(int AtomID,int LineNumber)
	{
		mt19937 rng(random_device{}() + AtomID); // Add AtomID for unique seeding
		uniform_real_distribution<> dist(MIN_RANDOM, MAX_RANDOM);
		double choice;
		
		while(running.load()) // Explicit load for atomic
		{
			choice=dist(rng);
			if(choice<THRESHOLD && AtomPositions[AtomID]>0)
			{
				// Fixed potential deadlock with consistent lock ordering
				int pos1 = AtomPositions[AtomID];
				int pos2 = pos1 - 1;
				if (pos1 > pos2) {
					lock(crystal[pos2]->mtx, crystal[pos1]->mtx);
				} else {
					lock(crystal[pos1]->mtx, crystal[pos2]->mtx);
				}
                lock_guard<mutex> lock1(crystal[pos1]->mtx, adopt_lock);
                lock_guard<mutex> lock2(crystal[pos2]->mtx, adopt_lock);
				
				volatile double dummy=0.0;
				for (int k=0; k<1000; k++)
					dummy+=sin(k*0.001)*cos(k*0.002);
				crystal[AtomPositions[AtomID]]->AtomsCount--;					
				crystal[AtomPositions[AtomID]-1]->AtomsCount++;
				AtomPositions[AtomID]--;
				CountsOfSteps[AtomID][0]++;
			}
			else if(choice>THRESHOLD && AtomPositions[AtomID]<CrystalSize-1)
			{
				// Fixed potential deadlock with consistent lock ordering
				int pos1 = AtomPositions[AtomID];
				int pos2 = pos1 + 1;
				if (pos1 > pos2) {
					lock(crystal[pos2]->mtx, crystal[pos1]->mtx);
				} else {
					lock(crystal[pos1]->mtx, crystal[pos2]->mtx);
				}
				lock_guard<mutex> lock1(crystal[pos1]->mtx, adopt_lock);
				lock_guard<mutex> lock2(crystal[pos2]->mtx, adopt_lock);
				
				volatile double dummy=0.0;
				for (int k=0; k<1000; k++)
					dummy+=sin(k*0.001)*cos(k*0.002);
				crystal[AtomPositions[AtomID]]->AtomsCount--;						
				crystal[AtomPositions[AtomID]+1]->AtomsCount++;
				AtomPositions[AtomID]++;
				CountsOfSteps[AtomID][1]++;
			}
			else
				CountsOfSteps[AtomID][2]++;
			PositionChangesPerThread[AtomID]++;
			this_thread::sleep_for(chrono::microseconds(1));
		}
	}
	
	public: CrystalClass(int NewCrystalSize,int NewCountOfAtoms,int SimulationTime,int SnapshotsCount,bool CrystalLockMode):
	CrystalSize(NewCrystalSize),CountOfAtoms(NewCountOfAtoms)
	{
		AtomPositions=(int*)calloc(CountOfAtoms,sizeof(int));
		CountsOfSteps=(int**)calloc(CountOfAtoms,sizeof(int*)); // Fixed: sizeof(int*) not sizeof(int)
		PositionChangesPerThread=(long long*)calloc(CountOfAtoms,sizeof(long long));
		AtomCountOfDigits=GetCountOfDigits(CountOfAtoms);
		CrystalCountOfDigits=GetCountOfDigits(CrystalSize-1);
		int i,j,LineNumber=CrystalSize/(90/(AtomCountOfDigits+1))+3;
		int LoggingInterval=SimulationTime/SnapshotsCount;
		
		// Initialize CountsOfSteps properly
		for(i=0; i<CountOfAtoms; i++)
		{
			CountsOfSteps[i]=(int*)calloc(3,sizeof(int));
		}
		
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
		for(i=0; i<CrystalSize; i++)
			crystal.emplace_back(make_unique<cell>());
		crystal[0]->AtomsCount=CountOfAtoms;
		
		auto start=chrono::high_resolution_clock::now();
		
		// Use vector for better memory management
		AtomThreads.reserve(CountOfAtoms);
		
		if(CrystalLockMode)		
			for(i=0; i<CountOfAtoms; i++,LineNumber++)
				AtomThreads.emplace_back(make_unique<thread>(&CrystalClass::AtomTaskCrystalLock,this,i,LineNumber));
		else			
			for(i=0; i<CountOfAtoms; i++,LineNumber++)
				AtomThreads.emplace_back(make_unique<thread>(&CrystalClass::AtomTaskCellLock,this,i,LineNumber));
		
		thread LoggerThread = thread([this,LoggingInterval]()
		{
			int i,CountOfHistoryRecords=0;
			long filepos;
			unique_ptr<long[]> AtomPosInFile(new long[CountOfAtoms]); // Use smart pointer
			string line;
			ifstream ReadFile("snapshot.log", ios::binary);
			for(i=0; i<CountOfAtoms; i++)
			{
				AtomPosInFile[i]=ReadFile.tellg();
				getline(ReadFile,line);
			}
			ReadFile.close();
			fstream WriteFile("snapshot.log", ios::in | ios::out | ios::binary);
			while(running.load()) // Explicit load for atomic
			{
				this_thread::sleep_for(chrono::seconds(LoggingInterval));
				lock_guard<mutex> lock(FileHistoryMutex);
				for(i=0; i<CountOfAtoms; i++)
				{
					filepos=AtomPosInFile[i]+AtomCountOfDigits+7+CountOfHistoryRecords*(CrystalCountOfDigits+1);
					WriteFile.seekp(filepos);
					WriteFile<<setw(CrystalCountOfDigits)<<AtomPositions[i]<<"|";
				}
				filepos=AtomPosInFile[CountOfAtoms-1]+AtomCountOfDigits+8+CountOfHistoryRecords*(CrystalCountOfDigits+1);
				WriteFile.seekp(0, ios::end);
				WriteFile<<"Crystal condition "<<CountOfHistoryRecords+1<<":";
				for(i=0; i<CrystalSize; i++)
				{
					if(i*(AtomCountOfDigits+1)%(90-(90%(AtomCountOfDigits+1)))==0)
						WriteFile<<endl;
					WriteFile<<setw(AtomCountOfDigits)<<crystal[i]->AtomsCount.load()<<"|"; // Explicit load for atomic
				}
				WriteFile<<endl;
				CountOfHistoryRecords++;
			}
			WriteFile.close();
		});
		
		this_thread::sleep_for(chrono::seconds(SimulationTime));
		running.store(false); // Explicit store for atomic
		
		if(LoggerThread.joinable())
			LoggerThread.join();
		
		// Join all atom threads
		for(i=0; i<CountOfAtoms; i++)
		{
			if(AtomThreads[i]->joinable())
				AtomThreads[i]->join();
		}
		
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed = end - start;
		cout<<"\nREAL DURATION: "<<elapsed.count()<<" SECONDS\n";
	}
	
	~CrystalClass()
	{		
		int i,TrueCountOfAtoms=0,CountOfLeftSteps=0,CountOfRightSteps=0,CountOfStops=0;
		long long TotalPositionChangesPerThread=0;
		for(i=0; i<CrystalSize; i++)		
			TrueCountOfAtoms+=crystal[i]->AtomsCount.load(); // Explicit load for atomic
		for(i=0; i<CountOfAtoms; i++)
		{
			TotalPositionChangesPerThread+=PositionChangesPerThread[i];
			CountOfLeftSteps+=CountsOfSteps[i][0];
			CountOfRightSteps+=CountsOfSteps[i][1];
			CountOfStops+=CountsOfSteps[i][2];
			free(CountsOfSteps[i]); // Use free() for calloc'd memory
		}
		free(AtomPositions);
		free(CountsOfSteps);
		free(PositionChangesPerThread);
		
		double AveragePositionChangesPerThread=TotalPositionChangesPerThread/double(CountOfAtoms);
		cout<<"TOTAL COUNT OF ATOM POSITION CHANGES:   "<<TotalPositionChangesPerThread<<";\n"
			<<"AVERAGE COUNT OF ATOM POSITION CHANGES: "<<AveragePositionChangesPerThread<<";\n";
		cout<<"TRUE COUNT OF ATOMS                     : "<<TrueCountOfAtoms<<endl;
		cout<<"COUNT OF STEPS TO THE LEFT OF ALL ATOMS : "<<CountOfLeftSteps<<endl;
		cout<<"COUNT OF STEPS TO THE RIGHT OF ALL ATOMS: "<<CountOfRightSteps<<endl;
		cout<<"COUNT OF MISSING STEPS OF ALL ATOMS     : "<<CountOfStops<<endl;
		cout<<string(90,'-')<<"\n";
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
	cout<<"MIN_RANDOM: "<<setprecision(3)<<MIN_RANDOM<<"; ";
	cout<<"MAX_RANDOM: "<<setprecision(3)<<MAX_RANDOM<<"; ";
	cout<<"SCALE: "<<setprecision(3)<<SCALE<<"; ";
	cout<<"THRESHOLD: "<<setprecision(3)<<THRESHOLD<<";\n";
	cout<<"CRYSTAL SIZE: "<<setw(CrystalSizeCountOfDigits+13)<<CrystalSize<<"; "
		<<"COUNT OF ATOMS: "<<setw(CountOfAtomsCountOfDigits+1)<<CountOfAtoms<<";\n"
		<<"SIMULATION TIME (SECONDS): "<<setw(SimulationTimeCountOfDigits)<<SimulationTime<<"; "
		<<"SNAPSHOTS COUNT: "<<setw(SnapshotsCountCountOfDigits)<<SnapshotsCount<<"; "
		<<"CRYSTAL LOCK MODE...";
	{
		CrystalClass CrystalLockMode(CrystalSize,CountOfAtoms,SimulationTime,SnapshotsCount,true);
	} // Automatic cleanup with RAII
	cout<<"CELL LOCK MODE...";
	{
		CrystalClass CellLockMode(CrystalSize,CountOfAtoms,SimulationTime,SnapshotsCount,false);
	} // Automatic cleanup with RAII
	return 0;
}