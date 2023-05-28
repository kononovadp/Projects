#include "SharedFunctions.h"
#include "creator.h"
class model
{	
	int BarSize,BarPos;
	double percent;
	double BarProgress,BarStep;	
	void TakeTimeStep(double time);
	public: model();
	~model();	
};