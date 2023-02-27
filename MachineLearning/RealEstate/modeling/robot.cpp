#include "headers/robot.h"
robot::robot(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double reliability,int CountOfBreakdowns,double NewSpeedOfLoading,double NewSpeedOfMovement,device* NewCreator,workshop** NewWorkshops):device(NewClassName,NewId,NewIndex,NewLineNumber,NewColumnNumber,reliability,CountOfBreakdowns)
{	
	location="creator";
	SpeedOfLoading=NewSpeedOfLoading;
	SpeedOfMovement=NewSpeedOfMovement;	
	workshops=NewWorkshops;
	creator=NewCreator;
	CountOfTasks=0;
	CountOfFinishedTasks=0;
	CurrentPosition=0;
	percent=0.0;
	BarProgress=0.0;
	BarSize=16;
	BarStep=100.0/BarSize;
	BarPos=46;
	CurrentPosition=0;
	CountOfVisitedWorkshops=0;	
	cout<<GetState()<<"|"<<AddSpacesToString(to_string(CountOfFinishedTasks)+"/"+to_string(CountOfTasks),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|"<<AddSpacesToString(ConvertDoubleToString(percent)+"%",15)<<"|                |"<<AddSpacesToString(location,28);
	CountOfFinishedTasks=-1;	
	SetNextTime(SimulationTime);
}
robot::~robot(){}
bool robot::AddTask(int workshop,double WorkTime)
{
	struct task* NewTask=new task();	
	NewTask->performer=workshop;
	NewTask->WorkTime=WorkTime;
	tasks.push_back(NewTask);
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
			SetState("PROC. 1");
			CountOfFinishedTasks=0;
			result=result+"Loading of "+to_string(tasks.size())+" tasks started";
			SetNextTime(SpeedOfLoading);
		}
		else
		{
			if(CountOfFinishedTasks<tasks.size())
			{
				CountOfFinishedTasks++;
				percent=(CountOfFinishedTasks*100.0)/tasks.size();
				result=result+" The task "+to_string(CountOfFinishedTasks)+" ("+NamesOfWorkshops[tasks[CountOfFinishedTasks-1]->performer]+": "+ConvertDoubleToString(tasks[CountOfFinishedTasks-1]->WorkTime)+") of "+to_string(tasks.size())+" was added";
				SetNextTime(SpeedOfLoading);
			}
			else
			{
				result=result+"Loading of "+to_string(CountOfFinishedTasks)+" tasks was finished";
				percent=0.0;
				BarProgress=0.0;
				BarPos=46;
				CountOfFinishedTasks=0;
				SetState("waiting");
				CountOfTasks=tasks.size();
				CurCountOfRoutes=0;
				//SetNextTime(SimulationTime);
				SetNextTime(GetDelay(Robot_MeanDelayOrMinDelay,Robot_MaxDelayOrDeviation,Robot_DelayDistribution));
				CountOfVisitedWorkshops=0;
				CurrentPosition=0;
			}
		}
	}
	else
		if(TheShortestRoute.size()==0)
		{
			TotalDistance=GetTheShortestRoute(matrix,NamesOfWorkshops.size(),CurrentPosition,tasks[CountOfVisitedWorkshops]->performer,&TheShortestRoute);
			TraversedTotalDistance=0.0;
			CurCountOfRoutes=TheShortestRoute.size()-1;
			CountOfTraversedRoutes=1;			
			CurrentDistance=matrix[CurrentPosition][TheShortestRoute[CountOfTraversedRoutes]];
			TraversedCurrentDistance=0.0;
			percent=0.0;
			BarProgress=0.0;
			BarPos=46;			
			result+="Moving to the workshop "+to_string(CountOfVisitedWorkshops+1)+"/"+to_string(CountOfTasks)+" started. Total distance: "+ConvertDoubleToString(TotalDistance)+"; route:\n";			
			int i;			
			for(i=0; i<CurCountOfRoutes; i++)
				result+=NamesOfWorkshops[TheShortestRoute[i]]+"->";
			result+=NamesOfWorkshops[TheShortestRoute[i]];
			result+="\nALL ROUTES:\n";
			for(i=1; i<TheShortestRoute.size(); i++)
				result+=NamesOfWorkshops[TheShortestRoute[i-1]]+" -> "+NamesOfWorkshops[TheShortestRoute[i]]+": "+ConvertDoubleToString(matrix[TheShortestRoute[i-1]][TheShortestRoute[i]])+"\n";
			result+="------------------------------------------------------------------------------------------\n";
			result+="Moving along the route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CurCountOfRoutes)+" "+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes-1]]+"->"+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes]]+" with the distance "+ConvertDoubleToString(CurrentDistance)+" started";
			location="route";
			SetNextTime(SpeedOfMovement);
		}
		else
		{
			if(TraversedTotalDistance<TotalDistance)
			{
				if(TraversedCurrentDistance<CurrentDistance)
				{
					double NewDistance=TraversedCurrentDistance+Robot_StepSize;
					if(NewDistance<CurrentDistance)
					{
						TraversedCurrentDistance=NewDistance;
						TraversedTotalDistance+=Robot_StepSize;
						SetNextTime(SpeedOfMovement);
					}
					else
					{
						double NewStepSize=Robot_StepSize-(NewDistance-CurrentDistance);
						TraversedCurrentDistance+=NewStepSize;
						TraversedTotalDistance+=NewStepSize;
						SetNextTime((SpeedOfMovement/100.0)*((NewStepSize*100.0)/Robot_StepSize));
					}
				}
				else
				{
					CurrentPosition=TheShortestRoute[CountOfTraversedRoutes];				
					if(CountOfTraversedRoutes<CurCountOfRoutes)
					{
						CountOfTraversedRoutes++;
						TraversedCurrentDistance=0.0;
						CurrentDistance=matrix[CurrentPosition][TheShortestRoute[CountOfTraversedRoutes]];
					}
					else
						TraversedTotalDistance=TotalDistance;
					SetNextTime(SpeedOfMovement);
				}
				result+="the common distance "+ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance)+"\nalong the route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CurCountOfRoutes)+" "+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes-1]]+"->"+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes]]+" (dist. "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance)+") was gone";
				//SetNextTime(SpeedOfMovement);
			}
			else
			{				
				if(workshops[tasks[CountOfVisitedWorkshops]->performer]->AddTask(GetIndex(),tasks[CountOfVisitedWorkshops]->WorkTime))
				{
					result+="the task was added to the workshop"+to_string(tasks[CountOfVisitedWorkshops]->performer);
					CountOfVisitedWorkshops++;
					SetNextTime(SimulationTime);
					location=NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes]];
				}
				else
				{
					SetNextTime(SpeedOfMovement);
					result+="The workshop "+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes]]+" was MISSED";
				}
				CountOfVisitedWorkshops++;
				TheShortestRoute.clear();
			}
		}
	return result;
}
void robot::UpdateDataOnScreen()
{
	ScreenCoordinates.X=GetColumnNumber();
	ScreenCoordinates.Y=GetLineNumber();
	SetConsoleCursorPosition(console,ScreenCoordinates);
	if(location=="creator")
	{
		if(GetState()=="waiting")		
			cout<<GetState()<<"|"<<AddSpacesToString(to_string(CountOfFinishedTasks)+"/"+to_string(tasks.size()),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|"<<AddSpacesToString(ConvertDoubleToString(percent)+"%",15)<<"|                |"<<AddSpacesToString(location,28);
		else
		{
			cout<<GetState()<<"|"<<AddSpacesToString(to_string(CountOfFinishedTasks)+"/"+to_string(tasks.size()),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|"<<AddSpacesToString(ConvertDoubleToString(percent)+"%",15)<<"|";
			while(BarProgress<100.0 && BarProgress<percent)
			{
				BarProgress+=BarStep;
				ChangeOutputOnScreenChar(GetLineNumber(),BarPos,'|');
				BarPos++;
			}
		}
	}
	else
		if(location=="route")
		{
			if(TraversedTotalDistance==0.0)
				ChangeOutputOnScreenString(GetLineNumber(),GetColumnNumber(),"proc. 2|"+AddSpacesToString(to_string(CountOfVisitedWorkshops)+"/"+to_string(CountOfTasks+1),7)+"|"+AddSpacesToString(to_string(GetCountOfFailures()),4)+"|"+AddSpacesToString(ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance),15)+"|                |"+AddSpacesToString("route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CurCountOfRoutes)+" "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance),28));
			else
			{
				ChangeOutputOnScreenString(GetLineNumber(),GetColumnNumber(),"proc. 2|"+AddSpacesToString(to_string(CountOfVisitedWorkshops)+"/"+to_string(CountOfTasks+1),7)+"|"+AddSpacesToString(to_string(GetCountOfFailures()),4)+"|"+AddSpacesToString(ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance),15));
				while(BarProgress<100.0 && BarProgress<percent)
				{
					BarProgress+=BarStep;
					ChangeOutputOnScreenChar(GetLineNumber(),BarPos,'|');
					BarPos++;
				}
				ChangeOutputOnScreenString(GetLineNumber(),63,AddSpacesToString("route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CurCountOfRoutes)+" "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance),28));
			}
		}
		else
			ChangeOutputOnScreenString(GetLineNumber(),GetColumnNumber(),"proc. 2|"+AddSpacesToString(to_string(CountOfVisitedWorkshops)+"/"+to_string(CountOfTasks+1),7)+"|"+AddSpacesToString(to_string(GetCountOfFailures()),4)+"|"+AddSpacesToString(ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance),15)+"|                |"+AddSpacesToString(location,28));
}