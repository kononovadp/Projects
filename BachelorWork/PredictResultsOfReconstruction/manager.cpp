#include "headers/model.h"
manager::manager(double NewSimulationTime,char NewDelayDistribution,double NewMeanDelayOrMinDelay,double NewMaxDelayOrDeviation,city** NewCities,double NewCostOfCompletion,double PercentageForStorage,int NewCountOfCars,car** NewCars):object(NewSimulationTime,NewDelayDistribution,NewMeanDelayOrMinDelay,NewMaxDelayOrDeviation)
{
	cities=NewCities;
	cars=NewCars;
	CountOfCars=NewCountOfCars;	
	for(int i=0; i<CountOfCars; i++)	
		IndexesOfCars.push_back(i);
	CostOfCompletion=NewCostOfCompletion;
	AllocatedFunds=0.0;
	SizeOfStorage=GetPercentage(CostOfCompletion,PercentageForStorage);
	PercentageOfStorageFilling=0.0;
	percent=0.0;
	BarSize=43;
	BarStep=100.0/BarSize;
	BarPos=44;
	SetNextTime(0.0,0.0);	
}
void manager::UpdateDataOnScreen()
{
/*
MANAGERS|VEHICLE|STORAGE|FAIL|  FUND (BN.)  |                                            |
        |123/123|123/123|1234|123.00/123.00 |                                            |
*/
	if(percent==0.0)
		ChangeOutputOnScreenString(2,8,"|"+AddSpacesToString(to_string(IndexesOfCars.size())+"/"+to_string(CountOfCars),7)+"|"+AddSpacesToString(ConvertDoubleToString(PercentageOfStorageFilling,2)+"%",7)+"|"+AddSpacesToString(to_string(GetCountOfFailures()),4)+"|"+AddSpacesToString(ConvertDoubleToString(AllocatedFunds,4)+"/"+ConvertDoubleToString(CostOfCompletion,4),14)+"|                                            |\n");
}