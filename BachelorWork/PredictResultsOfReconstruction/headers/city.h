#include "construction.h"
class city: public object
{
	object** cars;
	construction** constitutions;
	queue<struct task*> tasks;
	int CountOfConstructions,CountOfFinishedConstructions;
	double stuff,UsedStuff,PercentageOfUsedStuff,percent;
	public: city(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double NewSimulationTime,char NewDelayDistribution,double NewMeanDelayOrMinDelay,double NewMaxDelayOrDeviation,double reliability,int CountOfBreakdowns,int NewCountOfConstructions,object** NewCars);
	void UpdateDataOnScreen();
};