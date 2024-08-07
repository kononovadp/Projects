#include "../../UserFunctions.h"
const int SZ=1000;
const int DevisionPrecision=10;
extern bool IntegerDivision;
class verylong
{	
	char vlstr[SZ]; //число как строка
	int vlen; //длина строки verylong
	verylong multdigit(const int) const; //прототипы скрытых функций
	verylong mult10(const verylong) const;
	public:
	verylong(): vlen(0){vlstr[0]='\0';}
	verylong(const char s[SZ])
	{		
		strcpy(vlstr,s);
		vlen=strlen(s);
	}
	verylong(const unsigned long n)
	{
		ltoa(n,vlstr,10);
		//strrev(vlstr); //перевернуть ее
		vlen=strlen(vlstr); //найти длину
	}	
	void putvl() const; //вывести число
	void display();
	void getvl(); //получить число от пользователя
	char GetRandomDigit(char min,char max);
	verylong GetRandomIntBignum(verylong&,verylong&);
	verylong GetRandomSignedIntBignum(verylong&,verylong&);
	verylong OperatorPlusWithoutStrrev(verylong&,verylong&);	
	void DeleteSignMinus(verylong&);
	void AddSignMinus(verylong&);
	void AddChar(verylong&,char);
	void SwapOperands(verylong&,verylong&);
	void CopyVerylong(verylong&,verylong&);
	verylong operator+(verylong&);
	verylong operator*(verylong&);
	bool operator<(const verylong&);
	bool operator>(const verylong&);
	bool operator!=(const verylong&);
	bool operator==(const verylong&);
	verylong operator-(verylong&);
	verylong operator/(verylong&);
};