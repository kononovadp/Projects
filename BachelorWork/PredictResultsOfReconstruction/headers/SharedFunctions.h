#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <random>
#include <float.h>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <direct.h>
#include <windows.h>
using namespace std;
extern HANDLE console;
extern COORD ScreenCoordinates;
struct StructCity
{
	string name;
	int CountOfIncompleteConstructions;
	bool operator <(StructCity city2)
	{
        int MinLength;
		if(name.length()<city2.name.length())
			MinLength=name.length();
		else
			MinLength=city2.name.length();
		for(int i=0; i<MinLength; i++)
			if(name[i]<city2.name[i])
				return true;
			else
				if(name[i]>city2.name[i])
					return false;
		return true;
    }
};
//---------------------------------------------
int GetRandomInt(int min, int max);
double GetRandomDouble(double min, double max);
double GetPercentage(double number,double percentage);
double GetPercentageOfNumber1FromNumber2(double number1,double number2);
double AddPercentage(double number,double percentage);
double SubtractPercentage(double number,double percentage);
string ConvertDoubleToString(double number,int precision);
void ChangeOutputOnScreenInt(int line,int column,int FieldWidth,int NewOutput);
void ChangeOutputOnScreenDouble(int line,int column,int FieldWidth,double NewOutput);
void ChangeOutputOnScreenChar(int line,int column,char NewOutput);
void ChangeOutputOnScreenString(int line,int column,string NewOutput);
double GetExponentialDistribution(double MeanDelay);
double GetUniformDistribution(double MinDelay, double MaxDelay);
double GetNormalDistribution(double MeanDelay,double DelayDeviation);
double GetDelay(double MeanTimeOrMinTime,double MaxTimeOrTimeDeviation,char distribution);
void FisherYatesShuffle(int *array,int size);
string AddSpacesToString(string str,int NewSize);
string CutString(string str,int MaxLength,int MaxCountOfIdDigits);
int GetCountOfDigits(int n);
double GetTheShortestRoute(double** matrix,int size,int departure,int destination,vector<int>* TheShortestRoute);