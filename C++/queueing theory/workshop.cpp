#include "headers/workshop.h"
workshop::workshop(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double reliability,int CountOfBreakdowns,int NewMaxQueueOfDevices,device** NewRobots):device(NewClassName,NewId,NewIndex,NewLineNumber,NewColumnNumber,reliability,CountOfBreakdowns)
{
	MaxQueueOfDevices=NewMaxQueueOfDevices;
	AllRobots=NewRobots;
	MaxCountOfRobotsInQueue=0;
	TaskNumber=0;
	CountOfTasks=0;
	WorkTime=0.0;
	TotalCountOfTasks=0;
	TotalCountOfFinishedTasks=0;
	ActiveTime=0.0;	
	AverageDelay=0.0;
	CountOfDelays=0;
	BarSize=15;
	BarStep=100.0/BarSize;
	BarProgress=0.0;
	BarPos=GetColumnNumber()+21;
	cout<<GetState()<<"|"<<AddSpacesToString(to_string(CountOfTasks)+"/"+to_string(MaxQueueOfDevices),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|               ";
}
workshop::~workshop()
{
	tasks.pop();
}
int workshop::GetMaxCountOfRobotsInQueue(){return MaxCountOfRobotsInQueue;}
int workshop::GetAverageQueue()
{
	if(SizesOfQueue.size()==0)
		return 0;
	int i,AvgQueue=0;
	for(i=0; i<SizesOfQueue.size(); i++)
		AvgQueue+=SizesOfQueue[i];
	return AvgQueue/SizesOfQueue.size();
}
double workshop::GetAverageDelay()
{
	if(CountOfDelays==0)
		return 0.0;	
	return AverageDelay/CountOfDelays;
}
double workshop::GetLoad(){return (ActiveTime*100.0)/SimulationTime;}
int workshop::GetTotalCountOfTasks(){return TotalCountOfTasks;}
double workshop::GetPercentageOfFinishedTasks()
{
	if(TotalCountOfFinishedTasks==0 && TotalCountOfTasks==0)
		return 100.0;
	else
		return (TotalCountOfFinishedTasks*100.0)/TotalCountOfTasks;
}
bool workshop::AddTask(int RobotIndex,double WorkTime)
{	
	if(GetState()!="BROKEN " && tasks.size()<MaxQueueOfDevices)
	{
		struct task* NewTask=new task();
		NewTask->performer=RobotIndex;
		NewTask->WorkTime=WorkTime;
		tasks.push(NewTask);
		SizesOfQueue.push_back(tasks.size());
		if(GetState()=="waiting")
		{
			double NewTimeInterval=GetDelay(Workshop_MeanDelayOrMinDelay,Workshop_MaxDelayOrDeviation,Workshop_DelayDistribution);
			AverageDelay+=NewTimeInterval;
			CountOfDelays++;
			SetNextTime(NewTimeInterval);
		}
		CountOfTasks++;
		ChangeOutputOnScreenString(GetLineNumber(),GetColumnNumber()+8,AddSpacesToString(to_string(tasks.size())+"/"+to_string(MaxQueueOfDevices),7));
		TotalCountOfTasks++;
		if(tasks.size()>MaxCountOfRobotsInQueue)
			MaxCountOfRobotsInQueue=tasks.size();
		return true;
	}
	IncreaseCountOfFailures();
	return false;
}
string workshop::TakeOneStep()
{
	string result="WORKSHOP "+GetId()+": ";
	if(WorkTime==0.0)
	{
		struct task* NewTask=tasks.front();		
		TaskNumber++;
		WorkTime=NewTask->WorkTime;
		CurrentRobot=NewTask->performer;
		StepSize=WorkTime/5.0;
		WorkProgress=StepSize;
		percent=(WorkProgress*100.0)/WorkTime;
		result+="the task "+to_string(TaskNumber)+"/"+to_string(CountOfTasks)+" was executed for "+ConvertDoubleToString(percent)+"% ("+ConvertDoubleToString(WorkProgress)+"/"+ConvertDoubleToString(WorkTime)+")";
		SetNextTime(StepSize);
		ActiveTime+=StepSize;
		SetState("proc. 3");
	}
	else
	{
		if(WorkProgress<WorkTime)
		{
			double NewWorkProgress=WorkProgress+StepSize;
			if(NewWorkProgress<WorkTime)
			{
				WorkProgress=NewWorkProgress;
				SetNextTime(StepSize);
				ActiveTime+=StepSize;
			}
			else
			{
				double NewStepSize=StepSize-(NewWorkProgress-WorkTime);				
				WorkProgress=WorkTime;//WorkProgress+=NewStepSize;
				SetNextTime(NewStepSize);
				ActiveTime+=StepSize;
			}
			percent=(WorkProgress*100.0)/WorkTime;
			result+="the task "+to_string(TaskNumber)+"/"+to_string(CountOfTasks)+" was executed for "+ConvertDoubleToString(percent)+"% ("+ConvertDoubleToString(WorkProgress)+"/"+ConvertDoubleToString(WorkTime)+")";
		}
		else
		{				
			WorkProgress=0.0;
			BarProgress=0.0;
			BarPos=GetColumnNumber()+21;				
			AllRobots[CurrentRobot]->AddDelay(GetDelay(Robot_MeanDelayOrMinDelay,Robot_MaxDelayOrDeviation,Robot_DelayDistribution));
			result+="the task "+to_string(TaskNumber)+"/"+to_string(CountOfTasks)+" (robot "+to_string(CurrentRobot)+", work time "+ConvertDoubleToString(WorkTime)+") was finished";
			WorkTime=0.0;
			tasks.pop();
			ChangeOutputOnScreenString(GetLineNumber(),GetColumnNumber()+8,AddSpacesToString(to_string(tasks.size())+"/"+to_string(MaxQueueOfDevices),7));
			TotalCountOfFinishedTasks++;
			if(tasks.size()>0)
			{
				double NewTimeInterval=GetDelay(Workshop_MeanDelayOrMinDelay,Workshop_MaxDelayOrDeviation,Workshop_DelayDistribution);
				AverageDelay+=NewTimeInterval;
				CountOfDelays++;
				SetNextTime(NewTimeInterval);
			}
			else
			{
				TaskNumber=0;
				CountOfTasks=0;
				SetState("waiting");
				SetNextTime(DBL_MAX);				
			}
		}
	}
	device::WriteToFile(result);
	return result;
}
void workshop::UpdateDataOnScreen()
{
	if(WorkTime==0.0)
		ChangeOutputOnScreenString(GetLineNumber(),GetColumnNumber(),GetState()+"|"+AddSpacesToString(to_string(tasks.size())+"/"+to_string(MaxQueueOfDevices),7)+"|"+AddSpacesToString(to_string(GetCountOfFailures()),4)+"|               ");
	else
	{
		ChangeOutputOnScreenString(GetLineNumber(),GetColumnNumber(),GetState()+"|"+AddSpacesToString(to_string(tasks.size())+"/"+to_string(MaxQueueOfDevices),7)+"|"+AddSpacesToString(to_string(GetCountOfFailures()),4)+"|");
		while(BarProgress<100.0 && BarProgress<percent)
		{
			BarProgress+=BarStep;
			ChangeOutputOnScreenChar(GetLineNumber(),BarPos,'|');
			BarPos++;
		}
	}
}