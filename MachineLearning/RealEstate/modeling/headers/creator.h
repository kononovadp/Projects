#include "SharedFunctions.h"
#ifndef _device_h
#define _device_h
class device
{
	int index,LineNumber,ColumnNumber,NumberOfTimeInterval,CountOfFailures;
	string id,ClassName,PrevState,state;
	double NextTime,*TimeParts;
	void GenerateTimeLine(double reliability,int CountOfBreakdowns);
	public: device();
	device(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double reliability,int CountOfBreakdowns);
	~device();
	struct task
	{
		int performer;
		double WorkTime;
	};
	string GetId();
	int GetIndex();
	string GetClassName();
	string GetState();
	void SetState(string NewState);
	string SwitchState();
	double GetTimeOfTheNextState();
	void SetTimeOfTheNextState(double NewNextTime);	
	double GetNextTime();
	void SetNextTime(double NewNextTime);
	int GetLineNumber();
	int GetColumnNumber();
	int GetCountOfFailures();
	void IncreaseCountOfFailures();
	virtual bool AddTask(int NewId);
	virtual bool AddTask(int NewId,double NewWorkTime);
	virtual string TakeOneStep();
	virtual void UpdateDataOnScreen();
	void UpdateStateOnScreen();	
};
#endif
#ifndef _workshop_h
#define _workshop_h
class workshop: public device
{
	int MaxQueueOfDevices,BarSize,BarPos,TaskNumber,CurrentRobot;
	double WorkSpeed,WorkTime,WorkProgress,percent,BarProgress,BarStep;
	device** AllRobots;
	queue<struct task*> tasks;
	public: workshop(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double reliability,int CountOfBreakdowns,double NewWorkSpeed,int NewMaxQueueOfDevices,device** NewRobots);
	bool AddTask(int RobotIndex,double WorkTime);
	string TakeOneStep();
	void UpdateDataOnScreen();
};
#endif
#ifndef _robot_h
#define _robot_h
class robot: public device
{
	string location;
	int CountOfTasks,CountOfFinishedTasks,CountOfVisitedWorkshops,BarSize,BarPos;
	int CurrentPosition,CurCountOfRoutes,CountOfTraversedRoutes;
	double SpeedOfLoading,SpeedOfMovement,percent,BarProgress,BarStep;
	double TotalDistance,TraversedTotalDistance,CurrentDistance,TraversedCurrentDistance;
	vector<struct task*> tasks;
	vector<int> route;
	device* creator;
	workshop** workshops;
	vector<int> TheShortestRoute;
	public: robot(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double reliability,int CountOfBreakdowns,double NewSpeedOfLoading,double NewSpeedOfMovement,device* NewCreator,workshop** NewWorkshops);
	~robot();
	bool AddTask(int workshop,double WorkTime);
	string TakeOneStep();
	void UpdateDataOnScreen();	
};
#endif
class creator: public device
{
	int CountOfTasks,CountOfCreatedTasks,BarSize,BarPos;
	double percent,BarProgress,BarStep;
	queue<queue<task>> StorageOfTasks;
	robot** robots;
	vector<int> IndexesOfRobots;
	public: creator(robot** NewRobots);
	bool AddTask(int NewId);
	string TakeOneStep();
	void UpdateDataOnScreen();
};