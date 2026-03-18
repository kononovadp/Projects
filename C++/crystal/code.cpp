#include "accessories.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>
#include <random>
#include <memory>
#include <mutex>
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
	vector<unique_ptr<thread>> AtomThreads;
	struct cell
	{
		atomic<int> AtomsCount{0};
		mutex mtx;
		char no_false_sharing[64]={};
	};
	vector<unique_ptr<cell>> crystal;
	mutex CrystalMutex,FileHistoryMutex;
	vector<mutex> CellMutexs;
	atomic<bool> running=true;
	void AtomTaskCrystalLock(int AtomID,int LineNumber)
	{
		double choice;
		mt19937 rng(random_device{}());
		uniform_real_distribution<> dist(MIN_RANDOM, MAX_RANDOM);
		while(running)
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
			else
				if(choice>THRESHOLD && AtomPositions[AtomID]<CrystalSize-1)
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
		double choice;
		mt19937 rng(random_device{}());
		uniform_real_distribution<> dist(MIN_RANDOM, MAX_RANDOM);
		while(running)
		{
			choice=dist(rng);
			if(choice<THRESHOLD && AtomPositions[AtomID]>0)
			{
				lock(crystal[AtomPositions[AtomID]]->mtx, crystal[AtomPositions[AtomID]-1]->mtx);
                lock_guard<mutex> lock1(crystal[AtomPositions[AtomID]]->mtx, adopt_lock);
                lock_guard<mutex> lock2(crystal[AtomPositions[AtomID]-1]->mtx, adopt_lock);
				volatile double dummy=0.0;
				for (int k=0; k<1000; k++)
					dummy+=sin(k*0.001)*cos(k*0.002);
				crystal[AtomPositions[AtomID]]->AtomsCount--;					
				crystal[AtomPositions[AtomID]-1]->AtomsCount++;
				AtomPositions[AtomID]--;
				CountsOfSteps[AtomID][0]++;
			}
			else
				if(choice>THRESHOLD && AtomPositions[AtomID]<CrystalSize-1)
				{
					lock(crystal[AtomPositions[AtomID]]->mtx, crystal[AtomPositions[AtomID]+1]->mtx);
					lock_guard<mutex> lock1(crystal[AtomPositions[AtomID]]->mtx, adopt_lock);
					lock_guard<mutex> lock2(crystal[AtomPositions[AtomID]+1]->mtx, adopt_lock);
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
		CountsOfSteps=(int**)calloc(CountOfAtoms,sizeof(int*));
		PositionChangesPerThread=(long long*)calloc(CountOfAtoms,sizeof(long long));
		AtomCountOfDigits=GetCountOfDigits(CountOfAtoms);
		CrystalCountOfDigits=GetCountOfDigits(CrystalSize-1);
		int i,j,LineNumber=CrystalSize/(90/(AtomCountOfDigits+1))+3;
		int LoggingInterval=SimulationTime/SnapshotsCount;
		ofstream file("snapshot.log", ios::trunc);
		for(i=0; i<CountOfAtoms; i++)
		{
			file<<"Atom "<<setw(AtomCountOfDigits)<<i<<": ";
			for(j=0; j<SnapshotsCount; j++)
				file<<setw(CrystalCountOfDigits+1)<<"|";
			file<<endl;
			CountsOfSteps[i]=(int*)calloc(3,sizeof(int));
		}
		file.close();
		crystal.reserve(CrystalSize);
		for(i=0; i<CrystalSize; i++)
			crystal.emplace_back(make_unique<cell>());
		crystal[0]->AtomsCount=CountOfAtoms;
		auto start=chrono::high_resolution_clock::now();
		thread** AtomThreads=new thread*[CountOfAtoms];		
		if(CrystalLockMode)		
			for(i=0; i<CountOfAtoms; i++,LineNumber++)
				AtomThreads[i]=new thread(&CrystalClass::AtomTaskCrystalLock,this,i,LineNumber);		
			else			
				for(i=0; i<CountOfAtoms; i++,LineNumber++)
					AtomThreads[i]=new thread(&CrystalClass::AtomTaskCellLock,this,i,LineNumber);
		thread LoggerThread = thread([this,LoggingInterval]()
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
					WriteFile<<setw(CrystalCountOfDigits)<<AtomPositions[i]<<"|";
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
		if(LoggerThread.joinable())
			LoggerThread.join();
		for(i=0; i<CountOfAtoms; i++)		
			if(AtomThreads[i]->joinable())
				AtomThreads[i]->join();		
		for(i=0; i<CountOfAtoms; i++)
			delete AtomThreads[i];		
		delete[] AtomThreads;
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<double> elapsed=end-start;
		cout<<"\nTRUE DURATION: "<<elapsed.count()<<" SECONDS\n";
	}
	~CrystalClass()
	{		
		int i,TrueCountOfAtoms=0,CountOfLeftSteps=0,CountOfRightSteps=0,CountOfStops=0;
		long long TotalPositionChangesPerThread=0;
		for(i=0; i<CrystalSize; i++)		
			TrueCountOfAtoms+=crystal[i]->AtomsCount;
		for(i=0; i<CountOfAtoms; i++)
		{
			TotalPositionChangesPerThread+=PositionChangesPerThread[i];
			CountOfLeftSteps+=CountsOfSteps[i][0];
			CountOfRightSteps+=CountsOfSteps[i][1];
			CountOfStops+=CountsOfSteps[i][2];
			free(CountsOfSteps[i]);
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
	CrystalClass* CrystalLockMode=new CrystalClass(CrystalSize,CountOfAtoms,SimulationTime,SnapshotsCount,true);
	delete CrystalLockMode;
	cout<<"CELL LOCK MODE...";
	CrystalClass* CellLockMode=new CrystalClass(CrystalSize,CountOfAtoms,SimulationTime,SnapshotsCount,false);
	delete CellLockMode;
	return 0;
}