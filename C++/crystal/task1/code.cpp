#include "accessories.h"
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>
#include <mutex>
#include <random>
HANDLE console;
COORD ScreenCoordinates;
double MIN_RANDOM=5;
double MAX_RANDOM=10;
double SCALE=4;
double THRESHOLD=MIN_RANDOM+(MAX_RANDOM-MIN_RANDOM)/SCALE;
const auto ATOM_TASK_WAIT_DURATION=chrono::milliseconds(100);
class CrystalClass
{
	int CountOfAtoms,AtomCountOfDigits,CrystalCountOfDigits;	
	int CrystalSize,*crystal,*AtomPositions,**CountsOfSteps;
	thread** AtomThreads;
	mutex mtx,fileMutex,historyMutex;
	atomic<bool> running=true;
	void AtomTask(int AtomID,int LineNumber)
	{
		thread_local double choice;
		thread_local mt19937 rng(random_device{}());
		thread_local uniform_real_distribution<> dist(MIN_RANDOM, MAX_RANDOM);
		while(running)
		{			
			{
				lock_guard<mutex> lock(mtx);
				choice=dist(rng);
				if(choice<THRESHOLD && AtomPositions[AtomID]>0)
				{
					crystal[AtomPositions[AtomID]]--;
					AtomPositions[AtomID]--;
					crystal[AtomPositions[AtomID]]++;
					CountsOfSteps[AtomID][0]++;
				}
				else
					if(choice>THRESHOLD && AtomPositions[AtomID]<CrystalSize-1)
					{
						crystal[AtomPositions[AtomID]]--;
						AtomPositions[AtomID]++;
						crystal[AtomPositions[AtomID]]++;
						CountsOfSteps[AtomID][1]++;
					}
					else
						CountsOfSteps[AtomID][2]++;
				ScreenCoordinates.X=0;
				ScreenCoordinates.Y=LineNumber;
				SetConsoleCursorPosition(console,ScreenCoordinates);
				cout<<string(90,' ')<<"\r";
				SetConsoleCursorPosition(console,ScreenCoordinates);
				cout<<"Atom "<<setw(AtomCountOfDigits)<<AtomID<<": position: "<<AtomPositions[AtomID];
				display();
			}
			this_thread::sleep_for(ATOM_TASK_WAIT_DURATION);
		}
	}
	public: CrystalClass(int NewCrystalSize,int NewCountOfAtoms,int SimulationTime,int SnapshotsCount):
	CrystalSize(NewCrystalSize),CountOfAtoms(NewCountOfAtoms)
	{		
		crystal=(int*)calloc(CrystalSize,sizeof(int));
		AtomPositions=(int*)calloc(CountOfAtoms,sizeof(int));
		CountsOfSteps=(int**)calloc(CountOfAtoms,sizeof(int*));
		crystal[0]=CountOfAtoms;
		AtomCountOfDigits=GetCountOfDigits(CountOfAtoms);
		CrystalCountOfDigits=GetCountOfDigits(CrystalSize-1);
		ScreenCoordinates.X=0;		
		int i,j,LineNumber=CrystalSize/(90/(AtomCountOfDigits+1))+4;
		int LoggingInterval=SimulationTime/SnapshotsCount;
		for(i=0; i<CountOfAtoms; i++)
			CountsOfSteps[i]=(int*)calloc(3,sizeof(int));
		display();
		ofstream file("snapshot.log", ios::trunc);
		for(i=0; i<CountOfAtoms; i++)
		{
			file<<"Atom "<<setw(AtomCountOfDigits)<<i<<": ";
			for(j=0; j<SnapshotsCount; j++)
				file<<setw(CrystalCountOfDigits+1)<<"|";
			file<<endl;
		}
		file.close();
		AtomThreads=new thread*[CountOfAtoms];
		for(i=0; i<CountOfAtoms; i++,LineNumber++)
			AtomThreads[i]=new thread(&CrystalClass::AtomTask,this,i,LineNumber);
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
				lock_guard<mutex> lock(historyMutex);
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
					WriteFile<<setw(AtomCountOfDigits)<<crystal[i]<<"|";
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
			if (AtomThreads[i]->joinable())
				AtomThreads[i]->join();
	}
	~CrystalClass()
	{		
		int i,TrueCountOfAtoms=0,CountOfLeftSteps=0,CountOfRightSteps=0,CountOfStops=0;
		ScreenCoordinates.X=0;
		ScreenCoordinates.Y=(CrystalSize/(90/(AtomCountOfDigits+1))+1)+CountOfAtoms+3;
		SetConsoleCursorPosition(console,ScreenCoordinates);		
		for(i=0; i<CrystalSize; i++)
			TrueCountOfAtoms+=crystal[i];
		for(i=0; i<CountOfAtoms; i++)
		{
			CountOfLeftSteps+=CountsOfSteps[i][0];
			CountOfRightSteps+=CountsOfSteps[i][1];
			CountOfStops+=CountsOfSteps[i][2];
			delete AtomThreads[i];
			delete[] CountsOfSteps[i];
		}
		cout<<"TRUE COUNT OF ATOMS                     : "<<TrueCountOfAtoms<<endl;
		cout<<"COUNT OF STEPS TO THE LEFT OF ALL ATOMS : "<<CountOfLeftSteps<<endl;
		cout<<"COUNT OF STEPS TO THE RIGHT OF ALL ATOMS: "<<CountOfRightSteps<<endl;
		cout<<"COUNT OF MISSING STEPS OF ALL ATOMS     : "<<CountOfStops;
		delete[] crystal;
		delete[] AtomThreads;
		delete[] AtomPositions;
		delete[] CountsOfSteps;		
	}
	void display()
	{
		ScreenCoordinates.X=0;
		ScreenCoordinates.Y=2;
		SetConsoleCursorPosition(console,ScreenCoordinates);
		for(int i=0; i<CrystalSize; i++)
		{
			if(i*(AtomCountOfDigits+1)%(90-(90%(AtomCountOfDigits+1)))==0)
				cout<<endl;
			cout<<setw(AtomCountOfDigits)<<crystal[i]<<"|";
		}
	}
};
int main()
{
	/*mt19937 rng(random_device{}());
	double MIN_RANDOM=5;
	double MAX_RANDOM=10;
	double PART_SIZE=1.15;
	double THRESHOLD=MIN_RANDOM+(MAX_RANDOM-MIN_RANDOM)/PART_SIZE;
	uniform_real_distribution<> dist(MIN_RANDOM,MAX_RANDOM);
	double choice;
	cout<<"MIN_RANDOM: "<<MIN_RANDOM<<"; MAX_RANDOM: "<<MAX_RANDOM<<"; THRESHOLD: "<<THRESHOLD<<endl;
	int bigger_than_threshold=0;
	int smaller_than_threshold=0;
	for(int i=0; i<10; i++)
	{
		choice=dist(rng);
		if(choice>THRESHOLD)
			bigger_than_threshold++;
		else
			if(choice<THRESHOLD)
				smaller_than_threshold++;
		cout<<choice<<endl;
	}
	cout<<"bigger_than_threshold: "<<bigger_than_threshold<<endl;
	cout<<"smaller_than_threshold: "<<smaller_than_threshold<<endl;*/
	InitFloatingPointAndRandomNumbers();
	int CrystalSize=10,CountOfAtoms=10,SimulationTime=10,SnapshotsCount=10;
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
		<<"SNAPSHOTS COUNT: "<<setw(SnapshotsCountCountOfDigits)<<SnapshotsCount<<";";
	console=GetStdHandle(STD_OUTPUT_HANDLE);	
	CrystalClass* NewCrystal=new CrystalClass(CrystalSize,CountOfAtoms,SimulationTime=10,SnapshotsCount);
	delete NewCrystal;
	return 0;
}