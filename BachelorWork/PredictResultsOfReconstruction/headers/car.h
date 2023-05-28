#include "city.h"
class car: public object
{
	city** cities;
	object* manager;
	vector<struct task*> tasks;
	string location;
	int CountOfTasks,TotalCountOfTasks,TotalCountOfFinishedTasks,TaskIndex,CountOfDelays,CountOfFinishedTasks,CountOfReturnings,CurrentPosition,CountOfRoutes,CountOfTraversedRoutes,BarSize,BarPos;
	double volume,PercentageOfTrunkFilling,MovementTime,percent,stuff,DeliveredStuff,BarProgress,BarStep,TotalDistance,TraversedTotalDistance,CurrentDistance,TraversedCurrentDistance;
	vector<int> TheShortestRoute;
	char* CountsOfAttempts;
	public: car(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double NewSimulationTime,char NewDelayDistribution,double NewMeanDelayOrMinDelay,double NewMaxDelayOrDeviation,double reliability,int CountOfBreakdowns,double NewVolume,object* NewManager,city** NewCities);
	void UpdateDataOnScreen();
};