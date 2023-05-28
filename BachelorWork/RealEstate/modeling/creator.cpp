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
	SetNextTime(0.0);
	cout<<AddSpacesToString(GetState(),8)<<"|"<<AddSpacesToString(to_string(IndexesOfRobots.size())+"/"+to_string(CountOfRobots),7)<<"|"<<AddSpacesToString(to_string(StorageOfTasks.size())+"/"+to_string(Creator_MaxQueue),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|"<<AddSpacesToString(to_string(CountOfCreatedTasks)+"/"+to_string(CountOfTasks)+" "+ConvertDoubleToString(percent)+"%",15)<<"|                                             ";	
}
bool creator::AddTask(int NewId){return true;}
string creator::TakeOneStep()
{
	string result="CREATOR: ";
	if(CountOfTasks==0)
	{
		SetState("working");
		CountOfTasks=GetRandomInt(2,50);
		CountOfCreatedTasks=0;
		percent=0.0;
		BarProgress=0.0;
		result+="generating of "+to_string(CountOfTasks)+" tasks started";
		SetNextTime(1.0);
	}
	else
	{
		if(CountOfCreatedTasks<CountOfTasks)
		{
			if(IndexesOfRobots.size()>0 || StorageOfTasks.size()<Creator_MaxQueue)
			{
				int i,IndexOfRobot=-1,IndexOfIndexesOfRobots;
				int TaskSize=GetRandomInt(MinTaskComplexity,MaxTaskComplexity);
				struct task NewTask;
				queue<task> SetOfTasks;
				FisherYatesShuffle(IndexesOfWorkshops,NamesOfWorkshops.size()-1);
				for(i=0; i<TaskSize; i++)
				{
					NewTask.performer=IndexesOfWorkshops[i];					
					NewTask.WorkTime=GetRandomDouble(1.0,50.0);
					SetOfTasks.push(NewTask);
				}				
				for(i=0; i<IndexesOfRobots.size(); i++)
					if(robots[IndexesOfRobots[i]]->GetState()!="BROKEN")
					{
						IndexOfRobot=IndexesOfRobots[i];
						IndexOfIndexesOfRobots=i;
						break;
					}
				if(IndexOfRobot>-1)
				{					
					for(i=0; i<TaskSize; i++)
					{
						NewTask=SetOfTasks.front();
						robots[IndexOfRobot]->AddTask(NewTask.performer,NewTask.WorkTime);
						SetOfTasks.pop();
					}
					robots[IndexOfRobot]->SetNextTime(GetDelay(Robot_MeanDelayOrMinDelay,Robot_MaxDelayOrDeviation,Robot_DelayDistribution));					
					result=result+"task "+to_string(CountOfCreatedTasks+1)+" of "+to_string(CountOfTasks)+" with "+to_string(TaskSize)+" workshops was added to the robot "+to_string(IndexOfRobot);
					IndexesOfRobots.erase(IndexesOfRobots.begin()+IndexOfIndexesOfRobots);
				}
				else
				{
					StorageOfTasks.push(SetOfTasks);
					result=result+"task "+to_string(CountOfCreatedTasks+1)+" of "+to_string(CountOfTasks)+" with "+to_string(TaskSize)+" workshops was added to the queue ";
				}
				SetNextTime(SimulationTime);
				//(GetRandomDouble(Creator_MinSpeed,Creator_MaxSpeed));
			}
			else
			{
				IncreaseCountOfFailures();
				SetNextTime(GetRandomDouble(Creator_MinSpeed,Creator_MaxSpeed));
				result+="generating of task "+to_string(CountOfCreatedTasks+1)+" was FAILED";
			}
			CountOfCreatedTasks++;
			percent=(CountOfCreatedTasks*100.0)/CountOfTasks;			
		}
		else
		{
			SetState("waiting");
			percent=0.0;
			BarProgress=0.0;
			BarPos=46;
			//SetNextTime(SimulationTime);
			SetNextTime(GetDelay(Creator_MeanDelayOrMinDelay,Creator_MaxDelayOrDeviation,Creator_DelayDistribution));
			CountOfTasks=0;
			CountOfCreatedTasks=0;
			result+="generating of "+to_string(CountOfCreatedTasks)+" tasks was FINISHED";
		}
	}
	return result;
}
void creator::UpdateDataOnScreen()
{	
	ScreenCoordinates.X=0;
	if(GetState()=="working")
	{
		ScreenCoordinates.Y=2;
		SetConsoleCursorPosition(console,ScreenCoordinates);
		cout<<AddSpacesToString(GetState(),8)<<"|"<<AddSpacesToString(to_string(IndexesOfRobots.size())+"/"+to_string(CountOfRobots),7)<<"|"<<AddSpacesToString(to_string(StorageOfTasks.size())+"/"+to_string(Creator_MaxQueue),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|"<<AddSpacesToString(to_string(CountOfCreatedTasks)+"/"+to_string(CountOfTasks)+" "+ConvertDoubleToString(percent)+"%",15)<<"|";
		while(BarProgress<100 && BarProgress<percent)
		{
			BarProgress+=BarStep;
			ChangeOutputOnScreenChar(1,BarPos,'|');
			ChangeOutputOnScreenChar(2,BarPos,'|');
			BarPos++;
		}
	}
	else
	{
		ScreenCoordinates.Y=1;
		SetConsoleCursorPosition(console,ScreenCoordinates);
		cout<<"CREATOR | QUEUE |STORAGE|FAIL|   PROGRESS    |                                             "<<AddSpacesToString(GetState(),8)<<"|"<<AddSpacesToString(to_string(IndexesOfRobots.size())+"/"+to_string(CountOfRobots),7)<<"|"<<AddSpacesToString(to_string(StorageOfTasks.size())+"/"+to_string(Creator_MaxQueue),7)<<"|"<<AddSpacesToString(to_string(GetCountOfFailures()),4)<<"|"<<AddSpacesToString(to_string(CountOfCreatedTasks)+"/"+to_string(CountOfTasks)+" "+ConvertDoubleToString(percent)+"%",15)<<"|                                             ";
	}
}