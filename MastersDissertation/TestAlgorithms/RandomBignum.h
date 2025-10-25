#include "accessories.h"
extern const int MaxBignumLength;
extern const int MaxFractPartLength;
int GetPointPosition(char* number,int length);
bool IsLess(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
bool IsGreater(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
bool IsEqual(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
bool IsNotEqual(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
void DisplayBignum(char* number,int length);
void SetRandomIntBignum(char* number,int& length,char* min,char* max,int MinPointPos,int MaxPointPos);
void SetRandomFloatBignum(char* number,int& length,char* min,char* max,int MinPointPos,int MaxPointPos);
inline void SetRandomUnsignedBignum(char* number,int& length,char* min,char* max,bool SignMinus);
char* GetRandomBignum(int length,bool SignMinus,bool FloatingPoint);
char* GetRandomBignum(char* min,char* max);
void SwapBignums(char*& bignum1,int& Bignum1Length,char*& bignum2,int& Bignum2Length);