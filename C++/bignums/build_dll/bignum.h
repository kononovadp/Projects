#include "RandomBignum.h"
int decimal_str_to_mpq(char *str, mpq_t rop);
char* mpq_to_decimal_str(mpq_t q);
char* plus(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
char* minus(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
char* multiply(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);
char* divide(char* bignum1,int Bignum1Length,char* bignum2,int Bignum2Length);



