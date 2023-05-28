#include "SharedFunctions.h"
class device
{	
	ofstream OutputFile;
	int index,LineNumber,ColumnNumber,NumberOfTimeInterval,CountOfFailures;
	string id,ClassName,PrevState,state;
	double NextTime,TimeInterval,*TimeParts;
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
	virtual void AddDelay(double NewNextTime);
	virtual string TakeOneStep();
	virtual void UpdateDataOnScreen();
	void WriteToFile(string result);
	void UpdateStateOnScreen();	
};