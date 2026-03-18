#include "headers/model.h"
model::model()
{
	int i,j,k,LineNumber,CountOfDigits,MaxCountOfDigits,AverageIntValue=0;
	int Workshop_SizeOfQueue;
	double reliability,Robot_AverageReliability=0.0,AverageDoubleValue;	
	double Workshop_AverageReliability=0.0;	
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
	for(i=0,j=1,LineNumber=5; i<CountOfRobots; i++,j++,LineNumber++)
	{		
		CountOfDigits=MaxCountOfDigits-GetCountOfDigits(i);
		for(k=0,id=""; k<CountOfDigits; k++)
			id+="0";
		id+=to_string(i);
		reliability=GetRandomDouble(Robot_MinReliability,Robot_MaxReliability);
		Robot_AverageReliability+=reliability;
		robots[i]=new robot("Robot",id,i,LineNumber,0,reliability,GetRandomInt(Robot_MinCountOfBreakdowns,Robot_MaxCountOfBreakdowns),GetRandomDouble(Robot_MinTaskTime,Robot_MaxTaskTime),GetRandomDouble(Robot_MinMovementTime,Robot_MaxMovementTime),AllDevices[0],workshops);
		AllDevices[j]=dynamic_cast<robot*>(robots[i]);
	}	
	cout<<"WORKSHOP| STATE | QUEUE |FAIL|   PROGRESS    |WORKSHOP| STATE | QUEUE |FAIL|   PROGRESS    ";
	MaxCountOfDigits=GetCountOfDigits(CountOfWorkshops);	
	for(i=0,LineNumber++; i<CountOfWorkshops; i++,j++)
	{
		CountOfDigits=MaxCountOfDigits-GetCountOfDigits(i+1);
		for(k=0,id=""; k<CountOfDigits; k++)
			id+="0";
		id+=to_string(i+1);
		reliability=GetRandomDouble(Workshop_MinReliability,Workshop_MaxReliability);
		Workshop_AverageReliability+=reliability;
		Workshop_SizeOfQueue=GetRandomInt(Workshop_MinSizeOfQueueOfRobots,Workshop_MaxSizeOfQueueOfRobots);
		if(i%2==0)
		{
			workshops[i]=new workshop("Workshop",id,i,LineNumber,0,reliability,GetRandomInt(Workshop_MinCountOfBreakdowns,Workshop_MaxCountOfBreakdowns),Workshop_SizeOfQueue,&AllDevices[1]);
			cout<<"|";
		}
		else
		{
			workshops[i]=new workshop("Workshop",id,i,LineNumber,46,reliability,GetRandomInt(Workshop_MinCountOfBreakdowns,Workshop_MaxCountOfBreakdowns),Workshop_SizeOfQueue,&AllDevices[1]);
			LineNumber++;
		}
		AllDevices[j]=dynamic_cast<workshop*>(workshops[i]);
	}//--------------------SIMULATION--------------------
	double NextTime,MinNextTime;
	vector<string> results;
	vector<int> DevicesWithChangedState;
	bool SwitchStateOfDevice;
	CurrentTime=0.0;
	while(CurrentTime<SimulationTime)
	{
		CurrentTime=SimulationTime;
		for(i=1; i<CountOfAllDevices; i++)
		{
			NextTime=AllDevices[i]->GetTimeOfTheNextState();//GetNextTime();
			if(NextTime<CurrentTime)			
				CurrentTime=NextTime;
		}
		for(i=0,SwitchStateOfDevice=true; i<CountOfAllDevices; i++)
			if(AllDevices[i]->GetState()!="BROKEN ")
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
			if(AllDevices[i]->GetState()!="BROKEN " && AllDevices[i]->GetNextTime()==CurrentTime)
			{
				results.push_back(AllDevices[i]->TakeOneStep());
				DevicesWithChangedState.push_back(i);
			}
		ScreenCoordinates.X=0;
		ScreenCoordinates.Y=LastLineNumber;
		SetConsoleCursorPosition(console,ScreenCoordinates);
		if(results.size()>0)
		{
			//cout<<"Events of the time "<<CurrentTime<<":\n";
			for(i=0; i<results.size(); i++)
			{				
				File_AllEvents<<setw(7)<<CurrentTime<<". "<<results[i]<<endl;
				/*cout<<i+1<<". "<<results[i];
				if(i+1<results.size())
					cout<<endl;*/
			}
		}
		//getchar();
		//Sleep(10);
		for(i=0; i<DevicesWithChangedState.size(); i++)
		{
			AllDevices[DevicesWithChangedState[i]]->UpdateStateOnScreen();
			AllDevices[DevicesWithChangedState[i]]->UpdateDataOnScreen();
		}
		ScreenCoordinates.X=0;
		ScreenCoordinates.Y=LastLineNumber;
		SetConsoleCursorPosition(console,ScreenCoordinates);
		for(i=0; i<results.size(); i++)
		{
			for(j=0; j<results[i].length(); j++)
				if(results[i][j]=='\n')
					cout<<"                                                                                           ";
			cout<<"                                                                                           ";
		}
		cout<<"                                                                                           ";
		TakeTimeStep(CurrentTime);
		results.clear();
		DevicesWithChangedState.clear();
	}
	RobotStatistics<<"\n"<<Creator_MeanDelayOrMinDelay<<";"<<Creator_MaxDelayOrDeviation<<";"<<Robot_AverageReliability/CountOfRobots<<";";
	for(i=0,AverageDoubleValue=0.0; i<CountOfRobots; i++)
		AverageDoubleValue+=robots[i]->GetAverageDelay();
	RobotStatistics<<AverageDoubleValue/CountOfRobots<<";";
	for(i=0,AverageDoubleValue=0.0; i<CountOfRobots; i++)
		AverageDoubleValue+=robots[i]->GetAverageTimeForOneTask();
	RobotStatistics<<AverageDoubleValue/CountOfRobots<<";";
	for(i=0,AverageDoubleValue=0.0; i<CountOfRobots; i++)
		AverageDoubleValue+=robots[i]->GetLoad();
	RobotStatistics<<AverageDoubleValue/CountOfRobots<<";";
	for(i=0,AverageDoubleValue=0.0; i<CountOfRobots; i++)
		AverageDoubleValue+=robots[i]->GetCountOfTasks();
	RobotStatistics<<AverageDoubleValue/CountOfRobots<<";";
	for(i=0,AverageDoubleValue=0.0; i<CountOfRobots; i++)
		AverageDoubleValue+=robots[i]->GetPercentageOfFinishedTasks();
	RobotStatistics<<AverageDoubleValue/CountOfRobots<<";";
	for(i=0,AverageDoubleValue=0.0; i<CountOfRobots; i++)
		AverageDoubleValue+=robots[i]->GetCountOfReturnings();
	RobotStatistics<<AverageDoubleValue/CountOfRobots<<";";
	WorkshopStatistics<<"\n"<<Workshop_MeanDelayOrMinDelay<<";"<<Workshop_MaxDelayOrDeviation<<";"<<Workshop_AverageReliability/CountOfWorkshops<<";";
	for(i=0,AverageIntValue=0; i<CountOfWorkshops; i++)
		AverageIntValue+=workshops[i]->GetAverageQueue();
	WorkshopStatistics<<(int)AverageIntValue/CountOfWorkshops<<";";
	for(i=0,AverageIntValue=0; i<CountOfWorkshops; i++)
		AverageIntValue+=workshops[i]->GetMaxCountOfRobotsInQueue();
	WorkshopStatistics<<(int)AverageIntValue/CountOfWorkshops<<";";
	for(i=0,AverageDoubleValue=0.0; i<CountOfWorkshops; i++)
		AverageDoubleValue+=workshops[i]->GetAverageDelay();
	WorkshopStatistics<<AverageDoubleValue/CountOfWorkshops<<";";
	for(i=0,AverageDoubleValue=0.0; i<CountOfWorkshops; i++)
		AverageDoubleValue+=workshops[i]->GetLoad();
	WorkshopStatistics<<AverageDoubleValue/CountOfWorkshops<<";";
	for(i=0,AverageDoubleValue=0.0; i<CountOfWorkshops; i++)
		AverageDoubleValue+=workshops[i]->GetTotalCountOfTasks();
	WorkshopStatistics<<AverageDoubleValue/CountOfWorkshops<<";";
	for(i=0,AverageDoubleValue=0.0; i<CountOfWorkshops; i++)
		AverageDoubleValue+=workshops[i]->GetPercentageOfFinishedTasks();
	WorkshopStatistics<<AverageDoubleValue/CountOfWorkshops<<";";
	delete(NewCreator);	
	for(i=0; i<CountOfRobots; i++)
		robots[i]->~robot();
	delete(robots);
	for(i=0; i<CountOfWorkshops; i++)
		workshops[i]->~workshop();	
	delete(workshops);
	delete(AllDevices);	
	CurrentTime=0.0;	
	ScreenCoordinates.X=0;
	ScreenCoordinates.Y=0;
	SetConsoleCursorPosition(console,ScreenCoordinates);
}
void model::TakeTimeStep(double time)
{	
	percent=(time*100.0)/SimulationTime;	
	ChangeOutputOnScreenDouble(1,17,7,time);
	ChangeOutputOnScreenDouble(1,84,6,percent);
	while(BarProgress<100 && BarProgress<percent)
	{
		BarProgress+=BarStep;
		ChangeOutputOnScreenChar(1,BarPos,'|');
		BarPos++;
	}
}