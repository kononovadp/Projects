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