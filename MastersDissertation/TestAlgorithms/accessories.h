#pragma once
#include <iostream>
#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    char my_getch(void);
    char my_kbhit(void);
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
    char my_getch(void);
    char my_kbhit(void);
#endif
#include <fstream>
#include <iomanip>
#include <limits.h>
#include <sstream>
#include <cfloat>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <gmp.h>
#include <mpfr.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
using namespace std;
const int FloatingPointNumberPrecision=2;
void InitFloatingPointAndRandomNumbers();
int GetCountOfDigits(int n);
char GetRandomDigit(char min,char max);
int GetRandomInt(int min,int max);
float GetRandomFloat(float min,float max);
double GetRandomDouble(double min, double max);
char GetRandomChar(char min,char max);
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