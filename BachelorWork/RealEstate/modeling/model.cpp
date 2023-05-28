#include "headers/model.h"
model::model()
{	
	int i,j,k,LineNumber,CountOfDigits,MaxCountOfDigits;
	string id;
	percent=0.0;
	BarProgress=0.0;
	BarSize=50;
	BarStep=100.0/BarSize;
	BarPos=33;	
	cout<<"SIMULATION TIME: "<<left<<setw(7)<<CurrentTime<<"/"<<left<<setw(7)<<SimulationTime<<"                                                    "<<left<<setw(6)<<percent<<"%";
/*
CREATOR | QUEUE |STORAGE|FAIL|   PROGRESS    |                                             |
        |123/123|123/123|1234|123/123 100.00%|                                             |
 ROBOT  | STATE | TASKS |FAIL|   PROGRESS    |                |      CURRENT LOCATION      |
        |WAITING|123/123|1234|123.00/123.00M |                | IN THE QUEUE TO 0123456789 |
        |WAITING|123/123|1234|123.00/123.00M |                |route 12/12 1000.00/1000.00 |
WORKSHOP| STATE | QUEUE |FAIL|   PROGRESS    |WORKSHOP| STATE | QUEUE |FAIL|   PROGRESS    |
        |PROC. 1|123/123|1237| 123.00/123.00 |        |PROC. 1|123/123|1237| 123.00/123.00 |
*/
	robot** robots=new robot*[CountOfRobots];	
	workshop** workshops=new workshop*[CountOfWorkshops];
	device** AllDevices=new device*[CountOfAllDevices];
	cout<<"CREATOR | QUEUE |STORAGE|FAIL|   PROGRESS    |                                             ";
	creator* NewCreator=new creator(robots);
	AllDevices[0]=dynamic_cast<creator*>(NewCreator);
	cout<<" ROBOT  | STATE | TASKS |FAIL|   PROGRESS    |                |      CURRENT LOCATION      ";
	MaxCountOfDigits=GetCountOfDigits(CountOfRobots);
	for(i=0,j=1,LineNumber=4; i<CountOfRobots; i++,j++,LineNumber++)
	{		
		CountOfDigits=MaxCountOfDigits-GetCountOfDigits(i);
		for(k=0,id=""; k<CountOfDigits; k++)
			id+="0";
		id+=to_string(i);
		robots[i]=new robot("Robot",id,i,LineNumber,0,GetRandomDouble(Robot_MinReliability,Robot_MaxReliability),GetRandomInt(Robot_MinCountOfBreakdowns,Robot_MaxCountOfBreakdowns),GetRandomDouble(Robot_MinSpeedOfLoading,Robot_MaxSpeedOfLoading),GetRandomDouble(Robot_MinSpeedOfMovement,Robot_MaxSpeedOfMovement),AllDevices[0],workshops);
		AllDevices[j]=dynamic_cast<robot*>(robots[i]);
	}	
	cout<<"WORKSHOP| STATE | QUEUE |FAIL|   PROGRESS    |WORKSHOP| STATE | QUEUE |FAIL|   PROGRESS    ";
	MaxCountOfDigits=GetCountOfDigits(CountOfWorkshops);
	for(i=0,LineNumber++; i<CountOfWorkshops; i++,j++)
	{
		CountOfDigits=MaxCountOfDigits-GetCountOfDigits(i);
		for(k=0,id=""; k<CountOfDigits; k++)
			id+="0";
		id+=to_string(i);
		if(i%2==0)
		{
			workshops[i]=new workshop("Workshop",id,i,LineNumber,0,GetRandomDouble(Robot_MinReliability,Robot_MaxReliability),GetRandomInt(Robot_MinCountOfBreakdowns,Robot_MaxCountOfBreakdowns),GetRandomDouble(Workshop_MinSpeed,Workshop_MaxSpeed),GetRandomInt(Workshop_MinSizeOfQueueOfRobots,Workshop_MaxSizeOfQueueOfRobots),&AllDevices[1]);
			cout<<"|";
		}
		else
		{
			workshops[i]=new workshop("Workshop",id,i,LineNumber,46,GetRandomDouble(Robot_MinReliability,Robot_MaxReliability),GetRandomInt(Robot_MinCountOfBreakdowns,Robot_MaxCountOfBreakdowns),GetRandomDouble(Workshop_MinSpeed,Workshop_MaxSpeed),GetRandomInt(Workshop_MinSizeOfQueueOfRobots,Workshop_MaxSizeOfQueueOfRobots),&AllDevices[1]);
			LineNumber++;
		}
		AllDevices[j]=dynamic_cast<workshop*>(workshops[i]);
	}//--------------------SIMULATION--------------------
	double NextTime,MinNextTime;
	vector<string> results;
	vector<int> DevicesWithChangedState;
	bool SwitchStateOfDevice;
	while(CurrentTime<SimulationTime)
	{
		CurrentTime=SimulationTime;
		for(i=1; i<CountOfAllDevices; i++)
		{
			NextTime=AllDevices[i]->GetNextTime();//GetTimeOfTheNextState();
			if(NextTime<CurrentTime)			
				CurrentTime=NextTime;
		}
		for(i=0,SwitchStateOfDevice=true; i<CountOfAllDevices; i++)
			if(AllDevices[i]->GetState()!="BROKEN")
			{
				NextTime=AllDevices[i]->GetNextTime();
				if(NextTime<CurrentTime)
				{
					CurrentTime=NextTime;
					SwitchStateOfDevice=false;
				}
			}
		if(SwitchStateOfDevice==true)
			for(i=1; i<CountOfAllDevices; i++)
				if(AllDevices[i]->GetTimeOfTheNextState()==CurrentTime)
				{					
					results.push_back(AllDevices[i]->SwitchState());
					DevicesWithChangedState.push_back(i);
				}
		for(i=0; i<CountOfAllDevices; i++)
			if(AllDevices[i]->GetState()!="BROKEN" && AllDevices[i]->GetNextTime()==CurrentTime)
			{
				results.push_back(AllDevices[i]->TakeOneStep());
				DevicesWithChangedState.push_back(i);
			}
		TakeTimeStep(CurrentTime);
		ScreenCoordinates.X=0;
		ScreenCoordinates.Y=LastLineNumber;
		SetConsoleCursorPosition(console,ScreenCoordinates);
		if(results.size()>0)
		{
			cout<<"Events of the time "<<CurrentTime<<":\n";
			//TempFile<<"Events of the time "<<CurrentTime<<":\n";
			for(i=0; i<results.size(); i++)
			{
				cout<<i+1<<". "<<results[i]<<endl;
				//TempFile<<i+1<<". "<<results[i]<<endl;
			}
		}
		for(i=0; i<DevicesWithChangedState.size(); i++)
		{
			AllDevices[DevicesWithChangedState[i]]->UpdateDataOnScreen();
			AllDevices[DevicesWithChangedState[i]]->UpdateStateOnScreen();			
		}
		getchar();
		//Sleep(10);		
		ScreenCoordinates.X=0;
		ScreenCoordinates.Y=LastLineNumber;
		SetConsoleCursorPosition(console,ScreenCoordinates);
		for(i=0; i<results.size()+10; i++)
			cout<<"                                                                                           ";
		results.clear();
		DevicesWithChangedState.clear();
	}
	ScreenCoordinates.X=0;
	ScreenCoordinates.Y=LastLineNumber;
	SetConsoleCursorPosition(console,ScreenCoordinates);
}
model::~model()
{	
	/*for(int i=0; i<CountOfAllDevices; i++)
		delete(AllDevices[i]);
	delete(AllDevices);*/
}
void model::TakeTimeStep(double time)
{
	percent=(time*100.0)/SimulationTime;
	ChangeOutputOnScreenDouble(0,17,7,time);
	ChangeOutputOnScreenDouble(0,84,6,percent);
	while(BarProgress<100 && BarProgress<percent)
	{
		BarProgress+=BarStep;
		ChangeOutputOnScreenChar(0,BarPos,'|');
		BarPos++;
	}
}