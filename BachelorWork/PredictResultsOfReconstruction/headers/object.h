class object
{	
	ofstream OutputFile;
	char DelayDistribution;
	double SimulationTime,MeanDelayOrMinDelay,MaxDelayOrDeviation,NextTime,TimeInterval,*TimeParts;
	int index,LineNumber,ColumnNumber,NumberOfTimeInterval,CountOfFailures;
	string id,ClassName,PrevState,state;	
	void GenerateTimeLine(double reliability,int CountOfBreakdowns);
	public: object(double NewSimulationTime,char NewDelayDistribution,double NewMeanDelayOrMinDelay,double NewMaxDelayOrDeviation);
	object(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double NewSimulationTime,char NewDelayDistribution,double NewMeanDelayOrMinDelay,double NewMaxDelayOrDeviation,double reliability,int CountOfBreakdowns);
	~object();
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
	string SwitchState(double CurrentTime);
	double GetTimeOfTheNextState();
	void SetTimeOfTheNextState(double NewNextTime);	
	double GetNextTime();
	void SetNextTime(double CurrentTime,double NewNextTime);
	int GetLineNumber();
	int GetColumnNumber();
	int GetCountOfFailures();
	void IncreaseCountOfFailures();
	virtual bool AddTask(int NewId);
	virtual bool AddTask(int NewId,double NewWorkTime);
	virtual void AddDelay(double NewNextTime);
	virtual string TakeOneStep();
	virtual void UpdateDataOnScreen();
	void WriteToFile(double CurrentTime,string result);
	void UpdateStateOnScreen();	
};