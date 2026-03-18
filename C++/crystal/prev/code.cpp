#include "accessories.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>
#include <random>
#include <memory>
#include <mutex>
class CrystalClass
{
	int CountOfAtoms,CrystalSize,AtomCountOfDigits,CrystalCountOfDigits;	
	// int* crystal;
	struct cell
	{
		int AtomsCount=0;
		mutex mtx;
		char pad[64]={};  // To ensure no false sharing
		
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
	void AtomTaskCrystalLock(int AtomID,int LineNumber)
	{
		thread_local int position=0;
		thread_local bool choice;
		thread_local mt19937 rng(random_device{}());
		thread_local uniform_int_distribution<int> dist(0, 1);
		while(running)
		{			
			choice=dist(rng);	
			double dummy = 0.0;
			for (int k = 0; k < 1000; ++k)
				dummy += std::sin(k * 0.001) * std::cos(k * 0.002);
			if(choice==0 && position>0)
			{
				{
					lock_guard<mutex> lock(CrystalMutex);
					crystal[position]->AtomsCount--;					
					crystal[position-1]->AtomsCount++;
					// double dummy = 0.0;
					// for (int k = 0; k < 1000; ++k)
						// dummy += std::sin(k * 0.001) * std::cos(k * 0.002);
				}
				position--;
			}
			else
				if(choice==1 && position<CrystalSize-1)
				{
					{
						lock_guard<mutex> lock(CrystalMutex);
						crystal[position]->AtomsCount--;						
						crystal[position+1]->AtomsCount++;
						// double dummy = 0.0;
						// for (int k = 0; k < 1000; ++k)
							// dummy += std::sin(k * 0.001) * std::cos(k * 0.002);
					}
					position++;
				}			
			history[AtomID]=position;
			PositionChangesPerThread[AtomID]++;
			this_thread::sleep_for(chrono::microseconds(5));
		}
	}
	void AtomTaskCellLock(int AtomID,int LineNumber)
	{
		thread_local int position=0;
		thread_local bool choice;
		thread_local mt19937 rng(random_device{}());
		thread_local uniform_int_distribution<int> dist(0, 1);
		while(running)
		{
			choice=dist(rng);
			double dummy = 0.0;
			for (int k = 0; k < 1000; ++k)
				dummy += std::sin(k * 0.001) * std::cos(k * 0.002);
			if(choice==0 && position>0)
			{
				{
					// scoped_lock lock(crystal[position]->mtx,crystal[position-1]->mtx);
					lock(crystal[position]->mtx,crystal[position-1]->mtx);
					lock_guard<mutex> lock1(crystal[position]->mtx);
					lock_guard<mutex> lock2(crystal[position-1]->mtx);
					crystal[position]->AtomsCount--;					
					crystal[position-1]->AtomsCount++;
					// double dummy = 0.0;
					// for (int k = 0; k < 1000; ++k)
						// dummy += std::sin(k * 0.001) * std::cos(k * 0.002);
				}
				position--;
			}
			else
				if(choice==1 && position<CrystalSize-1)
				{
					{
						// scoped_lock lock(crystal[position]->mtx,crystal[position+1]->mtx);
						lock(crystal[position]->mtx,crystal[position+1]->mtx);
						lock_guard<mutex> lock1(crystal[position]->mtx);
						lock_guard<mutex> lock2(crystal[position+1]->mtx);
						crystal[position]->AtomsCount--;						
						crystal[position+1]->AtomsCount++;
						// double dummy = 0.0;
						// for (int k = 0; k < 1000; ++k)
							// dummy += std::sin(k * 0.001) * std::cos(k * 0.002);
					}
					position++;
				}
			history[AtomID]=position;
			PositionChangesPerThread[AtomID]++;
			// this_thread::sleep_for(chrono::microseconds(5));
		}
	}
	public: CrystalClass(int NewCrystalSize,int NewCountOfAtoms,int SimulationTime,int SnapshotsCount,bool CrystalLockMode):
	CrystalSize(NewCrystalSize),CountOfAtoms(NewCountOfAtoms)
	{		
		// crystal=(int*)calloc(CrystalSize,sizeof(int));
		// crystal.resize(CrystalSize);
		
		// crystal[0]->AtomsCount=CountOfAtoms;
		
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
		// for(i=0; i<CrystalSize; i++)
		// {
			// struct cell NewCell;
			// NewCell.AtomsCount=0;
			// crystal.push_back(NewCell);
		// }
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
		LoggerThread = thread([this,LoggingInterval]()
		{
			int i,CountOfHistoryRecords=0;
			long filepos,*AtomPosInFile=new long[CountOfAtoms];
			string line;
			ifstream ReadFile("snapshot.log", ios::binary);
			for(i=0; i<CountOfAtoms; i++)
			{
				AtomPosInFile[i]=ReadFile.tellg();
				getline(ReadFile,line);
			}
			ReadFile.close();
			fstream WriteFile("snapshot.log", ios::in | ios::out | ios::binary);
			while(running)
			{
				this_thread::sleep_for(chrono::seconds(LoggingInterval));
				lock_guard<mutex> lock(FileHistoryMutex);
				for(i=0; i<CountOfAtoms; i++)
				{
					filepos=AtomPosInFile[i]+AtomCountOfDigits+7+CountOfHistoryRecords*(CrystalCountOfDigits+1);
					WriteFile.seekp(filepos);
					WriteFile<<setw(CrystalCountOfDigits)<<history[i]<<"|";
				}
				filepos=AtomPosInFile[CountOfAtoms-1]+AtomCountOfDigits+8+CountOfHistoryRecords*(CrystalCountOfDigits+1);
				WriteFile.seekp(0, ios::end);
				WriteFile<<"Crystal condition "<<CountOfHistoryRecords+1<<":";
				for(i=0; i<CrystalSize; i++)
				{
					if(i*(AtomCountOfDigits+1)%(90-(90%(AtomCountOfDigits+1)))==0)
						WriteFile<<endl;
					WriteFile<<setw(AtomCountOfDigits)<<crystal[i]->AtomsCount<<"|";
				}
				WriteFile<<endl;
				CountOfHistoryRecords++;
			}
			WriteFile.close();
			delete[] AtomPosInFile;
		});		
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
		
		cout<<string(90,'-')<<"\n";
		// delete[] crystal;
	}
};
int main()
{
	InitFloatingPointAndRandomNumbers();
	int CrystalSize=10,CountOfAtoms=100,SimulationTime=20,SnapshotsCount=10;
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
	CrystalClass* CellLockMode=new CrystalClass(CrystalSize,CountOfAtoms,SimulationTime,SnapshotsCount,true);
	delete CellLockMode;
	return 0;
}