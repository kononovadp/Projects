#include "headers/SharedFunctions.h"
int GetRandomInt(int min, int max)
{
	return min+(rand()%(max-min));
}
double GetRandomDouble(double min, double max)
{
    double f=(double)rand()/RAND_MAX;	
    return min+f*(max - min);
}
string ConvertDoubleToString(double number)
{
	stringstream result;
	result<<fixed<<setprecision(2)<<number;
	return result.str();
}
void ChangeOutputOnScreenInt(int line,int column,int FieldWidth,int NewOutput)
{
	ScreenCoordinates.X=column;
    ScreenCoordinates.Y=line;
	SetConsoleCursorPosition(console,ScreenCoordinates);
	cout<<setw(FieldWidth)<<NewOutput;
}
void ChangeOutputOnScreenDouble(int line,int column,int FieldWidth,double NewOutput)
{
	ScreenCoordinates.X=column;
    ScreenCoordinates.Y=line;
	SetConsoleCursorPosition(console,ScreenCoordinates);
	cout<<setw(FieldWidth)<<NewOutput;
}
void ChangeOutputOnScreenChar(int line,int column,char NewOutput)
{	
	ScreenCoordinates.X=column;
    ScreenCoordinates.Y=line;
	SetConsoleCursorPosition(console,ScreenCoordinates);
	cout<<NewOutput;
}
void ChangeOutputOnScreenString(int line,int column,string NewOutput)
{
	ScreenCoordinates.X=column;
    ScreenCoordinates.Y=line;
	SetConsoleCursorPosition(console,ScreenCoordinates);
	cout<<NewOutput;
}
string AddSpacesToString(string str,int NewSize)
{
	for(int i=0; str.length()<NewSize; i++)
		if(i%2==1)
			str.insert(str.begin(),1,' ');
		else
			str+=" ";
	return str;
}
double GetExponentialDistribution(double MeanDelay)
{
	double result=0;
	while(result==0)
		result=GetRandomDouble(0.0,1.0);
	result=-MeanDelay*log(result);
	return result;
}
double GetUniformDistribution(double MinDelay, double MaxDelay)
{
	double result=0;
	while(result==0)
		result=GetRandomDouble(0.0,1.0);
	result=MinDelay+result*(MaxDelay-MinDelay);
	return result;
}
double GetNormalDistribution(double MeanDelay,double DelayDeviation)
{
	static double n2=0.0;
    static int n2_cached=0;
    if(!n2_cached)
    {
        double x,y,r;
        do
        {
            x=2.0*rand()/RAND_MAX-1;
            y=2.0*rand()/RAND_MAX-1;
            r=x*x+y*y;
        }
        while(r==0.0||r>1.0);
        {
            double d=sqrt(-2.0*log(r)/r);
            double n1=x*d;
            n2=y*d;
            double result=n1*DelayDeviation+MeanDelay;
            n2_cached=1;
            return result;
        }
    }
    else
    {
        n2_cached=0;
        return n2*DelayDeviation+MeanDelay;
    }
}
double GetDelay(double MeanTimeOrMinTime,double MaxTimeOrTimeDeviation,char distribution)
{	
	if(distribution=='e')
		return GetExponentialDistribution(MeanTimeOrMinTime);
	else
		if(distribution=='u')
			return GetUniformDistribution(MeanTimeOrMinTime,MaxTimeOrTimeDeviation);
		else
			if(distribution=='n')
				return GetNormalDistribution(MeanTimeOrMinTime,MaxTimeOrTimeDeviation);
			else
				return MeanTimeOrMinTime;
}
void FisherYatesShuffle(int *array,int size)
{
	int i,j,k;
	for(i=size-1; i>=1; i--)
    {
		j=rand()%(i+1); 
        k=array[j];
        array[j]=array[i];
        array[i]=k;
    }
}
int GetCountOfDigits(int n)
{
	if(n==0)
		return 1;
	int i=0;
	while(n>0)
	{
		n/=10;
		i++;
	}
	return i;
}
string CutString(string str,int MaxLength,int MaxCountOfIdDigits)
{
	if(str.length()<=MaxLength)
		return str;
	string id,result;
	int i,n;
	for(i=str.length()-MaxCountOfIdDigits; i<str.length(); i++)
		id+=str[i];
	for(i=0,n=MaxLength-MaxCountOfIdDigits-2; i<n; i++)
		result+=str[i];
	return result+".."+id;	
}
double GetTheShortestRoute(double** matrix,int size,int departure,int destination,vector<int>* TheShortestRoute)
{
	int* route=(int*)malloc(sizeof(int)*size);
	int i,j,k,minindex,end,prev,*visited=(int*)calloc(sizeof(int),size);
	double distance,MinimalDistance,*MinimalDistances=(double*)malloc(sizeof(double)*size);
	for(i=0; i<size; i++)
	{
		route[i]=-1;
		MinimalDistances[i]=10000;
	}
	MinimalDistances[departure]=0;	
	do
	{
		MinimalDistance=10000;
		minindex=10000;		
		for(i=0; i<size; i++)
			if(visited[i]==0 && MinimalDistances[i]<MinimalDistance)
			{
				MinimalDistance=MinimalDistances[i];
				minindex=i;
			}
		if(MinimalDistance<10000)
		{
			for(i=0; i<size; i++)
				if(matrix[minindex][i]>0)
				{
					distance=MinimalDistance+matrix[minindex][i];
					if(distance<MinimalDistances[i])
					{
						MinimalDistances[i]=distance;
						route[i]=minindex;
					}
				}
			visited[minindex]=1;
		}
	}while(MinimalDistance<10000);
	MinimalDistance=MinimalDistances[destination];
	if(TheShortestRoute==NULL)
	{
		free(route);
		free(visited);
		free(MinimalDistances);
		return MinimalDistance;
	}
	for(i=0; i<size; i++)
		visited[i]=-1;
	for(i=destination,j=0; route[i]!=-1; i=route[i],j++)		
		visited[j]=route[i];
	for(j--; j>-1; j--)
		TheShortestRoute->push_back(visited[j]);
	TheShortestRoute->push_back(destination);
	free(route);
	free(visited);
	free(MinimalDistances);
	return MinimalDistance;
}