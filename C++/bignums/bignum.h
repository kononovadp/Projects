#include "OptimizedBignum.h"
extern int MaxBignumLength;
extern int MaxFractPartLength;
class bignum
{
	public:
	bignum();	
	char* plus(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
	char* minus(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
	char* multiply(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
	char* divide(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
};


