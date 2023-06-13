#include "headers/device.h"
device::device()
{	
	state="waiting";
	LineNumber=3;
	ColumnNumber=0;
	TimeParts=NULL;
	NextTime=DBL_MAX;
	CountOfFailures=0;
	OutputFile.open("logs//Creator.txt");
	OutputFile.precision(2);
	OutputFile.setf(ios::fixed);	
}
device::device(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double reliability,int CountOfBreakdowns)
{	
	ClassName=NewClassName;
	id=NewId;
	index=NewIndex;
	LineNumber=NewLineNumber;
	ColumnNumber=NewColumnNumber+9;
	GenerateTimeLine(reliability,CountOfBreakdowns);
	NumberOfTimeInterval=1;
	state="waiting";
	NextTime=DBL_MAX;
	CountOfFailures=0;
	OutputFile.open("logs//"+ClassName+" "+id+".txt");
	OutputFile.precision(2);
	OutputFile.setf(ios::fixed);	
	cout<<AddSpacesToString(id,8)<<"|";
}
device::~device()
{
	if(TimeParts!=NULL)
		delete(TimeParts);
	OutputFile.close();
}
string device::GetId(){return id;}
int device::GetIndex(){return index;}
string device::GetClassName(){return ClassName;}
int device::GetLineNumber(){return LineNumber;};
int device::GetColumnNumber(){return ColumnNumber;}
double device::GetTimeOfTheNextState(){return TimeParts[NumberOfTimeInterval];}
void device::SetTimeOfTheNextState(double NewNextTime){TimeParts[NumberOfTimeInterval]=NewNextTime;};
string device::GetState(){return state;}
void device::SetState(string NewState){state=NewState;}
double device::GetNextTime(){return NextTime;}
void device::SetNextTime(double NewNextTime)
{
	TimeInterval=NewNextTime;
	NextTime=CurrentTime+NewNextTime;
}
int device::GetCountOfFailures(){return CountOfFailures;}
void device::IncreaseCountOfFailures(){CountOfFailures++;}
string device::TakeOneStep(){return "";}
void device::UpdateDataOnScreen(){}
bool device::AddTask(int NewId){return true;}
bool device::AddTask(int NewId,double NewWorkTime){return true;}
void device::AddDelay(double NewNextTime){}
void device::GenerateTimeLine(double reliability,int CountOfBreakdowns)
{
	double ActiveTime=reliability*SimulationTime,UnactiveTime=SimulationTime-ActiveTime;
	double CountOfBreakdownsDouble=(double)CountOfBreakdowns,TimePart;
	double MinActiveTime=ActiveTime/(CountOfBreakdownsDouble*2);
	double MaxActiveTime=ActiveTime/CountOfBreakdownsDouble;
	double MinUnactiveTime=UnactiveTime/(CountOfBreakdownsDouble*2);
	double MaxUnactiveTime=UnactiveTime/CountOfBreakdownsDouble;
	int i,ActiveTimeIndex=1,UnactiveTimeIndex=2;
	int TimePartsSize=CountOfBreakdowns*2+2;
	TimeParts=new double[TimePartsSize];
	for(i=0; i<TimePartsSize; i++)
		TimeParts[i]=0;			
	while(ActiveTime>MaxActiveTime && UnactiveTime>MaxUnactiveTime)
	{
		TimePart=GetRandomDouble(MinActiveTime,MaxActiveTime);
		TimeParts[ActiveTimeIndex]+=TimePart;
		ActiveTime-=TimePart;
		ActiveTimeIndex+=2;
		TimePart=GetRandomDouble(MinUnactiveTime,MaxUnactiveTime);
		TimeParts[UnactiveTimeIndex]+=TimePart;
		UnactiveTime-=TimePart;
		UnactiveTimeIndex+=2;		
		if(ActiveTimeIndex>=TimePartsSize)
			ActiveTimeIndex=1;
		if(UnactiveTimeIndex>=TimePartsSize)
			UnactiveTimeIndex=2;
	}
	TimeParts[ActiveTimeIndex]+=ActiveTime;
	TimeParts[UnactiveTimeIndex]+=UnactiveTime;
	TimeParts[TimePartsSize-1]=DBL_MAX;	
	for(ActiveTimeIndex=0,i=1; i<TimePartsSize-1; ActiveTimeIndex++,i++)
		TimeParts[i]+=TimeParts[ActiveTimeIndex];
}
string device::SwitchState()
{
	string result=ClassName+" "+id+": the state was changed to ";
	if(state!="BROKEN ")
	{
		PrevState=state;
		state="BROKEN ";
		result+="BROKEN ";
	}
	else
	{
		state=PrevState;		
		result+="active";
		if(NextTime<CurrentTime)
			NextTime=CurrentTime+TimeInterval;
	}
	NumberOfTimeInterval++;
	WriteToFile(result);
	return result;
}
void device::UpdateStateOnScreen()
{
	ChangeOutputOnScreenString(LineNumber,ColumnNumber,state);
}
void device::WriteToFile(string result)
{
	OutputFile<<setw(7)<<CurrentTime<<". "<<result<<endl;
}