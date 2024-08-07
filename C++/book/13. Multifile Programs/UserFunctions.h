#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <sstream>
#include <cfloat>
#include <cstring>
using namespace std;
const int FloatingPointNumberPrecision=2;
void InitFloatingPointAndRandomNumbers();
int GetCountOfDigits(int n);
int GetRandomInt(int min,int max);
char GetRandomChar(char min,char max);
float GetRandomFloat(float min,float max);
double GetRandomDouble(double min, double max);
void ShuffleArrayOfCharacters(char* array);
void ShuffleArrayOfIntegers(int* array,int ArraySize);
void ShuffleString(string& str);
string GetKeyboardInputAsString();
string GetKeyboardInputAsString(char* ExcludedCharacters);
char* GetKeyboardInputAsArrayOfChars();
int GetIntFromKeyboard();
int GetIntFromKeyboard(int MinInt,int MaxInt);
long GetLongFromKeyboard();
long GetLongFromKeyboard(long MinInt,long MaxInt);
float GetFloatFromKeyboard();
long double GetLongDoubleFromKeyboard();