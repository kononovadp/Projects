#include "headers/workshop.h"
workshop::workshop(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double reliability,int CountOfBreakdowns,double NewWorkSpeed,int NewMaxQueueOfDevices,device** NewRobots):device(NewClassName,NewId,NewIndex,NewLineNumber,NewColumnNumber,reliability,CountOfBreakdowns)
{
	MaxQueueOfDevices=NewMaxQueueOfDevices;
	AllRobots=NewRobots;
	WorkSpeed=NewWorkSpeed;
	TaskNumber=0;
	WorkTime=0.0;
	WorkProgress=0.0;
	BarSize=15;
	BarStep=100.0/BarSize;
	BarProgress=0.0;
	BarPos=GetColumnNumber()+21;
	cout<<GetState()<<"|"<<AddSpacesToString(to_string(tasks.size())+"/"+to_string(MaxQueueOfDevices),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|               ";
}
bool workshop::AddTask(int RobotIndex,double WorkTime)
{
	if(GetState()!="BROKEN" && tasks.size()<MaxQueueOfDevices)
	{
		struct task* NewTask=new task();
		NewTask->performer=RobotIndex;
		NewTask->WorkTime=WorkTime;
		tasks.push(NewTask);
		if(GetState()=="waiting")
		{
			SetNextTime(GetDelay(Workshop_MeanDelayOrMinDelay,Workshop_MaxDelayOrDeviation,Workshop_DelayDistribution));			
		}
		return true;
	}
	return false;
}
string workshop::TakeOneStep()
{
	string result="ROBOT "+GetId()+": ";
	if(tasks.size()>0)
	{
		if(WorkTime==0.0)
		{
			struct task* NewTask=tasks.front();
			tasks.pop();
			TaskNumber++;
			WorkTime=NewTask->WorkTime;
			CurrentRobot=NewTask->performer;
			result+="execution of task "+to_string(TaskNumber)+"/"+to_string(tasks.size())+" started (robot "+AllRobots[CurrentRobot]->GetId()+"; time of work: "+ConvertDoubleToString(WorkTime)+")";
			SetNextTime(WorkSpeed);
			SetState("proc. 3");
		}
		else
			if(WorkProgress<WorkTime)
			{
				double NewWorkProgress=WorkProgress+1.0;
				if(NewWorkProgress<WorkTime)
				{
					WorkProgress=NewWorkProgress;
					SetNextTime(WorkSpeed);
				}
				else
				{
					double NewStepSize=1.0-(NewWorkProgress-WorkTime);
					WorkProgress+=NewStepSize;
					SetNextTime((WorkSpeed/100.0)*((NewStepSize*100.0)/1.0));
				}
				percent=(WorkProgress*100.0)/WorkTime;
				result+="the task "+to_string(TaskNumber)+"/"+to_string(tasks.size())+" was executed for "+ConvertDoubleToString(percent)+"% ("+ConvertDoubleToString(WorkProgress)+"/"+ConvertDoubleToString(WorkTime)+")";
			}
			else
			{
				WorkTime=0.0;
				WorkProgress=0.0;
				BarProgress=0.0;
				BarPos=GetColumnNumber()+21;
			}
	}
	else
	{
		SetState("waiting");
		SetNextTime(SimulationTime);
		result+="execution of all tasks finished";
	}
	return result;
}
void workshop::UpdateDataOnScreen()
{
	if(WorkTime==0.0)
		cout<<GetState()<<"|"<<AddSpacesToString(to_string(tasks.size())+"/"+to_string(MaxQueueOfDevices),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|               ";
	else
	{
		cout<<GetState()<<"|"<<AddSpacesToString(to_string(tasks.size())+"/"+to_string(MaxQueueOfDevices),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|";
		while(BarProgress<100.0 && BarProgress<percent)
		{
			BarProgress+=BarStep;
			ChangeOutputOnScreenChar(GetLineNumber(),BarPos,'|');
			BarPos++;
		}
	}
}