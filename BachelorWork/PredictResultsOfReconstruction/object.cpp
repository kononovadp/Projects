#include "headers/model.h"
object::object(double NewSimulationTime,char NewDelayDistribution,double NewMeanDelayOrMinDelay,double NewMaxDelayOrDeviation)
{	
	SimulationTime=NewSimulationTime;
	DelayDistribution=NewDelayDistribution;
	MeanDelayOrMinDelay=NewMeanDelayOrMinDelay;
	MaxDelayOrDeviation=NewMaxDelayOrDeviation;
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
object::object(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double NewSimulationTime,char NewDelayDistribution,double NewMeanDelayOrMinDelay,double NewMaxDelayOrDeviation,double reliability,int CountOfBreakdowns)
{	
	ClassName=NewClassName;
	id=NewId;
	index=NewIndex;
	LineNumber=NewLineNumber;
	ColumnNumber=NewColumnNumber;
	GenerateTimeLine(reliability,CountOfBreakdowns);
	NumberOfTimeInterval=1;
	state="waiting";
	NextTime=DBL_MAX;
	CountOfFailures=0;
	OutputFile.open("logs//"+ClassName+" "+id+".txt");
	OutputFile.precision(2);
	OutputFile.setf(ios::fixed);	
}
object::~object()
{
	if(TimeParts!=NULL)
		delete(TimeParts);
	OutputFile.close();
}
string object::GetId(){return id;}
int object::GetIndex(){return index;}
string object::GetClassName(){return ClassName;}
int object::GetLineNumber(){return LineNumber;};
int object::GetColumnNumber(){return ColumnNumber;}
double object::GetTimeOfTheNextState(){return TimeParts[NumberOfTimeInterval];}
void object::SetTimeOfTheNextState(double NewNextTime){TimeParts[NumberOfTimeInterval]=NewNextTime;};
string object::GetState(){return state;}
void object::SetState(string NewState){state=NewState;}
double object::GetNextTime(){return NextTime;}
void object::SetNextTime(double CurrentTime,double NewNextTime)
{
	TimeInterval=NewNextTime;
	NextTime=CurrentTime+NewNextTime;
}
int object::GetCountOfFailures(){return CountOfFailures;}
void object::IncreaseCountOfFailures(){CountOfFailures++;}
string object::TakeOneStep(){return "";}
void object::UpdateDataOnScreen(){}
bool object::AddTask(int NewId){return true;}
bool object::AddTask(int NewId,double NewWorkTime){return true;}
void object::AddDelay(double NewNextTime){}
void object::GenerateTimeLine(double reliability,int CountOfBreakdowns)
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
string object::SwitchState(double CurrentTime)
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
	WriteToFile(CurrentTime,result);
	return result;
}
void object::UpdateStateOnScreen()
{
	//ChangeOutputOnScreenString(LineNumber,ColumnNumber,state);
}
void object::WriteToFile(double CurrentTime,string result)
{
	OutputFile<<setw(7)<<CurrentTime<<". "<<result<<endl;
}