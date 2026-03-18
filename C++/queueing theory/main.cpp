#include "headers/SharedFunctions.h"
#include "headers/model.h"
COORD ScreenCoordinates;
HANDLE console;
//--------------------CREATOR--------------------
char Creator_DelayDistribution;
double Creator_MeanDelayOrMinDelay,Creator_MaxDelayOrDeviation,Creator_MinTaskTime,Creator_MaxTaskTime;
int Creator_MaxQueue,MinTaskComplexity,MaxTaskComplexity;
//--------------------WORKSHOP--------------------
vector<string> NamesOfWorkshops;
int CountOfWorkshops,Workshop_MaxCountOfIdDigits,*IndexesOfWorkshops,Workshop_MinSizeOfQueueOfRobots,Workshop_MaxSizeOfQueueOfRobots,Workshop_MinCountOfBreakdowns,Workshop_MaxCountOfBreakdowns;
char Workshop_DelayDistribution;
double Workshop_MeanDelayOrMinDelay,Workshop_MaxDelayOrDeviation,Workshop_MinReliability,Workshop_MaxReliability;
//--------------------ROUTE--------------------
double **matrix;
//--------------------ROBOT--------------------
int CountOfRobots,Robot_MinCountOfBreakdowns,Robot_MaxCountOfBreakdowns;
char Robot_DelayDistribution;
double Robot_MeanDelayOrMinDelay,Robot_MaxDelayOrDeviation,Robot_MinMovementTime,Robot_MaxMovementTime,Robot_MinTaskTime,Robot_MaxTaskTime,Robot_MinReliability,Robot_MaxReliability,Robot_StepSize;
//---------------------------------------------
double SimulationTime,CurrentTime;
int CountOfAllDevices,LastLineNumber;
ofstream File_AllEvents,CreatorStatistics,RobotStatistics,WorkshopStatistics;
//----------TEST ROBOT WITH RETURNING TO THE PREVIOUS BLOCKS----------
string location,state="proc. 2";
int TaskNumber,CountOfTasks,CountOfFinishedTasks,TaskIndex,CountOfFailures=0;
int LineNumber=1,ColumnNumber=9,BarSize,BarPos;
int CurrentPosition,CountOfRoutes,CountOfTraversedRoutes;
double MovementTime,percent,BarStep,BarProgress;
double TotalDistance,TraversedTotalDistance,CurrentDistance,TraversedCurrentDistance;
struct task
{
	int performer;
	double WorkTime;
};
vector<struct task*> tasks;
vector<int> TheShortestRoute;
bool* states;
char* CountsOfAttempts;
void IncreaseCountOfFailures(){CountOfFailures++;}
bool AddTask(int NewId,double NewWorkTime)
{
	return states[NewId];
}
string TestRobot()
{
	string result="Robot 00: ";
	if(TheShortestRoute.size()==0)
	{
		if(TaskIndex>0 && tasks[TaskIndex]->performer==0)
		{
			result+="RETURNING to the previous blocks started\n========================================\n";
			TaskIndex=0;
		}
		else
			if(TaskIndex==0 && tasks[TaskIndex]->performer==0)
			{
				result+="the process DISPOSE started\n========================================\n";
				state="DISPOSE";
			}
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
		//SetState("proc. 2");
		//SetNextTime(MovementTime);
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
				//SetNextTime(MovementTime);
			}
			else
			{
				double NewStepSize=Robot_StepSize-(NewDistance-CurrentDistance);
				//TraversedCurrentDistance+=NewStepSize;
				TraversedCurrentDistance=CurrentDistance;
				TraversedTotalDistance+=NewStepSize;
				//SetNextTime((MovementTime/100.0)*((NewStepSize*100.0)/Robot_StepSize));
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
			}
			else						
			{
				//TraversedTotalDistance=TotalDistance;
				result+="finishing of the task "+to_string(CountOfFinishedTasks+1)+"/"+to_string(CountOfTasks)+" "+NamesOfWorkshops[TheShortestRoute[0]]+"->"+NamesOfWorkshops[tasks[TaskIndex]->performer]+":\n";
				location="route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CountOfRoutes)+" "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance);
				CountOfTraversedRoutes=CountOfRoutes;
				CurrentPosition=tasks[TaskIndex]->performer;
				CountsOfAttempts[tasks[TaskIndex]->performer]++;
				if(AddTask(tasks[TaskIndex]->performer,tasks[TaskIndex]->WorkTime))
				{
					result+="the task was added to the workshop "+NamesOfWorkshops[tasks[TaskIndex]->performer];
					location=NamesOfWorkshops[tasks[TaskIndex]->performer];
					tasks.erase(tasks.begin()+TaskIndex);
					CountOfFinishedTasks++;					
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
				}
				TheShortestRoute.clear();
			}
		}
	}
	percent=(TraversedTotalDistance*100.0)/TotalDistance;
	return result;
}
void UpdateDataOnScreen()
{
	if(TheShortestRoute.size()==0)
		ChangeOutputOnScreenString(LineNumber,ColumnNumber,state+"|"+AddSpacesToString(to_string(CountOfFinishedTasks)+"/"+to_string(CountOfTasks),7)+"|"+AddSpacesToString(to_string(CountOfFailures),4)+"|"+AddSpacesToString(ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance),15)+"|                |"+AddSpacesToString(location,28));
	else
	{
		ChangeOutputOnScreenString(LineNumber,ColumnNumber,state+"|"+AddSpacesToString(to_string(CountOfFinishedTasks)+"/"+to_string(CountOfTasks),7)+"|"+AddSpacesToString(to_string(CountOfFailures),4)+"|"+AddSpacesToString(ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance),15));
		while(BarProgress<100.0 && BarProgress<percent)
		{
			BarProgress+=BarStep;
			ChangeOutputOnScreenChar(LineNumber,BarPos,'|');
			BarPos++;
		}
		ChangeOutputOnScreenString(LineNumber,63,AddSpacesToString(location,28));
	}
}
//----------TEST END----------
int main(void)
{
	struct route
	{
		string departure,destination;
		double distance;
	};	
	vector<route> routes;
	srand(time(0));
	cout.precision(2);
	cout.setf(ios::fixed);
	fstream MapFile("MapOfWorkshops.csv");	
	route NewRoute;	
	string FileLine,NewWorkshop,DistanceString;
	char DepartureFound,DestinationFound;	
	int i,j,DepartureIndex,DestinationIndex,MinInt,MaxInt,PrevInt;
	while(getline(MapFile,FileLine))
	{		
		for(i=0; FileLine[i]!=';'; i++)
			NewRoute.departure+=FileLine[i];
		for(i++; FileLine[i]!=';'; i++)
			NewRoute.destination+=FileLine[i];
		for(i++; i<FileLine.length(); i++)
			DistanceString+=FileLine[i];
		NewRoute.distance=stod(DistanceString);				
		for(i=0,DepartureFound=0,DestinationFound=0; i<NamesOfWorkshops.size(); i++)
			if(NamesOfWorkshops[i]==NewRoute.departure)			
				DepartureFound=1;			
			else
				if(NamesOfWorkshops[i]==NewRoute.destination)
					DestinationFound=1;
		if(DepartureFound==0)
		{
			NewWorkshop=NewRoute.departure;
			NamesOfWorkshops.push_back(NewWorkshop);
		}
		if(DestinationFound==0)
		{
			NewWorkshop=NewRoute.destination;
			NamesOfWorkshops.push_back(NewWorkshop);
		}
		routes.push_back(NewRoute);
		NewRoute.departure="";
		NewRoute.destination="";
		DistanceString="";
	}
	MapFile.close();	
	sort(NamesOfWorkshops.begin(),NamesOfWorkshops.end());
	matrix=new double*[NamesOfWorkshops.size()];	
	for(i=0,DepartureIndex=3; i<NamesOfWorkshops.size(); i++)
	{
		matrix[i]=new double[NamesOfWorkshops.size()];
		for(j=0; j<NamesOfWorkshops.size(); j++)
			matrix[i][j]=0.0;
		if(i%2==0)
			DepartureIndex++;
	}
	IndexesOfWorkshops=new int[NamesOfWorkshops.size()-1];
	for(i=1; i<NamesOfWorkshops.size(); i++)	
		IndexesOfWorkshops[i-1]=i;
	for(i=0,Robot_StepSize=1000.0; i<routes.size(); i++)
	{
		for(DepartureIndex=0; NamesOfWorkshops[DepartureIndex]!=routes[i].departure; DepartureIndex++);
		for(DestinationIndex=0; NamesOfWorkshops[DestinationIndex]!=routes[i].destination; DestinationIndex++);
		matrix[DepartureIndex][DestinationIndex]=routes[i].distance/10;
		if(matrix[DepartureIndex][DestinationIndex]<Robot_StepSize)
			Robot_StepSize=matrix[DepartureIndex][DestinationIndex];
	}
	console=GetStdHandle(STD_OUTPUT_HANDLE);
	//----------TEST ROBOT WITH RETURNING TO THE PREVIOUS BLOCKS----------
	/*cout<<" ROBOT  | STATE | TASKS |FAIL|   PROGRESS    |                |      CURRENT LOCATION      ";
	cout<<"   00   |waiting|       | 0  |               |                |                            ";
	CountOfWorkshops=NamesOfWorkshops.size()-1;
	MovementTime=5.0;
	FisherYatesShuffle(IndexesOfWorkshops,CountOfWorkshops);
	CountOfTasks=5;
	CountOfFinishedTasks=0;
	states=new bool[CountOfWorkshops];
	CountsOfAttempts=new char[CountOfWorkshops];
	for(i=0; i<CountOfWorkshops; i++)
		CountsOfAttempts[i]=0;
	for(i=0; i<CountOfTasks; i++)
	{
		struct task* NewTask=new struct task;
		NewTask->performer=IndexesOfWorkshops[i];
		NewTask->WorkTime=10.0;
		tasks.push_back(NewTask);
		if(i%2==0)
			states[tasks[i]->performer]=false;
		else
			states[tasks[i]->performer]=true;
	}
	tasks[CountOfTasks-1]->performer=0;	
	string result;
	TaskIndex=0;
	CurrentPosition=0;
	CurrentDistance=0.0;
	CountOfRoutes=0;
	percent=0.0;	
	BarPos=46;
	BarSize=16;	
	BarProgress=0.0;
	BarStep=100.0/BarSize;
	while(tasks.size()>0)
	{
		result=TestRobot();
		ChangeOutputOnScreenString(2,0,result);
		getchar();
		//Sleep(10);
		for(i=2; i<20; i++)
			ChangeOutputOnScreenString(i,0,"                                                                                           ");
		UpdateDataOnScreen();
	}*/
	//----------TEST END----------	
	SimulationTime=1000.0;
	CountOfRobots=10;
	Creator_DelayDistribution='e';
	Creator_MeanDelayOrMinDelay=GetRandomDouble(100.0,200.0);
	Creator_MaxDelayOrDeviation=0.0;
	Creator_MinTaskTime=1.0;
	Creator_MaxTaskTime=5.0;
	Creator_MaxQueue=GetRandomInt(CountOfRobots/2,CountOfRobots*3);
	MinTaskComplexity=2;
	MaxTaskComplexity=NamesOfWorkshops.size()-1;
	//-------------------------------------------
	CountOfWorkshops=NamesOfWorkshops.size();
	Workshop_MaxCountOfIdDigits=GetCountOfDigits(CountOfWorkshops);
	Workshop_MinSizeOfQueueOfRobots=2;
	Workshop_MaxSizeOfQueueOfRobots=5;
	Workshop_DelayDistribution='e';
	Workshop_MeanDelayOrMinDelay=GetRandomDouble(10.0,20.0);
	Workshop_MaxDelayOrDeviation=0.0;
	Workshop_MinCountOfBreakdowns=5;
	Workshop_MaxCountOfBreakdowns=10;
	Workshop_MinReliability=0.75;
	Workshop_MaxReliability=0.9;
	//-------------------------------------------	
	Robot_DelayDistribution='e';
	Robot_MeanDelayOrMinDelay=GetRandomDouble(2.0,5.0);
	Robot_MaxDelayOrDeviation=0.0;
	Robot_MinMovementTime=1.0;
	Robot_MaxMovementTime=5.0;
	Robot_MinTaskTime=0.5;
	Robot_MaxTaskTime=2.0;
	Robot_MinCountOfBreakdowns=5;
	Robot_MaxCountOfBreakdowns=10;
	Robot_MinReliability=0.8;
	Robot_MaxReliability=0.95;
	CountOfAllDevices=1+CountOfWorkshops+CountOfRobots;
	LastLineNumber=NamesOfWorkshops.size()/2+CountOfRobots+5;	
	mkdir("logs");
	File_AllEvents.open("logs/AllEvents.txt");
	File_AllEvents.precision(2);
	File_AllEvents.setf(ios::fixed);
	CreatorStatistics.open("creator.csv");
	CreatorStatistics.precision(2);
	CreatorStatistics.setf(ios::fixed);
	RobotStatistics.open("robot.csv");
	RobotStatistics.precision(2);
	RobotStatistics.setf(ios::fixed);
	WorkshopStatistics.open("workshop.csv");
	WorkshopStatistics.precision(2);
	WorkshopStatistics.setf(ios::fixed);	
/*
Changing parameter: mean delay (exponential distribution);;;;;;
Mean delay   ;Max. delay  ;Size of;Avg. ;Avg. task ;Avg. time   ;Avg.  ;Count of
or min. delay;or deviation;storage;delay;complexity;for one task;load %;failures

Mean delay   ;Max. delay  ;Avg.   ;Avg. ;Avg. time   ;Avg.;Avg. count;Avg. Percentage of ;Avg. count
or min. delay;or deviation;reliab.;delay;for one task;load %;of tasks  ;finished tasks     ;of returnings

Mean delay   ;Max. delay  ;Avg.   ;Avg. size;Avg. max. count   ;Avg. ;Avg.  ;Avg. count;Avg. percentage
or min. delay;or deviation;reliab.;of queue ;of robots in queue;delay;load %;of tasks  ;of finished tasks
*/
	int NumberOfExperiment=1,CountOfOneTypeExperiments=10;
	int TotalCountOfExperiments=CountOfOneTypeExperiments*5+1;
	double Creator_MinDelay=25.0,Creator_MaxDelay=50.0;	
	double Robot_MinDelay=1.0,Robot_MaxDelay=5.0;	
	double Workshop_MinDelay=2.0,Workshop_MaxDelay=7.0;
	string NameOfVariable="mean delay (exponential distribution)";
	CreatorStatistics<<"Changing parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Size of;Avg. ;Avg. task ;Avg. time   ;Avg.  ;Count of\nor min. delay;or deviation;storage;delay;complexity;for one task;load %;failures";
	RobotStatistics<<"Changing parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Avg.   ;Avg. ;Avg. time   ;Avg.;Avg. count;Avg. Percentage of ;Avg. count\nor min. delay;or deviation;reliab.;delay;for one task;load %;of tasks  ;finished tasks     ;of returnings";
	WorkshopStatistics<<"Changing parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Avg.   ;Avg. size;Avg. max. count   ;Avg. ;Avg.  ;Avg. count;Avg. percentage\nor min. delay;or deviation;reliab.;of queue ;of robots in queue;delay;load %;of tasks  ;of finished tasks";	
	for(i=0; i<CountOfOneTypeExperiments; i++,NumberOfExperiment++)
	{
		cout<<"Experiment "<<NumberOfExperiment<<"/"<<TotalCountOfExperiments<<"; changing parameter: "<<NameOfVariable<<"\n";
		Creator_MeanDelayOrMinDelay=GetRandomDouble(Creator_MinDelay,Creator_MaxDelay);
		Robot_MeanDelayOrMinDelay=GetRandomDouble(Robot_MinDelay,Robot_MaxDelay);
		Workshop_MeanDelayOrMinDelay=GetRandomDouble(Workshop_MinDelay,Workshop_MaxDelay);
		model();
		Creator_MinDelay+=25.0;
		Creator_MaxDelay+=25.0;
		Robot_MinDelay+=10.0;
		Robot_MaxDelay+=10;0;
		Workshop_MinDelay+=20.0;
		Workshop_MaxDelay+=20.0;
	}
	Creator_MinDelay=25.0;
	Creator_MaxDelay=50.0;	
	Robot_MinDelay=1.0;
	Robot_MaxDelay=5.0;
	Workshop_MinDelay=2.0;
	Workshop_MaxDelay=7.0;
	double Creator_MinDeviation=Creator_MinDelay/2.0,Creator_MaxDeviation=Creator_MaxDelay/2;
	double Robot_MinDeviation=Robot_MinDelay/3,Robot_MaxDeviation=Robot_MaxDelay/3;
	double Workshop_MinDeviation=Workshop_MinDelay/3,Workshop_MaxDeviation=Workshop_MaxDelay/3;
	Creator_DelayDistribution='u';
	Robot_DelayDistribution='u';
	Workshop_DelayDistribution='u';
	NameOfVariable="mean delay and deviation (uniform distribution)";
	CreatorStatistics<<"\nChanging parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Size of;Avg. ;Avg. task ;Avg. time   ;Avg.  ;Count of\nor min. delay;or deviation;storage;delay;complexity;for one task;load %;failures";
	RobotStatistics<<"\nChanging parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Avg.   ;Avg. ;Avg. time   ;Avg.;Avg. count;Avg. Percentage of ;Avg. count\nor min. delay;or deviation;reliab.;delay;for one task;load %;of tasks  ;finished tasks     ;of returnings";
	WorkshopStatistics<<"\nChanging parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Avg.   ;Avg. size;Avg. max. count   ;Avg. ;Avg.  ;Avg. count;Avg. percentage\nor min. delay;or deviation;reliab.;of queue ;of robots in queue;delay;load %;of tasks  ;of finished tasks";	
	for(i=0; i<CountOfOneTypeExperiments; i++,NumberOfExperiment++)
	{		
		cout<<"Experiment "<<NumberOfExperiment<<"/"<<TotalCountOfExperiments<<"; changing parameters: "<<NameOfVariable<<"\n";
		Creator_MeanDelayOrMinDelay=GetRandomDouble(Creator_MinDelay,Creator_MaxDelay);
		Robot_MeanDelayOrMinDelay=GetRandomDouble(Robot_MinDelay,Robot_MaxDelay);
		Workshop_MeanDelayOrMinDelay=GetRandomDouble(Workshop_MinDelay,Workshop_MaxDelay);
		Creator_MaxDelayOrDeviation=GetRandomDouble(Creator_MinDeviation,Creator_MaxDeviation);
		Robot_MaxDelayOrDeviation=GetRandomDouble(Robot_MinDeviation,Robot_MaxDeviation);
		Workshop_MaxDelayOrDeviation=GetRandomDouble(Workshop_MinDeviation,Workshop_MaxDeviation);
		model();
		Creator_MinDelay+=25.0;
		Creator_MaxDelay+=25.0;
		Creator_MinDeviation+=12.5;
		Creator_MaxDeviation+=12.5;
		Robot_MinDelay+=10.0;
		Robot_MaxDelay+=10;0;
		Robot_MinDeviation+=5.0;
		Robot_MaxDeviation+=5.0;
		Workshop_MinDelay+=20.0;
		Workshop_MaxDelay+=20.0;
		Workshop_MinDeviation+=10.0;
		Workshop_MaxDeviation+=10.0;
	}
	Creator_MinDelay=25.0;
	Creator_MaxDelay=50.0;	
	Robot_MinDelay=1.0;
	Robot_MaxDelay=5.0;
	Workshop_MinDelay=2.0;
	Workshop_MaxDelay=7.0;	
	Creator_MinDeviation=Creator_MinDelay/2.0;
	Creator_MaxDeviation=Creator_MaxDelay/2;
	Robot_MinDeviation=Robot_MinDelay/3;
	Robot_MaxDeviation=Robot_MaxDelay/3;
	Workshop_MinDeviation=Workshop_MinDelay/3;
	Workshop_MaxDeviation=Workshop_MaxDelay/3;
	Creator_DelayDistribution='n';
	Robot_DelayDistribution='n';
	Workshop_DelayDistribution='n';
	NameOfVariable="mean delay and deviation (normal distribution) ";
	CreatorStatistics<<"\nChanging parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Size of;Avg. ;Avg. task ;Avg. time   ;Avg.  ;Count of\nor min. delay;or deviation;storage;delay;complexity;for one task;load %;failures";
	RobotStatistics<<"\nChanging parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Avg.   ;Avg. ;Avg. time   ;Avg.;Avg. count;Avg. Percentage of ;Avg. count\nor min. delay;or deviation;reliab.;delay;for one task;load %;of tasks  ;finished tasks     ;of returnings";
	WorkshopStatistics<<"\nChanging parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Avg.   ;Avg. size;Avg. max. count   ;Avg. ;Avg.  ;Avg. count;Avg. percentage\nor min. delay;or deviation;reliab.;of queue ;of robots in queue;delay;load %;of tasks  ;of finished tasks";
	for(i=0; i<CountOfOneTypeExperiments; i++,NumberOfExperiment++)
	{		
		cout<<"Experiment "<<NumberOfExperiment<<"/"<<TotalCountOfExperiments<<"; changing parameters: "<<NameOfVariable<<"\n";
		Creator_MeanDelayOrMinDelay=GetRandomDouble(Creator_MinDelay,Creator_MaxDelay);
		Robot_MeanDelayOrMinDelay=GetRandomDouble(Robot_MinDelay,Robot_MaxDelay);
		Workshop_MeanDelayOrMinDelay=GetRandomDouble(Workshop_MinDelay,Workshop_MaxDelay);
		Creator_MaxDelayOrDeviation=GetRandomDouble(Creator_MinDeviation,Creator_MaxDeviation);
		Robot_MaxDelayOrDeviation=GetRandomDouble(Robot_MinDeviation,Robot_MaxDeviation);
		Workshop_MaxDelayOrDeviation=GetRandomDouble(Workshop_MinDeviation,Workshop_MaxDeviation);
		model();
		Creator_MinDelay+=25.0;
		Creator_MaxDelay+=25.0;
		Creator_MinDeviation+=12.5;
		Creator_MaxDeviation+=12.5;
		Robot_MinDelay+=10.0;
		Robot_MaxDelay+=10;0;
		Robot_MaxDeviation+=5.0;
		Robot_MaxDeviation+=5.0;
		Workshop_MinDelay+=20.0;
		Workshop_MaxDelay+=20.0;
		Workshop_MinDeviation+=10.0;
		Workshop_MaxDeviation+=10.0;
	}	
	Creator_MinDelay=25.0;
	Creator_MaxDelay=50.0;	
	Robot_MinDelay=1.0;
	Robot_MaxDelay=5.0;
	Workshop_MinDelay=2.0;
	Workshop_MaxDelay=7.0;	
	Creator_MinDeviation=Creator_MinDelay/2.0;
	Creator_MaxDeviation=Creator_MaxDelay/2;
	Robot_MinDeviation=Robot_MinDelay/3;
	Robot_MaxDeviation=Robot_MaxDelay/3;
	Workshop_MinDeviation=Workshop_MinDelay/3;
	Workshop_MaxDeviation=Workshop_MaxDelay/3;	
	Creator_DelayDistribution='a';
	Robot_DelayDistribution='a';
	Workshop_DelayDistribution='a';
	NameOfVariable="equal delay                                    ";
	CreatorStatistics<<"\nChanging parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Size of;Avg. ;Avg. task ;Avg. time   ;Avg.  ;Count of\nor min. delay;or deviation;storage;delay;complexity;for one task;load %;failures";
	RobotStatistics<<"\nChanging parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Avg.   ;Avg. ;Avg. time   ;Avg.;Avg. count;Avg. Percentage of ;Avg. count\nor min. delay;or deviation;reliab.;delay;for one task;load %;of tasks  ;finished tasks     ;of returnings";
	WorkshopStatistics<<"\nChanging parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Avg.   ;Avg. size;Avg. max. count   ;Avg. ;Avg.  ;Avg. count;Avg. percentage\nor min. delay;or deviation;reliab.;of queue ;of robots in queue;delay;load %;of tasks  ;of finished tasks";
	for(i=0; i<CountOfOneTypeExperiments; i++,NumberOfExperiment++)
	{		
		cout<<"Experiment "<<NumberOfExperiment<<"/"<<TotalCountOfExperiments<<"; changing parameters: "<<NameOfVariable<<"\n";
		Creator_MeanDelayOrMinDelay=GetRandomDouble(Creator_MinDelay,Creator_MaxDelay);
		Robot_MeanDelayOrMinDelay=GetRandomDouble(Robot_MinDelay,Robot_MaxDelay);
		Workshop_MeanDelayOrMinDelay=GetRandomDouble(Workshop_MinDelay,Workshop_MaxDelay);
		Creator_MaxDelayOrDeviation=GetRandomDouble(Creator_MinDeviation,Creator_MaxDeviation);
		Robot_MaxDelayOrDeviation=GetRandomDouble(Robot_MinDeviation,Robot_MaxDeviation);
		Workshop_MaxDelayOrDeviation=GetRandomDouble(Workshop_MinDeviation,Workshop_MaxDeviation);
		model();
		Creator_MinDelay+=25.0;
		Creator_MaxDelay+=25.0;
		Creator_MinDeviation+=12.5;
		Creator_MaxDeviation+=12.5;
		Robot_MinDelay+=10.0;
		Robot_MaxDelay+=10;0;
		Robot_MaxDeviation+=5.0;
		Robot_MaxDeviation+=5.0;
		Workshop_MinDelay+=20.0;
		Workshop_MaxDelay+=20.0;
		Workshop_MinDeviation+=10.0;
		Workshop_MaxDeviation+=10.0;
	}
	Creator_MeanDelayOrMinDelay=GetRandomDouble(100.0,200.0);
	Creator_MaxDelayOrDeviation=0.0;
	Creator_DelayDistribution='e';
	Workshop_MeanDelayOrMinDelay=GetRandomDouble(10.0,20.0);
	Workshop_MaxDelayOrDeviation=0.0;
	Workshop_DelayDistribution='e';
	Robot_DelayDistribution='e';
	Robot_MeanDelayOrMinDelay=GetRandomDouble(2.0,5.0);
	Robot_MaxDelayOrDeviation=0.0;
	NameOfVariable="task complexity";
	CreatorStatistics<<"\nChanging parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Size of;Avg. ;Avg. task ;Avg. time   ;Avg.  ;Count of\nor min. delay;or deviation;storage;delay;complexity;for one task;load %;failures";
	RobotStatistics<<"\nChanging parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Avg.   ;Avg. ;Avg. time   ;Avg.;Avg. count;Avg. Percentage of ;Avg. count\nor min. delay;or deviation;reliab.;delay;for one task;load %;of tasks  ;finished tasks     ;of returnings";
	WorkshopStatistics<<"\nChanging parameter: "+NameOfVariable+";;;;;;\nMean delay   ;Max. delay  ;Avg.   ;Avg. size;Avg. max. count   ;Avg. ;Avg.  ;Avg. count;Avg. percentage\nor min. delay;or deviation;reliab.;of queue ;of robots in queue;delay;load %;of tasks  ;of finished tasks";
	MinTaskComplexity=2;
	MaxTaskComplexity=2;	
	for(i=0; i<CountOfOneTypeExperiments+1; i++,NumberOfExperiment++)
	{		
		cout<<"Experiment "<<NumberOfExperiment<<"/"<<TotalCountOfExperiments<<"; changing parameters: "<<NameOfVariable<<"\n";
		if(i%2==0)
		{
			MinTaskComplexity+=2;
			MaxTaskComplexity+=2;
		}
		else
		{
			MinTaskComplexity+=1;
			MaxTaskComplexity+=1;
		}
		model();
	}	
	File_AllEvents.close();
	CreatorStatistics.close();
	RobotStatistics.close();
	WorkshopStatistics.close();	
	for(i=0; i<NamesOfWorkshops.size(); i++)
		delete(matrix[i]);
	delete(matrix);
	delete(IndexesOfWorkshops);
	ScreenCoordinates.X=0;
	ScreenCoordinates.Y=LastLineNumber;
	SetConsoleCursorPosition(console,ScreenCoordinates);
	return 0;
}