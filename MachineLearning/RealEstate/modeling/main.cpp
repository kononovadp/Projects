#include "headers/SharedFunctions.h"
#include "headers/model.h"
COORD ScreenCoordinates;
HANDLE console;
//--------------------CREATOR--------------------
char Creator_DelayDistribution;
double Creator_MeanDelayOrMinDelay,Creator_MaxDelayOrDeviation,Creator_MinSpeed,Creator_MaxSpeed;
int Creator_MaxQueue,MinTaskComplexity,MaxTaskComplexity;
//--------------------WORKSHOP--------------------
vector<string> NamesOfWorkshops;
int CountOfWorkshops,Workshop_MaxCountOfIdDigits,*IndexesOfWorkshops,Workshop_MinSizeOfQueueOfRobots,Workshop_MaxSizeOfQueueOfRobots,Workshop_MinCountOfBreakdowns,Workshop_MaxCountOfBreakdowns;
char Workshop_DelayDistribution;
double Workshop_MeanDelayOrMinDelay,Workshop_MaxDelayOrDeviation,Workshop_MinSpeed,Workshop_MaxSpeed,Workshop_MinReliability,Workshop_MaxReliability;
//--------------------ROUTE--------------------
double **matrix,Route_MinReliability,Route_MaxReliability;
int CountOfRoutes,Route_MinSizeOfQueueOfRobots,Route_MaxSizeOfQueueOfRobots,Route_MinCountOfBreakdowns,Route_MaxCountOfBreakdowns;
//--------------------ROBOT--------------------
int CountOfRobots,Robot_MinCountOfBreakdowns,Robot_MaxCountOfBreakdowns;
char Robot_DelayDistribution;
double Robot_MeanDelayOrMinDelay,Robot_MaxDelayOrDeviation,Robot_MinSpeedOfMovement,Robot_MaxSpeedOfMovement,Robot_MinSpeedOfLoading,Robot_MaxSpeedOfLoading,Robot_MinReliability,Robot_MaxReliability,Robot_StepSize;
//---------------------------------------------
double SimulationTime,CurrentTime;
int CountOfAllDevices,LastLineNumber;
//ofstream TempFile;
//---------------------------------------------
//--------------------temp--------------------
int CountOfTasks,CountOfVisitedWorkshops,CountOfFailures=0;
int LineNumber=1,ColumnNumber=9,BarSize,BarPos;
int CurrentPosition,/*CountOfRoutes,*/CountOfTraversedRoutes;
double SpeedOfMovement,percent,BarStep,BarProgress;
double TotalDistance,TraversedTotalDistance,CurrentDistance,TraversedCurrentDistance;
vector<int> tasks;
vector<int> TheShortestRoute;
string TestRobot()
{
	string result="Robot 00: ";
	if(TheShortestRoute.size()==0)
	{
		TotalDistance=GetTheShortestRoute(matrix,NamesOfWorkshops.size(),CurrentPosition,tasks[CountOfVisitedWorkshops],&TheShortestRoute);
		TraversedTotalDistance=0.0;
		CountOfRoutes=TheShortestRoute.size()-1;
		CountOfTraversedRoutes=1;		
		percent=0.0;
		BarProgress=0.0;
		BarPos=46;
		CurrentDistance=matrix[CurrentPosition][TheShortestRoute[CountOfTraversedRoutes]];
		TraversedCurrentDistance=0.0;
		result+="Moving to the workshop "+to_string(CountOfVisitedWorkshops+1)+"/"+to_string(CountOfTasks)+" started. Total distance: "+ConvertDoubleToString(TotalDistance)+"; route:\n";
		int i;
		for(i=0; i<CountOfRoutes; i++)
			result+=NamesOfWorkshops[TheShortestRoute[i]]+"->";
		result+=NamesOfWorkshops[TheShortestRoute[i]];
		result+="\nALL ROUTES:\n";
		for(i=1; i<TheShortestRoute.size(); i++)
			result+=NamesOfWorkshops[TheShortestRoute[i-1]]+" -> "+NamesOfWorkshops[TheShortestRoute[i]]+": "+ConvertDoubleToString(matrix[TheShortestRoute[i-1]][TheShortestRoute[i]])+"\n";
		result+="------------------------------------------------------------------------------------------\nMoving along the route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CountOfRoutes)+" "+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes-1]]+"->"+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes]]+" with the distance "+ConvertDoubleToString(CurrentDistance)+" started";
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
				}
				else
				{
					double NewStepSize=Robot_StepSize-(NewDistance-CurrentDistance);
					TraversedCurrentDistance+=NewStepSize;
					TraversedTotalDistance+=NewStepSize;
				}
			}
			else
			{
				CurrentPosition=TheShortestRoute[CountOfTraversedRoutes];				
				if(CountOfTraversedRoutes<CountOfRoutes)
				{
					CountOfTraversedRoutes++;
					TraversedCurrentDistance=0.0;
					CurrentDistance=matrix[CurrentPosition][TheShortestRoute[CountOfTraversedRoutes]];
				}
				else
					TraversedTotalDistance=TotalDistance;
			}
			result+="the common distance "+ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance)+"\nalong the route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CountOfRoutes)+" "+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes-1]]+"->"+NamesOfWorkshops[TheShortestRoute[CountOfTraversedRoutes]]+" (dist. "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance)+") was gone";
		}
		else
		{			
			TheShortestRoute.clear();
			CountOfVisitedWorkshops++;
			result+="the task was added to the workshop";			
		}
	}
	return result;
}
void UpdateDataOnScreen()
{
	if(TheShortestRoute.size()==0)
		ChangeOutputOnScreenString(LineNumber,ColumnNumber,"proc. 2|"+AddSpacesToString(to_string(CountOfVisitedWorkshops)+"/"+to_string(CountOfTasks),7)+"|"+AddSpacesToString(to_string(CountOfFailures),4)+"|"+AddSpacesToString(ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance),15)+"|                |"+AddSpacesToString("route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CountOfRoutes)+" "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance),28));
	else
		if(TraversedTotalDistance==TotalDistance)		
			ChangeOutputOnScreenString(LineNumber,ColumnNumber,"waiting|"+AddSpacesToString(to_string(CountOfVisitedWorkshops)+"/"+to_string(CountOfTasks),7)+"|"+AddSpacesToString(to_string(CountOfFailures),4)+"|               |                |"+AddSpacesToString("workshop",28));
		else
		{
			ChangeOutputOnScreenString(LineNumber,ColumnNumber,"proc. 2|"+AddSpacesToString(to_string(CountOfVisitedWorkshops)+"/"+to_string(CountOfTasks),7)+"|"+AddSpacesToString(to_string(CountOfFailures),4)+"|"+AddSpacesToString(ConvertDoubleToString(TraversedTotalDistance)+"/"+ConvertDoubleToString(TotalDistance),15));
			while(BarProgress<100.0 && BarProgress<percent)
			{
				BarProgress+=BarStep;
				ChangeOutputOnScreenChar(LineNumber,BarPos,'|');
				BarPos++;
			}
			ChangeOutputOnScreenString(LineNumber,63,AddSpacesToString("route "+to_string(CountOfTraversedRoutes)+"/"+to_string(CountOfRoutes)+" "+ConvertDoubleToString(TraversedCurrentDistance)+"/"+ConvertDoubleToString(CurrentDistance),28));
		}
}
//--------------------temp--------------------
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
	fstream MapFile("MapOfCities.csv");
	route NewRoute;	
	string FileLine,NewWorkshop,DistanceString;
	char DepartureFound,DestinationFound;	
	int i,j,DepartureIndex,DestinationIndex;	
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
	//-------------------temp-------------------
	/*console=GetStdHandle(STD_OUTPUT_HANDLE);
	CountOfWorkshops=NamesOfWorkshops.size()-1;
	SpeedOfMovement=5.0;
	FisherYatesShuffle(IndexesOfWorkshops,CountOfWorkshops);
	CountOfTasks=5;//GetRandomInt(1,CountOfWorkshops);
	for(i=0; i<CountOfTasks-1; i++)			
		tasks.push_back(IndexesOfWorkshops[i]);	
	tasks.push_back(0);
	cout<<" ROBOT  | STATE | TASKS |FAIL|   PROGRESS    |                |      CURRENT LOCATION      ";
	cout<<"   00   |waiting|       | 0  |               |                |                            ";
	string result;
	percent=0.0;
	CurrentPosition=0;
	CountOfRoutes=0;
	CountOfVisitedWorkshops=0;
	CurrentDistance=0.0;
	BarPos=46;
	BarSize=16;	
	BarProgress=0.0;
	BarStep=100.0/BarSize;	
	while(CountOfVisitedWorkshops<CountOfTasks)
	{
		result=TestRobot();
		ChangeOutputOnScreenString(2,0,result);
		getchar();
		for(i=2; i<20; i++)
			ChangeOutputOnScreenString(i,0,"                                                                                           ");
		UpdateDataOnScreen();
	}*/
	//-------------------end temp-------------------
	CurrentTime=0.0;
	SimulationTime=1000.0;
	Creator_DelayDistribution='e';
	Creator_MeanDelayOrMinDelay=GetRandomDouble(100.0,200.0);
	Creator_MaxDelayOrDeviation=0.0;	
	Creator_MinSpeed=1.0;
	Creator_MaxSpeed=5.0;
	Creator_MaxQueue=GetRandomInt(10,100);
	MinTaskComplexity=1;
	MaxTaskComplexity=NamesOfWorkshops.size();
	//-------------------------------------------
	CountOfWorkshops=NamesOfWorkshops.size();
	Workshop_MaxCountOfIdDigits=GetCountOfDigits(CountOfWorkshops);
	Workshop_MinSizeOfQueueOfRobots=2;
	Workshop_MaxSizeOfQueueOfRobots=5;
	Workshop_DelayDistribution='e';
	Workshop_MeanDelayOrMinDelay=GetRandomDouble(10.0,20.0);
	Workshop_MaxDelayOrDeviation=0.0;	
	Workshop_MinSpeed=10.0;
	Workshop_MaxSpeed=50.0;
	Workshop_MinCountOfBreakdowns=5;
	Workshop_MaxCountOfBreakdowns=10;
	Workshop_MinReliability=0.75;
	Workshop_MaxReliability=0.9;
	//-------------------------------------------
	CountOfRoutes=routes.size();
	Route_MinSizeOfQueueOfRobots=2;
	Route_MaxSizeOfQueueOfRobots=7;
	Route_MinCountOfBreakdowns=5;
	Route_MaxCountOfBreakdowns=10;
	Route_MinReliability=0.75;
	Route_MaxReliability=0.9;
	//-------------------------------------------
	CountOfRobots=1;
	Robot_DelayDistribution='u';
	Robot_MeanDelayOrMinDelay=1.0;
	Robot_MaxDelayOrDeviation=10.0;	
	Robot_MinSpeedOfMovement=1.0;
	Robot_MaxSpeedOfMovement=5.0;
	Robot_MinSpeedOfLoading=0.5;
	Robot_MaxSpeedOfLoading=2.0;
	Robot_MinCountOfBreakdowns=5;
	Robot_MaxCountOfBreakdowns=10;
	Robot_MinReliability=0.8;
	Robot_MaxReliability=0.95;
	CountOfAllDevices=1+CountOfWorkshops+CountOfRobots;
	LastLineNumber=NamesOfWorkshops.size()/2+CountOfRobots+5;
	//TempFile.open("temp.txt");
	model();
	//TempFile.close();
	for(i=0; i<NamesOfWorkshops.size(); i++)
		delete(matrix[i]);
	delete(matrix);
	delete(IndexesOfWorkshops);
	return 0;
}