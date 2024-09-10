#include "car.h"
class manager: public object
{
	queue<queue<task>> StorageOfTasks;
	car** cars;
	city** cities;
	vector<int> IndexesOfCars;
	int CountOfCars,BarSize,BarPos;
	double CostOfCompletion,AllocatedFunds,SizeOfStorage,PercentageOfStorageFilling,percent,BarStep;	
	public: manager(double NewSimulationTime,char NewDelayDistribution,double NewMeanDelayOrMinDelay,double NewMaxDelayOrDeviation,city** NewCities,double NewCostOfCompletion,double PercentageForStorage,int NewCountOfCars,car** NewCars);
	manager(car** NewCars);
	void UpdateDataOnScreen();
};