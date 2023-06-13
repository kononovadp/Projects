#include "headers/creator.h"
creator::creator(robot** NewRobots):device()
{
	robots=NewRobots;
	for(int i=0; i<CountOfRobots; i++)	
		IndexesOfRobots.push_back(i);
	percent=0.0;
	BarSize=45;
	BarStep=100.0/BarSize;
	BarPos=46;
	CountOfTasks=0;
	CountOfCreatedTasks=0;
	ActiveTime=0.0;
	SetNextTime(0.0);
	AverageDelay=0.0;
	CountOfDelays=0;
	AverageTimeForOneTask=0.0;
	TotalCountOfTasks=0;
	AverageTaskComplexity=0.0;
	cout<<AddSpacesToString(GetState(),8)<<"|"<<AddSpacesToString(to_string(IndexesOfRobots.size())+"/"+to_string(CountOfRobots),7)<<"|"<<AddSpacesToString(to_string(StorageOfTasks.size())+"/"+to_string(Creator_MaxQueue),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|"<<AddSpacesToString(to_string(CountOfCreatedTasks)+"/"+to_string(CountOfTasks)+" "+ConvertDoubleToString(percent)+"%",15)<<"|                                             ";
}
creator::~creator()
{
	while(StorageOfTasks.size()>0)	
		StorageOfTasks.pop();
	IndexesOfRobots.clear();
	CreatorStatistics<<"\n"<<Creator_MeanDelayOrMinDelay<<";"<<Creator_MaxDelayOrDeviation<<";"<<Creator_MaxQueue<<";"<<AverageDelay/CountOfDelays<<";"<<AverageTaskComplexity/TotalCountOfTasks<<";"<<AverageTimeForOneTask/TotalCountOfTasks<<";"<<(ActiveTime*100.0)/SimulationTime<<";"<<GetCountOfFailures();	
}
bool creator::AddTask(int NewId)
{
	IndexesOfRobots.push_back(NewId);
	ChangeOutputOnScreenString(3,9,AddSpacesToString(to_string(IndexesOfRobots.size())+"/"+to_string(CountOfRobots),7));
	return true;
}
string creator::TakeOneStep()
{
	double TimeInterval;
	string result="CREATOR: ";	
	int i,RobotIndex=-1,IndexOfIndexesOfRobots;	
	for(i=0; i<IndexesOfRobots.size(); i++)
		if(robots[IndexesOfRobots[i]]->GetState()!="BROKEN")
		{
			RobotIndex=IndexesOfRobots[i];
			IndexOfIndexesOfRobots=i;
			break;
		}
	if(StorageOfTasks.size()>0 && RobotIndex>-1)
	{		
		queue<task> NewSetOfTask=StorageOfTasks.front();
		int NewSetOfTaskSize=NewSetOfTask.size();
		StorageOfTasks.pop();
		IndexesOfRobots.erase(IndexesOfRobots.begin()+IndexOfIndexesOfRobots);
		ChangeOutputOnScreenString(3,9,AddSpacesToString(to_string(IndexesOfRobots.size())+"/"+to_string(CountOfRobots),7));
		while(NewSetOfTask.size()>0)
		{
			struct task NewTask=NewSetOfTask.front();
			NewSetOfTask.pop();
			robots[RobotIndex]->AddTask(NewTask.performer,NewTask.WorkTime);
		}
		robots[RobotIndex]->AddDelay(GetDelay(Robot_MeanDelayOrMinDelay,Robot_MaxDelayOrDeviation,Robot_DelayDistribution));
		result+=to_string(NewSetOfTaskSize)+" tasks were added to the robot "+robots[RobotIndex]->GetId()+" from the STORAGE";
		TimeInterval=GetDelay(Creator_MeanDelayOrMinDelay,Creator_MaxDelayOrDeviation,Creator_DelayDistribution);
		AverageDelay+=TimeInterval;
		CountOfDelays++;
		SetNextTime(TimeInterval);
	}
	else
	{
		if(CountOfTasks==0)
		{
			SetState("working");
			CountOfTasks=GetRandomInt(1,CountOfRobots+3);
			CountOfCreatedTasks=0;
			percent=0.0;
			BarProgress=0.0;
			result+="generating of "+to_string(CountOfTasks)+" tasks started";
			SetNextTime(1.0);
			ActiveTime+=1.0;
		}
		else
		{
			if(CountOfCreatedTasks<CountOfTasks)
			{
				if(IndexesOfRobots.size()>0 || StorageOfTasks.size()<Creator_MaxQueue)
				{
					int i,TaskSize=GetRandomInt(MinTaskComplexity,MaxTaskComplexity);
					TotalCountOfTasks++;
					AverageTaskComplexity+=TaskSize;
					queue<task> SetOfTasks;
					FisherYatesShuffle(IndexesOfWorkshops,CountOfWorkshops-1);
					for(i=0; i<TaskSize-1; i++)
					{
						struct task NewTask;
						NewTask.performer=IndexesOfWorkshops[i];						
						NewTask.WorkTime=GetRandomDouble(1.0,50.0);
						SetOfTasks.push(NewTask);
					}
					struct task NewTask;
					NewTask.performer=0;					
					NewTask.WorkTime=GetRandomDouble(1.0,50.0);
					SetOfTasks.push(NewTask);
					if(RobotIndex>-1)
					{
						for(i=0; i<TaskSize; i++)
						{
							NewTask=SetOfTasks.front();
							robots[RobotIndex]->AddTask(NewTask.performer,NewTask.WorkTime);
							SetOfTasks.pop();
						}
						robots[RobotIndex]->AddDelay(GetDelay(Robot_MeanDelayOrMinDelay,Robot_MaxDelayOrDeviation,Robot_DelayDistribution));
						result=result+"task "+to_string(CountOfCreatedTasks+1)+" of "+to_string(CountOfTasks)+" with "+to_string(TaskSize)+" workshops was added to the robot "+robots[RobotIndex]->GetId();
						IndexesOfRobots.erase(IndexesOfRobots.begin()+IndexOfIndexesOfRobots);
						ChangeOutputOnScreenString(3,9,AddSpacesToString(to_string(IndexesOfRobots.size())+"/"+to_string(CountOfRobots),7));
					}
					else
					{
						StorageOfTasks.push(SetOfTasks);
						result=result+"task "+to_string(CountOfCreatedTasks+1)+" of "+to_string(CountOfTasks)+" with "+to_string(TaskSize)+" workshops was added to the queue ";
					}
					/*TimeInterval=GetRandomDouble(Creator_MinTaskTime,Creator_MaxTaskTime);
					ActiveTime+=TimeInterval;
					SetNextTime(TimeInterval);*/
				}
				else
				{
					IncreaseCountOfFailures();					/*TimeInterval=GetRandomDouble(Creator_MinTaskTime,Creator_MaxTaskTime);
					ActiveTime+=TimeInterval;
					SetNextTime(TimeInterval);*/
					result+="generating of task "+to_string(CountOfCreatedTasks+1)+" was FAILED";
				}
				CountOfCreatedTasks++;
				//TotalCountOfTasks++;
				percent=(CountOfCreatedTasks*100.0)/CountOfTasks;
				TimeInterval=GetRandomDouble(Creator_MinTaskTime,Creator_MaxTaskTime);
				ActiveTime+=TimeInterval;
				AverageTimeForOneTask+=TimeInterval;				
				SetNextTime(TimeInterval);
			}
			else
			{
				SetState("waiting");
				percent=0.0;
				BarProgress=0.0;
				BarPos=46;
				TimeInterval=GetDelay(Creator_MeanDelayOrMinDelay,Creator_MaxDelayOrDeviation,Creator_DelayDistribution);
				AverageDelay+=TimeInterval;
				CountOfDelays++;
				SetNextTime(TimeInterval);
				CountOfTasks=0;			
				result+="generating of "+to_string(CountOfCreatedTasks)+" tasks was FINISHED";
				CountOfCreatedTasks=0;
			}
		}
	}
	device::WriteToFile(result);
	return result;
}
void creator::UpdateDataOnScreen()
{
	ScreenCoordinates.X=0;
	if(GetState()=="working")
	{
		ScreenCoordinates.Y=3;
		SetConsoleCursorPosition(console,ScreenCoordinates);
		cout<<AddSpacesToString(GetState(),8)<<"|"<<AddSpacesToString(to_string(IndexesOfRobots.size())+"/"+to_string(CountOfRobots),7)<<"|"<<AddSpacesToString(to_string(StorageOfTasks.size())+"/"+to_string(Creator_MaxQueue),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|"<<AddSpacesToString(to_string(CountOfCreatedTasks)+"/"+to_string(CountOfTasks)+" "+ConvertDoubleToString(percent)+"%",15)<<"|";
		while(BarProgress<100 && BarProgress<percent)
		{
			BarProgress+=BarStep;
			ChangeOutputOnScreenChar(2,BarPos,'|');
			ChangeOutputOnScreenChar(3,BarPos,'|');
			BarPos++;
		}
	}
	else
	{
		ScreenCoordinates.Y=2;
		SetConsoleCursorPosition(console,ScreenCoordinates);
		cout<<"CREATOR | QUEUE |STORAGE|FAIL|   PROGRESS    |                                             "<<AddSpacesToString(GetState(),8)<<"|"<<AddSpacesToString(to_string(IndexesOfRobots.size())+"/"+to_string(CountOfRobots),7)<<"|"<<AddSpacesToString(to_string(StorageOfTasks.size())+"/"+to_string(Creator_MaxQueue),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|"<<AddSpacesToString(to_string(CountOfCreatedTasks)+"/"+to_string(CountOfTasks)+" "+ConvertDoubleToString(percent)+"%",15)<<"|                                             ";
	}
}