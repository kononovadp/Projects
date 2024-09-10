#include "headers/robot.h"
robot::robot(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double reliability,int CountOfBreakdowns,double NewTaskTime,double NewMovementTime,device* NewCreator,workshop** NewWorkshops):device(NewClassName,NewId,NewIndex,NewLineNumber,NewColumnNumber,reliability,CountOfBreakdowns)
{
	location="creator";
	TaskTime=NewTaskTime;
	MovementTime=NewMovementTime;
	workshops=NewWorkshops;
	creator=NewCreator;
	CountOfTasks=0;
	TotalCountOfTasks=0;
	CountOfFinishedTasks=0;	
	TotalCountOfFinishedTasks=0;
	CountOfReturnings=0;
	TimeForOneTask=0.0;
	AverageTimeForOneTask=0.0;
	AverageDelay=0.0;
	CountOfDelays=0;
	CurrentPosition=0;
	ActiveTime=0.0;
	percent=0.0;
	BarProgress=0.0;
	BarSize=16;
	BarStep=100.0/BarSize;
	BarPos=46;	
	CountsOfAttempts=new char[CountOfWorkshops];
	for(int i=0; i<CountOfWorkshops; i++)
		CountsOfAttempts[i]=0;
	cout<<GetState()<<"|"<<AddSpacesToString(to_string(CountOfFinishedTasks)+"/"+to_string(CountOfTasks),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|"<<AddSpacesToString(ConvertDoubleToString(percent)+"%",15)<<"|                |"<<AddSpacesToString(location,28);
	CountOfFinishedTasks=-1;
	TaskIndex=0;
	SetNextTime(DBL_MAX);
}
robot::~robot()
{
	tasks.clear();
	route.clear();
	delete(CountsOfAttempts);
	TheShortestRoute.clear();	
}
void robot::AddDelay(double NewNextTime)
{
	CountOfDelays++;
	AverageDelay+=NewNextTime;
	SetNextTime(NewNextTime);
	ChangeOutputOnScreenString(GetLineNumber(),63,AddSpacesToString("route",28));
}
double robot::GetAverageDelay(){return AverageDelay/CountOfDelays;}
double robot::GetAverageTimeForOneTask()
{
	if(CountOfFinishedTasks<1)
		return 0.0;
	return AverageTimeForOneTask/CountOfFinishedTasks;
}
double robot::GetLoad(){return (ActiveTime*100.0)/SimulationTime;}
double robot::GetCountOfTasks(){return TotalCountOfTasks;}
double robot::GetPercentageOfFinishedTasks()
{
	if(TotalCountOfFinishedTasks==0 && TotalCountOfTasks==0)
		return 0.0;
	else
		return (TotalCountOfFinishedTasks*100.0)/TotalCountOfTasks;	 
}
int robot::GetCountOfReturnings(){return CountOfReturnings;}
bool robot::AddTask(int workshop,double WorkTime)
{
	struct task* NewTask=new task();
	NewTask->performer=workshop;
	NewTask->WorkTime=WorkTime;
	tasks.push_back(NewTask);	
	CountsOfAttempts[workshop]=0;
	CountOfTasks=0;	
	CountOfFinishedTasks=-1;
	TaskIndex=0;
	TotalCountOfTasks++;
	ChangeOutputOnScreenString(GetLineNumber(),63,AddSpacesToString("route",28));
	return true;
}
string robot::TakeOneStep()
{
	string result="ROBOT "+GetId()+": ";
	if(CountOfTasks==0)
	{
		if(CountOfFinishedTasks==-1)
		{
			percent=0.0;
			BarProgress=0.0;
			SetState("proc. 1");
			CountOfFinishedTasks=1;
			result+="the task "+to_string(CountOfFinishedTasks)+"/"+to_string(tasks.size())+" ("+NamesOfWorkshops[tasks[CountOfFinishedTasks-1]->performer]+" "+ConvertDoubleToString(tasks[CountOfFinishedTasks-1]->WorkTime)+") was added";
			ActiveTime+=TaskTime;
			SetNextTime(TaskTime);
		}
		else
		{
			if(CountOfFinishedTasks+1<tasks.size())
			{
				CountOfFinishedTasks++;
				percent=(CountOfFinishedTasks*100.0)/tasks.size();
				result+="the task "+to_string(CountOfFinishedTasks)+"/"+to_string(tasks.size())+" ("+NamesOfWorkshops[tasks[CountOfFinishedTasks-1]->performer]+" "+ConvertDoubleToString(tasks[CountOfFinishedTasks-1]->WorkTime)+") was added";
				SetNextTime(TaskTime);
				ActiveTime+=TaskTime;
				TimeForOneTask+=TaskTime;
				AverageTimeForOneTask+=TaskTime;
			}
			else
			{
				result+="the task "+to_string(CountOfFinishedTasks+1)+"/"+to_string(tasks.size())+" ("+NamesOfWorkshops[tasks[CountOfFinishedTasks]->performer]+" "+ConvertDoubleToString(tasks[CountOfFinishedTasks]->WorkTime)+") was added";
				percent=0.0;
				BarProgress=0.0;
				BarPos=46;
				CountOfFinishedTasks=0;
				SetState("waiting");
				CountOfTasks=tasks.size();
				CountOfRoutes=0;				
				double TimeInterval=GetDelay(Robot_MeanDelayOrMinDelay,Robot_MaxDelayOrDeviation,Robot_DelayDistribution);
				AverageDelay+=TimeInterval;
				CountOfDelays++;
				TimeForOneTask+=TimeInterval;
				AverageTimeForOneTask+=TimeInterval;
				SetNextTime(TimeInterval);
				CurrentPosition=0;
			}
		}
	}
	else
	{
		if(TheShortestRoute.size()==0)
		{
			if(TaskIndex>0 && tasks[TaskIndex]->performer==0)
			{
				result+="RETURNING to the previous blocks started\n========================================\n";
				TaskIndex=0;
				CountOfReturnings++;
			}
			else
				if(TaskIndex==0 && tasks[TaskIndex]->performer==0)
				{
					result+="the process DISPOSE started\n========================================\n";
					SetState("DISPOSE");
				}
				else
					SetState("proc. 2");
			TotalDistance=GetTheShortestRoute(matrix,NamesOfWorkshops.size(),CurrentPosition,tasks[TaskIndex]->performer,&TheShortestRoute);
			TraversedTotalDistance=0.0;
			CountOfRoutes=TheShortestRoute.size()-1;
			CountOfTraversedRoutes=1;
			CurrentDistance=matrix[CurrentPosition][TheShortestRoute[CountOfTraversedRoutes]];
			TraversedCurrentDistance=0.0;
			percent=0.0;
			BarProgress=0.0;
			BarPos=46;			
			result+="Moving to the workshop "+to_string(CountOfFinishedTasks+1)+"/"+to_string(CountOfTasks)+" started. Total distance: "+ConvertDoubleToString(TotalDistance)+"; route:\n";
			int i;			
			for(i=0; i<CountOfRoutes; i++)
				result+=NamesOfWorkshops[TheShortestRoute[i]]+"->";
			result+=NamesOfWorkshops[TheShortestRoute[i]];
			result+="\nALL ROUTES:\n";
			for(i=1; i<TheShortestRoute.size(); i++)
				result+=NamesOfWorkshops[TheShortestRoute[i-1]]+" -> "+NamesOfWorkshops[TheShortestRoute[i]]+": "+ConvertDoubleToString(matrix[TheShortestRoute[i-1]][TheShortestRoute[i]])+"\n";
			result+="------------------------------------------------------------------------------------------\n";
			result+="Moving along the route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CountOfRoutes)+" "+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes-1]]+"->"+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes]]+" with the distance "+ConvertDoubleToString(CurrentDistance)+" started";
			location="route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CountOfRoutes)+" "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance);
			TimeForOneTask+=MovementTime;
			AverageTimeForOneTask+=MovementTime;
			ActiveTime+=MovementTime;
			SetNextTime(MovementTime);			
		}
		else
		{
			if(TraversedCurrentDistance<CurrentDistance)
			{
				double NewDistance=TraversedCurrentDistance+Robot_StepSize;
				if(NewDistance<CurrentDistance)
				{
					TraversedCurrentDistance=NewDistance;
					TraversedTotalDistance+=Robot_StepSize;
					ActiveTime+=MovementTime;
					TimeForOneTask+=MovementTime;
					AverageTimeForOneTask+=MovementTime;
					SetNextTime(MovementTime);					
				}
				else
				{
					double NewStepSize=Robot_StepSize-(NewDistance-CurrentDistance);
					TraversedCurrentDistance=CurrentDistance;
					TraversedTotalDistance+=NewStepSize;
					NewStepSize=(MovementTime/100.0)*((NewStepSize*100.0)/Robot_StepSize);
					ActiveTime+=NewStepSize;
					TimeForOneTask+=NewStepSize;
					AverageTimeForOneTask+=NewStepSize;
					SetNextTime(NewStepSize);					
				}
				result+="the total distance "+ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance)+"\nalong the route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CountOfRoutes)+" "+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes-1]]+"->"+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes]]+" (dist. "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance)+") was gone";
				location="route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CountOfRoutes)+" "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance);
			}
			else
			{
				CurrentPosition=TheShortestRoute[CountOfTraversedRoutes];
				TraversedCurrentDistance=0.0;
				if(CountOfTraversedRoutes<CountOfRoutes)
				{
					CountOfTraversedRoutes++;				
					CurrentDistance=matrix[CurrentPosition][TheShortestRoute[CountOfTraversedRoutes]];
					result+="the total distance "+ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance)+"\nalong the route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CountOfRoutes)+" "+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes-1]]+"->"+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes]]+" (dist. "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance)+") was gone";
					location="route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CountOfRoutes)+" "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance);
					ActiveTime+=MovementTime;
					TimeForOneTask+=MovementTime;
					AverageTimeForOneTask+=MovementTime;
					SetNextTime(MovementTime);					
				}
				else
				{
					result+="finishing of the task "+to_string(CountOfFinishedTasks+1)+"/"+to_string(CountOfTasks)+" "+NamesOfWorkshops[TheShortestRoute[0]]+"->"+NamesOfWorkshops[tasks[TaskIndex]->performer]+":\n";
					location="route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CountOfRoutes)+" "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance);
					CountOfTraversedRoutes=CountOfRoutes;
					CurrentPosition=tasks[TaskIndex]->performer;
					CountsOfAttempts[tasks[TaskIndex]->performer]++;
					bool AddingResult=true;					
					if(tasks[TaskIndex]->performer==0)
						AddingResult=creator->AddTask(GetIndex());
					else
						AddingResult=workshops[tasks[TaskIndex]->performer]->AddTask(GetIndex(),tasks[TaskIndex]->WorkTime);
					if(AddingResult==true)
					{
						if(tasks[TaskIndex]->performer==0)						
							result+="the process DISPOSE was finished";
						else						
							result+="the task was added to the workshop "+NamesOfWorkshops[tasks[TaskIndex]->performer];						
						TotalCountOfFinishedTasks++;
						location=NamesOfWorkshops[tasks[TaskIndex]->performer];
						tasks.erase(tasks.begin()+TaskIndex);
						TimeForOneTask=0.0;
						CountOfFinishedTasks++;						
						SetState("waiting");						
						SetNextTime(DBL_MAX);
					}
					else
					{
						if(CountsOfAttempts[tasks[TaskIndex]->performer]==3)
						{
							result+="after 3 attempts to enter the workshop "+NamesOfWorkshops[tasks[TaskIndex]->performer]+" seems to be unachievable\nand was REMOVED";
							tasks.erase(tasks.begin()+TaskIndex);
							IncreaseCountOfFailures();
							CountOfFinishedTasks++;
						}
						else
						{
							result+="the workshop "+NamesOfWorkshops[tasks[TaskIndex]->performer]+" was missed";
							TaskIndex++;						
						}
						ActiveTime+=MovementTime;
						TimeForOneTask+=MovementTime;
						AverageTimeForOneTask+=MovementTime;
						SetNextTime(MovementTime);						
					}
					TheShortestRoute.clear();
				}
			}
		}
		percent=(TraversedTotalDistance*100.0)/TotalDistance;
	}
	device::WriteToFile(result);
	return result;
}
void robot::UpdateDataOnScreen()
{
	int NewCountOfFinishedTasks;
	if(CountOfFinishedTasks<0)
		NewCountOfFinishedTasks=0;
	else
		NewCountOfFinishedTasks=CountOfFinishedTasks;
	if(location=="creator")
	{
		if(GetState()=="waiting")		
			ChangeOutputOnScreenString(GetLineNumber(),GetColumnNumber(),GetState()+"|"+AddSpacesToString(to_string(NewCountOfFinishedTasks)+"/"+to_string(tasks.size()),7)+"|"+AddSpacesToString(to_string(GetCountOfFailures()),4)+"|"+AddSpacesToString(ConvertDoubleToString(percent)+"%",15)+"|                |"+AddSpacesToString(location,28));
		else
		{
			ChangeOutputOnScreenString(GetLineNumber(),GetColumnNumber(),GetState()+"|"+AddSpacesToString(to_string(NewCountOfFinishedTasks)+"/"+to_string(tasks.size()),7)+"|"+AddSpacesToString(to_string(GetCountOfFailures()),4)+"|"+AddSpacesToString(ConvertDoubleToString(percent)+"%",15)+"|");
			while(BarProgress<100.0 && BarProgress<percent)
			{
				BarProgress+=BarStep;
				ChangeOutputOnScreenChar(GetLineNumber(),BarPos,'|');
				BarPos++;
			}
		}
	}
	else
	{
		if(TheShortestRoute.size()==0)
			ChangeOutputOnScreenString(GetLineNumber(),GetColumnNumber(),GetState()+"|"+AddSpacesToString(to_string(NewCountOfFinishedTasks)+"/"+to_string(CountOfTasks),7)+"|"+AddSpacesToString(to_string(GetCountOfFailures()),4)+"|"+AddSpacesToString(ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance),15)+"|                |"+AddSpacesToString(location,28));
		else
		{
			ChangeOutputOnScreenString(GetLineNumber(),GetColumnNumber(),GetState()+"|"+AddSpacesToString(to_string(NewCountOfFinishedTasks)+"/"+to_string(CountOfTasks),7)+"|"+AddSpacesToString(to_string(GetCountOfFailures()),4)+"|"+AddSpacesToString(ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance),15));
			while(BarProgress<100.0 && BarProgress<percent)
			{
				BarProgress+=BarStep;
				ChangeOutputOnScreenChar(GetLineNumber(),BarPos,'|');
				BarPos++;
			}
			ChangeOutputOnScreenString(GetLineNumber(),63,AddSpacesToString(location,28));
		}
	}
}