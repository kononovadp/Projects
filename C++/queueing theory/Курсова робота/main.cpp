/*Завдання 15. На обробку до інформаційної системи приймаються три класи завдань А, В і С. Завдання класів А і В можуть вирішуватися інформаційною системою одночасно, а завдання класу С вимагають, щоб система була вільна від інших завдань. Завдання класу А надходять через 20±5 хвилин, класу В - через 20±10 хвилин і класу С - через 30±10 хвилин і потребують для виконання: клас А - 20±5 хвилин, клас В - 21±3 хвилин і клас С - 28±5 хвилин. Завдання класів А і В можуть дозавантажуватись до задачі, що вирішується.
Визначити завантаження інформаційної системи. Розглянути різноманітні засоби управління чергами і визначити той із них, при якому число завдань у чергах мінімально.*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <float.h>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <windows.h>
using namespace std;
HANDLE console;
COORD ScreenCoordinates;
ofstream statistics;
int GetRandomInt(int min, int max)
{
	if(min==max)
		return min;
	return min+(rand()%(max-min));
}
double GetRandomDouble(double min, double max)
{
    if(min==max)
		return min;
	double f=(double)rand()/RAND_MAX;	
    return min+f*(max - min);
}
string ConvertDoubleToString(double number)
{
	stringstream result;
	result<<fixed<<setprecision(2)<<number;
	return result.str();
}
void ChangeOutputOnScreenDouble(int line,int column,int FieldWidth,double NewOutput)
{
	ScreenCoordinates.X=column;
    ScreenCoordinates.Y=line;
	SetConsoleCursorPosition(console,ScreenCoordinates);
	cout<<setw(FieldWidth)<<NewOutput;
}
void ChangeOutputOnScreenChar(int line,int column,char NewOutput)
{	
	ScreenCoordinates.X=column;
    ScreenCoordinates.Y=line;
	SetConsoleCursorPosition(console,ScreenCoordinates);
	cout<<NewOutput;
}
void ChangeOutputOnScreenString(int line,int column,string NewOutput)
{
	ScreenCoordinates.X=column;
    ScreenCoordinates.Y=line;
	SetConsoleCursorPosition(console,ScreenCoordinates);
	cout<<NewOutput;
}
string AddSpacesToString(string str,int NewSize)
{
	for(int i=0; str.length()<NewSize; i++)
		if(i%2==1)
			str.insert(str.begin(),1,' ');
		else
			str+=" ";
	return str;
}
class task
{
	string name;
	int BarSize,BarPos,StartBarPos;
	double NextTime,TaskTime,PrevTaskTime,TaskProgress,StepSize,ActiveTime,BarProgress,BarStep,percent;
	public: task(string NewName,double NewTaskTime,double CurrentTime,int NewBarPos)
	{
		name=NewName;
		TaskTime=NewTaskTime;
		PrevTaskTime=TaskTime;
		NextTime=CurrentTime;
		StartBarPos=NewBarPos;
		BarPos=StartBarPos;
		StepSize=TaskTime/5.0;
		ActiveTime=0.0;
		TaskProgress=0.0;
		percent=0.0;
		BarSize=26;
		BarStep=100.0/BarSize;
		BarProgress=0.0;
	}
	task(string NewName){name=NewName;}
	string TakeOneStep(double CurrentTime)
	{
		if(TaskProgress<TaskTime)
		{
			double NewTaskProgress=TaskProgress+StepSize;
			if(NewTaskProgress<TaskTime)
			{
				TaskProgress=NewTaskProgress;
				NextTime=CurrentTime+StepSize;
				ActiveTime+=StepSize;
			}
			else
			{
				double NewStepSize=NewTaskProgress-TaskTime;
				TaskProgress=TaskTime;
				NextTime=CurrentTime+NewStepSize;
				ActiveTime+=NewStepSize;
			}
			percent=(TaskProgress*100.0)/TaskTime;
			return "The tasks of the "+name+" was executed for "+ConvertDoubleToString(percent)+"% (time: "+ConvertDoubleToString(TaskProgress)+"/"+ConvertDoubleToString(TaskTime)+")";
		}
		else
		{
			NextTime=DBL_MAX;
			TaskProgress+=10.0;
			return "The tasks of the "+name+" was FINISHED and REMOVED from the system";
		}		
	}
	double GetActiveTime(){return ActiveTime;}
	string AddTask(task NewTask)
	{
		PrevTaskTime=TaskTime;
		TaskTime+=NewTask.TaskTime;	
		StepSize=TaskTime/5.0;
		percent=(TaskProgress*100.0)/TaskTime;
		return "The tasks of the "+NewTask.name+" were added to the tasks of the "+name+" (new time: "+ConvertDoubleToString(TaskTime)+")";
	}
	void UpdateDataOnScreen()
	{
		if(TaskTime>PrevTaskTime)
		{
			BarPos=StartBarPos;
			BarProgress=0.0;
			PrevTaskTime=TaskTime;
			ChangeOutputOnScreenString(3,BarPos,"                          ");
			while(BarProgress<100.0 && BarProgress<percent)
			{
				BarProgress+=BarStep;
				ChangeOutputOnScreenChar(3,BarPos,'|');
				BarPos++;
			}
		}
		else
			if(TaskProgress==0.0)
				ChangeOutputOnScreenString(3,BarPos,"                          ");
			else
				if(TaskProgress<=TaskTime)
				{					
					while(BarProgress<100.0 && BarProgress<percent)
					{
						BarProgress+=BarStep;
						ChangeOutputOnScreenChar(3,BarPos,'|');
						BarPos++;
					}					
				}
				else					
					ChangeOutputOnScreenString(3,StartBarPos,AddSpacesToString("ABSENT",26));
	}
	string GetName(){return name;}
	void SetNextTime(double NewNextTime){NextTime=NewNextTime;}
	double GetNextTime(){return NextTime;}	
};
vector<task> InformationSystem;
class TaskCreator: public task
{
	int BarPos;
	double MinDelay,MaxDelay,MinTaskTime,MaxTaskTime;
	public: TaskCreator(string NewName,double NewMinDelay,double NewMaxDelay,double NewMinTaskTime,double NewMaxTaskTime,int NewBarPos):task(NewName)
	{		
		BarPos=NewBarPos;
		MinDelay=NewMinDelay;
		MaxDelay=NewMaxDelay;
		MinTaskTime=NewMinTaskTime;
		MaxTaskTime=NewMaxTaskTime;
		SetNextTime(GetRandomDouble(MinDelay,MaxDelay));
	}
	task TakeOneStep(double CurrentTime)
	{		
		SetNextTime(CurrentTime+GetRandomDouble(MinDelay,MaxDelay));		
		return task(GetName(),GetRandomDouble(MinTaskTime,MaxTaskTime),CurrentTime,BarPos);
	}
};
class QueueParent
{
	int MaxQueue,CountOfQueueUses,*ClassesInQueue,TotalCountOfClassesInQueue;	
	vector<int> SizesOfQueue;
	public: QueueParent()
	{
		MaxQueue=0;
		CountOfQueueUses=0;
		TotalCountOfClassesInQueue=0;
		ClassesInQueue=new int[3];	
		ClassesInQueue[0]=0;
		ClassesInQueue[1]=0;
		ClassesInQueue[2]=0;
	}
	~QueueParent(){delete(ClassesInQueue);}
	virtual void clear()
	{
		MaxQueue=0;
		CountOfQueueUses=0;
		TotalCountOfClassesInQueue=0;
		ClassesInQueue[0]=0;
		ClassesInQueue[1]=0;
		ClassesInQueue[2]=0;
		SizesOfQueue.clear();
	}
	virtual string AddTask(task NewTask,int NewSizeOfQueue)
	{		
		string TaskClassName=NewTask.GetName();
		SizesOfQueue.push_back(NewSizeOfQueue);
		if(NewSizeOfQueue>MaxQueue)
			MaxQueue=NewSizeOfQueue;
		if(TaskClassName=="class A")
			ClassesInQueue[0]++;
		else
			if(TaskClassName=="class B")
				ClassesInQueue[1]++;
			else
				ClassesInQueue[2]++;
		TotalCountOfClassesInQueue++;
		return "";
	}
	virtual string AddTask(task NewTask){return "";}
	virtual int GetSize(){return 0;}
	virtual task* GetTask(){return NULL;}
	virtual string RemoveTask(string TaskName){return "";}
	virtual string RemoveTask(){CountOfQueueUses++; return "";}
	virtual void WriteStatisticToFile()
	{
		int i,AverageQueue=0;
		for(i=0; i<SizesOfQueue.size(); i++)
			AverageQueue+=SizesOfQueue[i];
		AverageQueue/=SizesOfQueue.size();
		statistics<<MaxQueue<<";"<<AverageQueue<<";"<<(ClassesInQueue[0]*100.0)/TotalCountOfClassesInQueue<<";"<<(ClassesInQueue[1]*100.0)/TotalCountOfClassesInQueue<<";"<<(ClassesInQueue[2]*100.0)/TotalCountOfClassesInQueue<<";"<<CountOfQueueUses<<"\n";		
	}
};
//====================ONE QUEUE====================
class OneQueue: public QueueParent
{
	queue<task> QueueOfTasks;
	task* (*GetTask_OverloadedMethod)(queue<task>& QueueOfTasks);
	string (*RemoveTask_OverloadedMethod)(queue<task>& QueueOfTasks);	
	public: OneQueue(task* GetMethod(queue<task>& QueueOfTasks),string RemoveMethod(queue<task>& QueueOfTasks))
	{
		GetTask_OverloadedMethod=GetMethod;
		RemoveTask_OverloadedMethod=RemoveMethod;
	}
	string AddTask(task NewTask)
	{
		QueueOfTasks.push(NewTask);
		QueueParent::AddTask(NewTask,QueueOfTasks.size());		
		return "The tasks of the "+NewTask.GetName()+" were added to the QUEUE";
	}
	task* GetTask()
	{
		return GetTask_OverloadedMethod(QueueOfTasks);
	}
	string RemoveTask(string TaskName)
	{
		string result=RemoveTask_OverloadedMethod(QueueOfTasks);
		QueueParent::RemoveTask();		
		return result;
	}
	int GetSize(){return QueueOfTasks.size();}
	void clear()
	{
		QueueParent::clear();
		while(QueueOfTasks.size()>0)
			QueueOfTasks.pop();	
	}
};
task* GetTask_WithoutExtraction(queue<task>& QueueOfTasks){return NULL;}
string RemoveTask_WithoutExtraction(queue<task>& QueueOfTasks){return "";}
task* GetTask_SimpleQueue(queue<task>& QueueOfTasks)
{
	if(QueueOfTasks.size()>0)
		return &QueueOfTasks.front();
	return NULL;
}
string RemoveTask_SimpleQueue(queue<task>& QueueOfTasks)
{
	string result="The tasks of the "+QueueOfTasks.front().GetName()+" were removed from the QUEUE";
	QueueOfTasks.pop();	
	return result;
}
//====================ONE QUEUE FOR EACH CLASS====================
class OneQueueForEachClass: public QueueParent
{
	vector<queue<task>> QueuesOfTasks;
	void (*AddTask_OverloadedMethod)(task NewTask,vector<queue<task>>& QueuesOfTasks);
	task* (*GetTask_OverloadedMethod)(vector<queue<task>>& QueuesOfTasks);
	public: OneQueueForEachClass(void AddMethod(task NewTask,vector<queue<task>>& QueuesOfTasks),task* GetMethod(vector<queue<task>>& QueuesOfTasks))
	{
		AddTask_OverloadedMethod=AddMethod;
		GetTask_OverloadedMethod=GetMethod;
		for(int i=0; i<3; i++)
		{
			queue<task> NewQueue;
			QueuesOfTasks.push_back(NewQueue);
		}
	}
	string AddTask(task NewTask)
	{
		AddTask_OverloadedMethod(NewTask,QueuesOfTasks);
		QueueParent::AddTask(NewTask,GetSize());		
		return "The tasks of the "+NewTask.GetName()+" were added to the QUEUE";
	}
	task* GetTask(){return GetTask_OverloadedMethod(QueuesOfTasks);}
	string RemoveTask(string RemovedTaskName)
	{
		string result;
		int QueueIndex;
		for(QueueIndex=0; QueueIndex<3; QueueIndex++)
			if(QueuesOfTasks[QueueIndex].size()>0 && QueuesOfTasks[QueueIndex].front().GetName()==RemovedTaskName)
				break;
		result="The tasks of the "+QueuesOfTasks[QueueIndex].front().GetName()+" were removed from the QUEUE";
		QueuesOfTasks[QueueIndex].pop();
		QueueParent::RemoveTask();		
		return result;
	}
	int GetSize()
	{
		return QueuesOfTasks[0].size()+QueuesOfTasks[1].size()+QueuesOfTasks[2].size();
	}
	void clear()
	{
		QueueParent::clear();
		for(int i=0; i<3; i++)		
			while(QueuesOfTasks[i].size()>0)
				QueuesOfTasks[i].pop();
	}
};
void AddTask_DefaultMethod(task NewTask,vector<queue<task>>& QueuesOfTasks)
{
	string NewTaskName=NewTask.GetName();
	if(NewTaskName=="class A")
		QueuesOfTasks[0].push(NewTask);
	else
		if(NewTaskName=="class B")
			QueuesOfTasks[1].push(NewTask);
		else
			QueuesOfTasks[2].push(NewTask);
}
void AddTask_WithMerging(task NewTask,vector<queue<task>>& QueuesOfTasks)
{
	string NewTaskName=NewTask.GetName();
	if(NewTaskName=="class A")
	{
		if(QueuesOfTasks[0].size()==0)		
			QueuesOfTasks[0].push(NewTask);
		else
		{
			task TasksFromQueue=QueuesOfTasks[0].front();				
			QueuesOfTasks[0].pop();
			TasksFromQueue.AddTask(NewTask)+"\n";
			QueuesOfTasks[0].push(TasksFromQueue);			
		}
	}
	else
		if(NewTaskName=="class B")
		{
			if(QueuesOfTasks[1].size()==0)			
				QueuesOfTasks[1].push(NewTask);
			else
			{
				task TasksFromQueue=QueuesOfTasks[1].front();
				QueuesOfTasks[1].pop();
				TasksFromQueue.AddTask(NewTask)+"\n";
				QueuesOfTasks[1].push(TasksFromQueue);
				"The tasks of the "+NewTaskName+" were MERGED in the QUEUE";
			}
		}
		else		
			QueuesOfTasks[2].push(NewTask);			
}
void AddTask_WithMergingIncludingClassC(task NewTask,vector<queue<task>>& QueuesOfTasks)
{
	string NewTaskName=NewTask.GetName();
	if(NewTaskName=="class A")
	{
		if(QueuesOfTasks[0].size()==0)		
			QueuesOfTasks[0].push(NewTask);
		else
		{
			task TasksFromQueue=QueuesOfTasks[0].front();				
			QueuesOfTasks[0].pop();
			TasksFromQueue.AddTask(NewTask)+"\n";
			QueuesOfTasks[0].push(TasksFromQueue);			
		}
	}
	else
		if(NewTaskName=="class B")
		{
			if(QueuesOfTasks[1].size()==0)			
				QueuesOfTasks[1].push(NewTask);
			else
			{
				task TasksFromQueue=QueuesOfTasks[1].front();
				QueuesOfTasks[1].pop();
				TasksFromQueue.AddTask(NewTask)+"\n";
				QueuesOfTasks[1].push(TasksFromQueue);
				"The tasks of the "+NewTaskName+" were MERGED in the QUEUE";
			}
		}
		else
		{
			if(QueuesOfTasks[2].size()==0)		
				QueuesOfTasks[2].push(NewTask);
			else
			{
				task TasksFromQueue=QueuesOfTasks[2].front();				
				QueuesOfTasks[2].pop();
				TasksFromQueue.AddTask(NewTask)+"\n";
				QueuesOfTasks[2].push(TasksFromQueue);			
			}
		}
}
task* GetTask_PriorityForClassA(vector<queue<task>>& QueuesOfTasks)
{
	task* NewTask=NULL;
	if(QueuesOfTasks[0].size()>0)
		NewTask=&QueuesOfTasks[0].front();
	else
		if(QueuesOfTasks[1].size()>0)
			NewTask=&QueuesOfTasks[1].front();
		else
			if(QueuesOfTasks[2].size()>0)
				NewTask=&QueuesOfTasks[2].front();
	return NewTask;
}
task* GetTask_PriorityForClassB(vector<queue<task>>& QueuesOfTasks)
{
	task* NewTask=NULL;
	if(QueuesOfTasks[1].size()>0)
		NewTask=&QueuesOfTasks[1].front();
	else
		if(QueuesOfTasks[2].size()>0)
			NewTask=&QueuesOfTasks[2].front();
		else
			if(QueuesOfTasks[0].size()>0)
				NewTask=&QueuesOfTasks[0].front();
	return NewTask;
}
task* GetTask_PriorityForClassC(vector<queue<task>>& QueuesOfTasks)
{
	task* NewTask=NULL;
	if(QueuesOfTasks[2].size()>0)
		NewTask=&QueuesOfTasks[2].front();
	else
		if(QueuesOfTasks[1].size()>0)
			NewTask=&QueuesOfTasks[1].front();
		else
			if(QueuesOfTasks[0].size()>0)
				NewTask=&QueuesOfTasks[0].front();
		return NewTask;
}
task* GetTask_MaxQueue(vector<queue<task>>& QueuesOfTasks)
{
	task* NewTask=NULL;
	int i,CurSize,MaxSize=0,MaxQueueIndex=0;
	for(i=0; i<QueuesOfTasks.size(); i++)
	{
		CurSize=QueuesOfTasks[i].size();
		if(CurSize>MaxSize)
		{
			MaxSize=CurSize;
			MaxQueueIndex=i;
		}
	}
	if(MaxSize>0)
		NewTask=&QueuesOfTasks[MaxQueueIndex].front();
	return NewTask;
}
task* GetTask_MinQueue(vector<queue<task>>& QueuesOfTasks)
{
	task* NewTask=NULL;
	int i,CurSize,MinSize=1000,MinQueueIndex=0;
	for(i=0; i<QueuesOfTasks.size(); i++)
	{
		CurSize=QueuesOfTasks[i].size();
		if(CurSize>0 && CurSize<MinSize)
		{
			MinSize=CurSize;
			MinQueueIndex=i;
		}
	}
	if(MinSize<1000)
		NewTask=&QueuesOfTasks[MinQueueIndex].front();
	return NewTask;
}
task* GetTask_BasedOnSystem_NewTaskPreferable_MinQueue(vector<queue<task>>& QueuesOfTasks)
{
	task* NewTask=NULL;		
		if(QueuesOfTasks[0].size()==0 && QueuesOfTasks[1].size()==0 && QueuesOfTasks[2].size()==0)
			return NULL;		
		if(InformationSystem.size()==0)
			NewTask=GetTask_MinQueue(QueuesOfTasks);
		else
			if(InformationSystem.size()==1)
			{
				string SystemTaskName=InformationSystem[0].GetName();
				if(SystemTaskName=="class A")
				{
					if(QueuesOfTasks[1].size()>0)
						NewTask=&QueuesOfTasks[1].front();
					else
						if(QueuesOfTasks[0].size()>0)
							NewTask=&QueuesOfTasks[0].front();
						else
							NewTask=NULL;
				}
				else
					if(SystemTaskName=="class B")
					{
						if(QueuesOfTasks[0].size()>0)
							NewTask=&QueuesOfTasks[0].front();
						else
							if(QueuesOfTasks[1].size()>0)
								NewTask=&QueuesOfTasks[1].front();
							else
								NewTask=NULL;
					}
					else
						if(SystemTaskName=="class C")
							NewTask=NULL;
			}
			else
				NewTask=GetTask_MinQueue(QueuesOfTasks);
		return NewTask;
}
task* GetTask_BasedOnSystem_MergingPreferable_MinQueue(vector<queue<task>>& QueuesOfTasks)
{
	task* NewTask=NULL;		
		if(QueuesOfTasks[0].size()==0 && QueuesOfTasks[1].size()==0 && QueuesOfTasks[2].size()==0)
			return NULL;		
		if(InformationSystem.size()==0)
			NewTask=GetTask_MinQueue(QueuesOfTasks);
		else
			if(InformationSystem.size()==1)
			{
				string SystemTaskName=InformationSystem[0].GetName();
				if(SystemTaskName=="class A")
				{
					if(QueuesOfTasks[0].size()>0)
						NewTask=&QueuesOfTasks[0].front();
					else
						if(QueuesOfTasks[1].size()>0)
							NewTask=&QueuesOfTasks[1].front();
						else
							NewTask=NULL;
				}
				else
					if(SystemTaskName=="class B")
					{
						if(QueuesOfTasks[1].size()>0)
							NewTask=&QueuesOfTasks[1].front();
						else
							if(QueuesOfTasks[0].size()>0)
								NewTask=&QueuesOfTasks[0].front();
							else
								NewTask=NULL;
					}
					else
						if(SystemTaskName=="class C")
							NewTask=NULL;
			}
			else
				NewTask=GetTask_MinQueue(QueuesOfTasks);
		return NewTask;
}
task* GetTask_BasedOnSystem_NewTaskPreferable_MaxQueue(vector<queue<task>>& QueuesOfTasks)
{
	task* NewTask=NULL;		
		if(QueuesOfTasks[0].size()==0 && QueuesOfTasks[1].size()==0 && QueuesOfTasks[2].size()==0)
			return NULL;		
		if(InformationSystem.size()==0)
			NewTask=GetTask_MaxQueue(QueuesOfTasks);
		else
			if(InformationSystem.size()==1)
			{
				string SystemTaskName=InformationSystem[0].GetName();
				if(SystemTaskName=="class A")
				{
					if(QueuesOfTasks[1].size()>0)
						NewTask=&QueuesOfTasks[1].front();
					else
						if(QueuesOfTasks[0].size()>0)
							NewTask=&QueuesOfTasks[0].front();
						else
							NewTask=NULL;
				}
				else
					if(SystemTaskName=="class B")
					{
						if(QueuesOfTasks[0].size()>0)
							NewTask=&QueuesOfTasks[0].front();
						else
							if(QueuesOfTasks[1].size()>0)
								NewTask=&QueuesOfTasks[1].front();
							else
								NewTask=NULL;
					}
					else
						if(SystemTaskName=="class C")
							NewTask=NULL;
			}
			else
				NewTask=GetTask_MaxQueue(QueuesOfTasks);
		return NewTask;
}
task* GetTask_BasedOnSystem_MergingPreferable_MaxQueue(vector<queue<task>>& QueuesOfTasks)
{
	task* NewTask=NULL;		
		if(QueuesOfTasks[0].size()==0 && QueuesOfTasks[1].size()==0 && QueuesOfTasks[2].size()==0)
			return NULL;		
		if(InformationSystem.size()==0)
			NewTask=GetTask_MaxQueue(QueuesOfTasks);
		else
			if(InformationSystem.size()==1)
			{
				string SystemTaskName=InformationSystem[0].GetName();
				if(SystemTaskName=="class A")
				{
					if(QueuesOfTasks[0].size()>0)
						NewTask=&QueuesOfTasks[0].front();
					else
						if(QueuesOfTasks[1].size()>0)
							NewTask=&QueuesOfTasks[1].front();
						else
							NewTask=NULL;
				}
				else
					if(SystemTaskName=="class B")
					{
						if(QueuesOfTasks[1].size()>0)
							NewTask=&QueuesOfTasks[1].front();
						else
							if(QueuesOfTasks[0].size()>0)
								NewTask=&QueuesOfTasks[0].front();
							else
								NewTask=NULL;
					}
					else
						if(SystemTaskName=="class C")
							NewTask=NULL;
			}
			else
				NewTask=GetTask_MaxQueue(QueuesOfTasks);
		return NewTask;
}
void TestModel(QueueParent* QueueOfTasks,bool MergingIsActive)
{
	int i,CountOfTasks=0,CountOfFinishedTasks,CountOfMergings=0,CountOfLoads=0;
	int BarSize=50,BarPos=33;
	double SimulationTime=1000.0,CurrentTime=0.0,NextTime,CurrentLoad=0.0,AverageLoad=0.0;
	double BarProgress=0.0,BarStep=100.0/BarSize,percent=0.0;
	double CurrentActiveTime,*ActiveTime=new double[3];
	bool ExecuteSystemTasks,TheTasksWereMerged;
	string NewTaskName;	
	vector<string> results;
	vector<TaskCreator> CreatorsOfTasks;
	CreatorsOfTasks.push_back(TaskCreator("class A",15.0,25.0,15.0,25.0,0));
	CreatorsOfTasks.push_back(TaskCreator("class B",10.0,30.0,18.0,24.0,27));
	CreatorsOfTasks.push_back(TaskCreator("class C",20.0,40.0,23.0,33.0,54));	
	/*cout<<"SIMULATION TIME: "<<left<<setw(7)<<CurrentTime<<"/"<<left<<setw(7)<<SimulationTime<<"                                                    "<<left<<setw(6)<<percent<<"%";
	cout<<"       TASK CLASS A       |       TASK CLASS B       |       TASK CLASS C       |QUEUE|LOAD";
	cout<<AddSpacesToString("ABSENT",26)<<"|"<<AddSpacesToString("ABSENT",26)<<"|"<<AddSpacesToString("ABSENT",26)<<"|"<<AddSpacesToString(to_string(0),5)<<"|"<<AddSpacesToString(to_string((int)CurrentLoad),4);*/
	for(i=0; i<3; i++)	
		ActiveTime[i]=0.0;
	while(CurrentTime<SimulationTime)
	{		
		if(InformationSystem.size()>1)
		{
			bool CorrectSystem=true;
			for(i=0; i<InformationSystem.size(); i++)
				if(InformationSystem[i].GetName()=="class C")
					CorrectSystem=false;
			if((InformationSystem[0].GetName()=="class A" && InformationSystem[1].GetName()=="class A") || (InformationSystem[0].GetName()=="class B" && InformationSystem[1].GetName()=="class B"))
				CorrectSystem=false;			
			if(CorrectSystem==false || InformationSystem.size()>2)
			{
				ChangeOutputOnScreenString(4,0,"INCORRECT SYSTEM!!!");
				getchar();
				exit(1);
			}
		}
		CurrentTime=SimulationTime;
		for(i=0,ExecuteSystemTasks=false; i<InformationSystem.size(); i++)
		{
			NextTime=InformationSystem[i].GetNextTime();
			if(NextTime<CurrentTime)
			{
				CurrentTime=NextTime;
				ExecuteSystemTasks=true;
			}
		}
		for(i=0; i<CreatorsOfTasks.size(); i++)
		{
			NextTime=CreatorsOfTasks[i].GetNextTime();
			if(NextTime<CurrentTime)
			{
				CurrentTime=NextTime;
				ExecuteSystemTasks=false;
			}
		}
		task* NewTask=QueueOfTasks->GetTask();
		if(NewTask!=NULL)
		{			
			NewTaskName=NewTask->GetName();			
			if(InformationSystem.size()==0)
			{
				NewTask->SetNextTime(CurrentTime);
				InformationSystem.push_back(*NewTask);
				results.push_back(QueueOfTasks->RemoveTask(NewTaskName));
				results.push_back("QUEUE: The tasks of the "+NewTaskName+" were added to the InformationSystem");				
			}
			else
				if(NewTaskName!="class C" && InformationSystem[0].GetName()!="class C")
				{
					TheTasksWereMerged=false;
					if(MergingIsActive==true)
						for(int i=0; i<InformationSystem.size(); i++)
							if(InformationSystem[i].GetName()==NewTaskName)
							{
								CountOfMergings++;							
								TheTasksWereMerged=true;
								results.push_back(QueueOfTasks->RemoveTask(NewTaskName));
								results.push_back("QUEUE: "+InformationSystem[i].AddTask(*NewTask));
								break;
							}
					if(InformationSystem.size()==1 && InformationSystem[0].GetName()!=NewTaskName)
					{						
						NewTask->SetNextTime(CurrentTime);
						InformationSystem.push_back(*NewTask);
						results.push_back(QueueOfTasks->RemoveTask(NewTaskName));
						results.push_back("QUEUE: The tasks of the "+NewTaskName+" were added to the InformationSystem");
					}
				}
		}
		if(ExecuteSystemTasks==true)		
			for(i=0; i<InformationSystem.size(); i++)
				if(InformationSystem[i].GetNextTime()==CurrentTime)
					results.push_back(InformationSystem[i].TakeOneStep(CurrentTime));
		for(i=0; i<CreatorsOfTasks.size(); i++)
			if(CreatorsOfTasks[i].GetNextTime()==CurrentTime)
			{
				task NewTask=CreatorsOfTasks[i].TakeOneStep(CurrentTime);				
				NewTaskName=NewTask.GetName();
				CountOfTasks++;
				if(InformationSystem.size()==0)
				{
					InformationSystem.push_back(NewTask);					
					results.push_back("The tasks of the "+NewTaskName+" were added to the InformationSystem");
				}
				else
				{
					if(NewTaskName=="class C" || InformationSystem[0].GetName()=="class C")
						results.push_back(QueueOfTasks->AddTask(NewTask));
					else
					{						
						TheTasksWereMerged=false;
						if(MergingIsActive==true)
							for(i=0; i<InformationSystem.size(); i++)
								if(NewTaskName==InformationSystem[i].GetName())
								{
									results.push_back(InformationSystem[i].AddTask(NewTask));
									CountOfMergings++;
									TheTasksWereMerged=true;
								}
						if(TheTasksWereMerged==false)
						{
							if(InformationSystem.size()==1 && InformationSystem[0].GetName()!=NewTaskName)
							{
								InformationSystem.push_back(NewTask);
								results.push_back("The tasks of the "+NewTaskName+" were added to the InformationSystem");
							}
							else
								results.push_back(QueueOfTasks->AddTask(NewTask));
						}
					}
				}
			}
		percent=(CurrentTime*100.0)/SimulationTime;
		/*ScreenCoordinates.X=0;
		ScreenCoordinates.Y=4;
		SetConsoleCursorPosition(console,ScreenCoordinates);
		cout<<"--------------------Events of the time "<<CurrentTime<<":--------------------\n";
		for(i=0; i<results.size(); i++)
			cout<<results[i]<<endl;
		getchar();
		ChangeOutputOnScreenDouble(1,17,7,CurrentTime);
		ChangeOutputOnScreenDouble(1,84,6,percent);
		while(BarProgress<100 && BarProgress<percent)
		{
			BarProgress+=BarStep;
			ChangeOutputOnScreenChar(1,BarPos,'|');
			BarPos++;
		}*/
		for(i=0; i<InformationSystem.size(); i++)
		{
			//InformationSystem[i].UpdateDataOnScreen();
			if(InformationSystem[i].GetNextTime()==DBL_MAX)
			{
				NewTaskName=InformationSystem[i].GetName();
				CurrentActiveTime=InformationSystem[i].GetActiveTime();				
				if(NewTaskName=="class A")
					ActiveTime[0]+=CurrentActiveTime;
				else
					if(NewTaskName=="class B")
						ActiveTime[1]+=CurrentActiveTime;
					else
						ActiveTime[2]+=CurrentActiveTime;
				InformationSystem.erase(InformationSystem.begin()+i);
			}
		}
		if(InformationSystem.size()>0)
		{
			if(InformationSystem.size()==1)
			{
				if(InformationSystem[0].GetName()=="class C")				
					CurrentLoad=100.0;
				else
					CurrentLoad=50.0;
			}
			else
				CurrentLoad=100.0;
			CountOfLoads++;
			AverageLoad+=CurrentLoad;
		}
		else
			CurrentLoad=0.0;
		/*ChangeOutputOnScreenString(3,81,AddSpacesToString(to_string(QueueOfTasks->GetSize()),5)+"|"+AddSpacesToString(to_string((int)CurrentLoad),4));
		ScreenCoordinates.X=0;
		ScreenCoordinates.Y=4;
		SetConsoleCursorPosition(console,ScreenCoordinates);
		for(i=0; i<results.size()+1; i++)
			cout<<"                                                                                          \n";*/
		results.clear();
	}
	CountOfFinishedTasks=CountOfTasks-(InformationSystem.size()+QueueOfTasks->GetSize());
	statistics<<CountOfTasks<<";"<<CountOfFinishedTasks<<";"<<(double)(CountOfFinishedTasks*100.0)/CountOfTasks<<";"<<CountOfMergings<<";"<<AverageLoad/CountOfLoads<<";"<<(ActiveTime[0]*100.0)/SimulationTime<<";"<<(ActiveTime[1]*100.0)/SimulationTime<<";"<<(ActiveTime[2]*100.0)/SimulationTime<<";";
	QueueOfTasks->WriteStatisticToFile();
	ScreenCoordinates.X=0;
    ScreenCoordinates.Y=0;
	SetConsoleCursorPosition(console,ScreenCoordinates);
	QueueOfTasks->clear();
	InformationSystem.clear();
	delete(ActiveTime);
}
int main(void)
{
/*
Count   ;Count of  ;% of fin.;Count of;Avg.  ;% of time  ;% of time  ;% of time  ;Max. ;Avg.  ;% of class A;% of class B;% of class C;Count of  
of tasks;fin. tasks;tasks    ;mergings;load %;for class A;for class B;for class C;queue;queue;in queue    ;in queue    ;in queue    ;queue uses
Count   ;count of  ;% of fin.;Count of;Avg.  ;% of time  ;% of time  ;% of time  
of tasks;fin. tasks;tasks    ;mergings;load %;for class A;for class B;for class C
Max. ;Avg.  ;% of class A;% of class B;% of class C;Count of  
queue;queue;in queue    ;in queue    ;in queue    ;queue uses
*/		
	console=GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(0));
	cout.precision(2);
	cout.setf(ios::fixed);
	int i,j,CountOfOneTypeExperiments=10,TotalCountOfExperiments;
	int ExperimentNumber=1,ExperimentNumberInFile=1,CountOfAllExperiments;
	statistics.open("statistics.csv");	
	statistics.precision(2);
	statistics.setf(ios::fixed);
	vector<QueueParent*> queues;
	vector<string> NamesOfExperiments;	
	NamesOfExperiments.push_back("One queue without extractions");	
	queues.push_back(new OneQueue(GetTask_WithoutExtraction,RemoveTask_WithoutExtraction));	
	NamesOfExperiments.push_back("One queue with extractions");
	queues.push_back(new OneQueue(GetTask_SimpleQueue,RemoveTask_SimpleQueue));	
	NamesOfExperiments.push_back("One queue for each class (3 queues): default push method, get method with priority for class A");
	queues.push_back(new OneQueueForEachClass(AddTask_DefaultMethod,GetTask_PriorityForClassA));	
	NamesOfExperiments.push_back("One queue for each class (3 queues): default push method, get method with priority for class B");
	queues.push_back(new OneQueueForEachClass(AddTask_DefaultMethod,GetTask_PriorityForClassB));	
	NamesOfExperiments.push_back("One queue for each class (3 queues): default push method, get method with priority for class C");
	queues.push_back(new OneQueueForEachClass(AddTask_DefaultMethod,GetTask_PriorityForClassC));	
	NamesOfExperiments.push_back("One queue for each class (3 queues): default push method, getting tasks from min. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_DefaultMethod,GetTask_MinQueue));
	NamesOfExperiments.push_back("One queue for each class (3 queues): default push method, getting tasks from max. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_DefaultMethod,GetTask_MaxQueue));
	NamesOfExperiments.push_back("One queue for each class (3 queues) based on the system state: default push method, bigger priority for simultaneous execution of several tasks, otherwise extraction from min. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_DefaultMethod,GetTask_BasedOnSystem_NewTaskPreferable_MinQueue));
	NamesOfExperiments.push_back("One queue for each class (3 queues) based on the system state: default push method, bigger priority for merging of tasks, otherwise extraction from min. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_DefaultMethod,GetTask_BasedOnSystem_MergingPreferable_MinQueue));	
	NamesOfExperiments.push_back("One queue for each class (3 queues) based on the system state: default push method, bigger priority for simultaneous execution of several tasks, otherwise extraction from max. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_DefaultMethod,GetTask_BasedOnSystem_NewTaskPreferable_MaxQueue));
	NamesOfExperiments.push_back("One queue for each class (3 queues) based on the system state: default push method, bigger priority for merging of tasks, otherwise extraction from max. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_DefaultMethod,GetTask_BasedOnSystem_MergingPreferable_MaxQueue));
	NamesOfExperiments.push_back("One queue for each class (3 queues) based on the system state: push method with merging, bigger priority for simultaneous execution of several tasks, otherwise extraction from min. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_WithMerging,GetTask_BasedOnSystem_NewTaskPreferable_MinQueue));
	NamesOfExperiments.push_back("One queue for each class (3 queues) based on the system state: push method with merging, bigger priority for merging of tasks, otherwise extraction from min. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_WithMerging,GetTask_BasedOnSystem_MergingPreferable_MinQueue));	
	NamesOfExperiments.push_back("One queue for each class (3 queues) based on the system state: push method with merging, bigger priority for simultaneous execution of several tasks, otherwise extraction from max. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_WithMerging,GetTask_BasedOnSystem_NewTaskPreferable_MaxQueue));
	NamesOfExperiments.push_back("One queue for each class (3 queues) based on the system state: push method with merging, bigger priority for merging of tasks, otherwise extraction from max. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_WithMerging,GetTask_BasedOnSystem_MergingPreferable_MaxQueue));
	NamesOfExperiments.push_back("One queue for each class (3 queues) based on the system state: push method with merging of tasks of ALL classes, bigger priority for simultaneous execution of several tasks, otherwise extraction from min. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_WithMergingIncludingClassC,GetTask_BasedOnSystem_NewTaskPreferable_MinQueue));
	NamesOfExperiments.push_back("One queue for each class (3 queues) based on the system state: push method with merging of tasks of ALL classes, bigger priority for merging of tasks, otherwise extraction from min. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_WithMergingIncludingClassC,GetTask_BasedOnSystem_MergingPreferable_MinQueue));	
	NamesOfExperiments.push_back("One queue for each class (3 queues) based on the system state: push method with merging of tasks of ALL classes, bigger priority for simultaneous execution of several tasks, otherwise extraction from max. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_WithMergingIncludingClassC,GetTask_BasedOnSystem_NewTaskPreferable_MaxQueue));
	NamesOfExperiments.push_back("One queue for each class (3 queues) based on the system state: push method with merging of tasks of ALL classes, bigger priority for merging of tasks, otherwise extraction from max. queue");
	queues.push_back(new OneQueueForEachClass(AddTask_WithMergingIncludingClassC,GetTask_BasedOnSystem_MergingPreferable_MaxQueue));
	TotalCountOfExperiments=queues.size()*10;
	CountOfAllExperiments=queues.size()*2;
	statistics<<"MERGING IS ON;;;;;;;;;;;;;;\n";
	for(i=0; i<queues.size(); i++,ExperimentNumberInFile++)
	{
		statistics<<"Experiment "<<ExperimentNumberInFile<<"/"<<CountOfAllExperiments<<": "<<NamesOfExperiments[i]<<":;;;;;;;;;;;;;;\nCount   ;Count of  ;% of fin.;Count of;Avg.  ;% of time  ;% of time  ;% of time  ;Max. ;Avg.  ;% of class A;% of class B;% of class C;Count of\nof tasks;fin. tasks;tasks    ;mergings;load %;for class A;for class B;for class C;queue;queue;in queue    ;in queue    ;in queue    ;queue uses\n";
		for(j=0; j<CountOfOneTypeExperiments; j++,ExperimentNumber++)
		{
			//cout<<"Experiment "<<ExperimentNumber<<"/"<<TotalCountOfExperiments<<": "<<NamesOfExperiments[i]<<"\n";
			TestModel(queues[i],true);
		}
	}
	statistics<<"MERGING IS OFF;;;;;;;;;;;;;;\n";
	for(i=0; i<queues.size(); i++,ExperimentNumberInFile++)
	{
		statistics<<"Experiment "<<ExperimentNumberInFile<<"/"<<CountOfAllExperiments<<": "<<NamesOfExperiments[i]<<":;;;;;;;;;;;;;;\nCount   ;Count of  ;% of fin.;Count of;Avg.  ;% of time  ;% of time  ;% of time  ;Max. ;Avg.  ;% of class A;% of class B;% of class C;Count of\nof tasks;fin. tasks;tasks    ;mergings;load %;for class A;for class B;for class C;queue;queue;in queue    ;in queue    ;in queue    ;queue uses\n";
		for(j=0; j<CountOfOneTypeExperiments; j++,ExperimentNumber++)
		{
			//cout<<"Experiment "<<ExperimentNumber<<"/"<<TotalCountOfExperiments<<": "<<NamesOfExperiments[i]<<"\n";
			TestModel(queues[i],false);
		}
	}
	/*ScreenCoordinates.X=0;
	ScreenCoordinates.Y=4;
	SetConsoleCursorPosition(console,ScreenCoordinates);*/
	statistics.close();
	return 0;
}