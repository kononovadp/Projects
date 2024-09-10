#include "headers/model.h"
model::model(int CountOfYears,double PercentageOfAdditionalDelay,double PercentageOfAdditionalMinReliability,double CostOfCompletion,double PercentageForStorage,const vector<StructCity> NewCities,double** matrix,int CountOfCars,double PercentageOfAdditionalCarVolume)
{
	int i,j,k,LineNumber,CountOfDigits,MaxCountOfDigits;
	int CountOfAllObjects=1+NewCities.size()+CountOfCars;
	double CurrentTime=0.0,SimulationTime=CountOfYears*365.0,reliability;
	string id;	
	percent=0.0;
	BarProgress=0.0;
	BarSize=50;
	BarStep=100.0/BarSize;
	BarPos=33;
	CurrentTime=0.0;	
	object** objects=new object*[CountOfAllObjects];
	car** cars=new car*[CountOfCars];
	city** cities=new city*[NewCities.size()];
	manager* NewManager=new manager(SimulationTime,'r',AddPercentage(PercentageOfAdditionalDelay,100.0),AddPercentage(PercentageOfAdditionalDelay,200.0),cities,CostOfCompletion,PercentageForStorage,CountOfCars,cars);
	objects[0]=dynamic_cast<manager*>(NewManager);
	MaxCountOfDigits=GetCountOfDigits(CountOfCars);
	for(i=0,j=1,LineNumber=4; i<CountOfCars; i++,j++,LineNumber++)
	{		
		CountOfDigits=MaxCountOfDigits-GetCountOfDigits(i);
		for(k=0,id=""; k<CountOfDigits; k++)
			id+="0";
		id+=to_string(i);
		reliability=GetRandomDouble(AddPercentage(PercentageOfAdditionalMinReliability,0.75),0.95);		
		cars[i]=new car("Car",id,i,LineNumber,0,SimulationTime,'r',AddPercentage(PercentageOfAdditionalDelay,2.0),AddPercentage(PercentageOfAdditionalDelay,5.0),reliability,GetRandomInt(3,10),GetRandomDouble(AddPercentage(0.005,PercentageOfAdditionalCarVolume),AddPercentage(0.01,PercentageOfAdditionalCarVolume)),NewManager,cities);
		objects[j]=dynamic_cast<car*>(cars[i]);
	}
	for(i=0,LineNumber++; i<NewCities.size(); i++,j++)
	{
		if(NewCities[i].name.length()<=8)
			id=NewCities[i].name;
		else
		{			
			id="";
			CountOfDigits=NewCities[i].name.length()-3;
			id=id+NewCities[i].name[0]+NewCities[i].name[1]+NewCities[i].name[2]+".."+NewCities[i].name[CountOfDigits]+NewCities[i].name[CountOfDigits+1]+NewCities[i].name[CountOfDigits+2];
		}
		reliability=GetRandomDouble(AddPercentage(PercentageOfAdditionalMinReliability,0.75),0.95);
		if(i%2==0)
			cities[i]=new city("City",id,i,LineNumber,0,SimulationTime,'r',AddPercentage(PercentageOfAdditionalDelay,2.0),AddPercentage(PercentageOfAdditionalDelay,5.0),reliability,GetRandomInt(3,10),NewCities[i].CountOfIncompleteConstructions,objects);
		else
		{
			cities[i]=new city("City",id,i,LineNumber,45,SimulationTime,'r',AddPercentage(PercentageOfAdditionalDelay,2.0),AddPercentage(PercentageOfAdditionalDelay,5.0),reliability,GetRandomInt(3,10),NewCities[i].CountOfIncompleteConstructions,objects);
			LineNumber++;
		}
	}
	cout<<"SIMULATION TIME: "<<left<<setw(7)<<CurrentTime<<"/"<<left<<setw(7)<<SimulationTime<<"                                                  "<<left<<setw(6)<<percent<<"%|\n";
	cout<<"MANAGER |  CAR  |STORAGE|FAIL| FUNDS $ BNS. |                                            |\n";	
	objects[0]->UpdateDataOnScreen();
	cout<<"  CARS  | STATE | TASKS |  DELIVERED STUFF  |                |      CURRENT LOCATION     |\n";
	for(i=0; i<CountOfCars; i++)
		cars[i]->UpdateDataOnScreen();
	cout<<"LOCATION| STATE | BLDGS |USED STUFF ($ BNS.)|LOCATION| STATE | BLDGS |USED STUFF ($ BNS.)|\n";
	for(i=0; i<NewCities.size(); i++)
		cities[i]->UpdateDataOnScreen();
/*
MANAGERS|  CAR  |STORAGE|FAIL| FUNDS $ BNS. |                                            |
        |123/123|123/123|1234|0.0005/0.0005 |                                            |
  CARS  | STATE | TASKS |DELIVERED STUFF ($)|                |      CURRENT LOCATION     |
        |WAITING|123/123|0.0005/0.0005 100% |                | IN THE QUEUE TO 0123456789|
        |WAITING|123/123|0.0005/0.0005 100% |                |route 12/12 1000.00/1000.00|
LOCATION|  CAR  |FROZEN |FUNDS ($ BNS.)|LOCATION|  CAR  | REC. BLDGS |FUNDS ($ BNS.)|
        |123/123|123/123|123.00/123.00 |        |123/123|10000/10000 |123.00/123.00 |
LOCATION| STATE | BLDGS |USED STUFF ($ BNS.)|LOCATION| STATE | BLDGS |USED STUFF ($ BNS.)|
        |PROC. 1|123/123|123.00/123.00 100% |        |PROC. 1|123/123|123.00/123.00 100% |
*/
	
}
void model::TakeTimeStep(double time)
{	
	//percent=(time*100.0)/SimulationTime;	
	ChangeOutputOnScreenDouble(1,17,7,time);
	ChangeOutputOnScreenDouble(1,84,6,percent);
	while(BarProgress<100 && BarProgress<percent)
	{
		BarProgress+=BarStep;
		ChangeOutputOnScreenChar(1,BarPos,'|');
		BarPos++;
	}
}