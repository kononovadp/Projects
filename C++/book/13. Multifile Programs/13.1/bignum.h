#include "../UserFunctions.h"
#include <algorithm>
extern int MaxLength;
extern int MaxFractPartLength;
class bignum
{	
	char* number;
	int length;
	public:
	bignum();
	~bignum();
	bignum(char*);
	bignum(char*,int);
	void display();
	int GetPointPosition();
	void SetRandomIntBignum(bignum* min,bignum* max,int MinPointPos,int MaxPointPos);
	void SetRandomFloatBignum(bignum* min,bignum* max,int MinPointPos,int MaxPointPos);
	inline void SetRandomUnsignedBignum(bignum* min,bignum* max,bool SignMinus);
	void SetRandomBignum(bignum* min,bignum* max);
	void SetRandomBignum(int length,bool SignMinus,bool FloatingPoint);
	bool operator<(bignum* operand2);
	bool operator>(bignum* operand2);
	bool operator==(bignum* operand2);
	bool operator!=(bignum* operand2);
	bignum* operator+(bignum* operand2);
	bignum* operator-(bignum* operand2);
	bignum* operator*(bignum* operand2);
	bignum* operator/(bignum* operand2);
	bool CheckMultiplicationOrDivisionResult();
};
void SwapOperands(bignum*& bignum1,bignum*& bignum2);
char GetRandomDigit(char min,char max);