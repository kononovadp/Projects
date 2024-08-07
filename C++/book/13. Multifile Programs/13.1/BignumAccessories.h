#include "../UserFunctions.h"
#include "bignum.h"
#include <algorithm>
void AddZerosAndNumber(char* recipient, int ZeroPosition, int ZeroCount,char* source,int SourceLength);
int GetCharacterPosition(char* array,int size,char ch);
void SwapOperands(bignum*& op1,bignum*& op2);
int JustifyNumbers(char*& op1,char*& op2,char* source1,char* source2,int& Source1Length,int& Source2Length,bool& DeleteOperand1,bool& DeleteOperand2);
char GetRandomDigit(char min,char max);