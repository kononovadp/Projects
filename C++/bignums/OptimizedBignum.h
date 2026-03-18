#include "RandomBignum.h"
extern int MaxBignumLength;
extern int MaxFractPartLength;
void decimal_str_to_mpq(char *bignum, mpq_t& out);
char* mpq_to_decimal_str(mpq_t q);
int power(mpq_t rop, const mpq_t base, const mpq_t exp);
int validate_power_comprehensive(const mpq_t result, const mpq_t base, const mpq_t exp, double tolerance);
class OptimizedBignum
{
	public:
	OptimizedBignum();
	char* plus(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
	char* minus(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
	char* multiply(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
	char* divide(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);	
};

