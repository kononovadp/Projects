#include "headers/model.h"
car::car(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double NewSimulationTime,char NewDelayDistribution,double NewMeanDelayOrMinDelay,double NewMaxDelayOrDeviation,double reliability,int CountOfBreakdowns,double NewVolume,object* NewManager,city** NewCities):object(NewClassName,NewId,NewIndex,NewLineNumber,NewColumnNumber,NewSimulationTime,NewDelayDistribution,NewMeanDelayOrMinDelay,NewMaxDelayOrDeviation,reliability,CountOfBreakdowns)
{
	location="Manager";
	volume=NewVolume;
	manager=NewManager;
	cities=NewCities;
	stuff=0.0;
	DeliveredStuff=0.0;
	PercentageOfTrunkFilling=0.0;
	CountOfFinishedTasks=0;	
	percent=0.0;
	BarProgress=0.0;
	BarSize=15;
	BarStep=100.0/BarSize;
	BarPos=46;
}
void car::UpdateDataOnScreen()
{
/*
  CARS  | STATE | TASKS |  DELIVERED STUFF  |               |      CURRENT LOCATION      |	
*/	
	if(percent==0.0)
		ChangeOutputOnScreenString(GetLineNumber(),0,AddSpacesToString(GetId(),8)+"|"+AddSpacesToString(GetState(),7)+"|"+AddSpacesToString(to_string(CountOfFinishedTasks)+"/"+to_string(tasks.size()),7)+"|"+AddSpacesToString(ConvertDoubleToString(DeliveredStuff,2)+"/"+ConvertDoubleToString(stuff,2)+" "+ConvertDoubleToString(PercentageOfTrunkFilling,0)+"%",19)+"|                |"+AddSpacesToString(location,27)+"|\n");
}
