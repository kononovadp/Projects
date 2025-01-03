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
extern ofstream File_AllEvents,statistics,CreatorStatistics,RobotStatistics,WorkshopStatistics;
extern COORD ScreenCoordinates;
//--------------------CREATOR--------------------
extern char Creator_DelayDistribution;
extern double Creator_MeanDelayOrMinDelay,Creator_MaxDelayOrDeviation,Creator_MinTaskTime,Creator_MaxTaskTime;
extern int Creator_MaxQueue,MinTaskComplexity,MaxTaskComplexity;
//--------------------WORKSHOP--------------------
extern vector<string> NamesOfWorkshops;
extern int CountOfWorkshops,Workshop_MaxCountOfIdDigits,*IndexesOfWorkshops,Workshop_MinSizeOfQueueOfRobots,Workshop_MaxSizeOfQueueOfRobots,Workshop_MinCountOfBreakdowns,Workshop_MaxCountOfBreakdowns;
extern char Workshop_DelayDistribution;
extern double Workshop_MeanDelayOrMinDelay,Workshop_MaxDelayOrDeviation,Workshop_MinReliability,Workshop_MaxReliability;
//--------------------ROUTE--------------------
extern double **matrix;
//--------------------ROBOT--------------------
extern int CountOfRobots,Robot_MinCountOfBreakdowns,Robot_MaxCountOfBreakdowns;
extern char Robot_DelayDistribution;
extern double Robot_MeanDelayOrMinDelay,Robot_MaxDelayOrDeviation,Robot_MinMovementTime,Robot_MaxMovementTime,Robot_MinTaskTime,Robot_MaxTaskTime,Robot_MinReliability,Robot_MaxReliability,Robot_StepSize;
//---------------------------------------------
extern double SimulationTime,CurrentTime;
extern int CountOfAllDevices,LastLineNumber;
//---------------------------------------------
int GetRandomInt(int min, int max);
double GetRandomDouble(double min, double max);
string ConvertDoubleToString(double number);
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