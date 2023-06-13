#include "SharedFunctions.h"
#include "object.h"
#include "manager.h"
extern double CurrentTime,SimulationTime;
class model
{	
	int BarSize,BarPos;
	double percent;
	double BarProgress,BarStep;	
	void TakeTimeStep(double time);
	public: model(int CountOfYears,double PercentageOfAdditionalDelay,double PercentageOfAdditionalMinReliability,double CostOfCompletion,double PercentageForStorage,const vector<StructCity> NewCities,double** matrix,int CountOfCars,double PercentageOfAdditionalCarVolume);
};