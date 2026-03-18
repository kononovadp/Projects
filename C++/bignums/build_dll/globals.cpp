#include "globals.h"
int MinCountOfDigits=1;
int MaxCountOfDigits=10;
int CountOfExpressions=1000;
int MinCountOfOperations=1;
int MaxCountOfOperations=10;
int MaxFractPartLength=MaxCountOfDigits;
int MaxBignumLength=MaxCountOfDigits+MaxFractPartLength;
DLL_EXPORT void UpdateLimits(void)
{
    if (MaxCountOfDigits < 1)
        MaxCountOfDigits = 1;
    MaxFractPartLength = MaxCountOfDigits;
    MaxBignumLength    = MaxCountOfDigits + MaxFractPartLength;
}

