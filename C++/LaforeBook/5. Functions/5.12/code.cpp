/*12. Модифицируйте калькулятор, созданный в упражнении 12 главы 4, так, чтобы каждая арифметическая операция выполнялась с помощью функции. Функции могут называться fadd(), fsub(), fmul() и fdiv(). Каждая из функций должна принимать два структурных аргумента типа fraction и возвращать значение того же типа.*/
#include <iostream>
#include <conio.h>
using namespace std;
struct fract
{
	int numerator,denominator;
};
double fadd(fract f1,fract f2)
{
	double res=(f1.numerator*f2.denominator)+(f1.denominator*f2.numerator);
	return res/(f1.denominator*f2.denominator);
}
double fsub(fract f1,fract f2)
{
	double res=(f1.numerator*f2.denominator)-(f1.denominator*f2.numerator);
	return res/(f1.denominator*f2.denominator);
}
double fmul(fract f1,fract f2)
{
	double res=f1.numerator*f2.numerator;
	return res/(f1.denominator*f2.denominator);;
}
double fdiv(fract f1,fract f2)
{
	double res=f1.numerator*f2.denominator;
	return res/(f1.denominator*f2.numerator);
}
int main(void)
{
	struct fract f1,f2;
	char op,ch=0;
	double res;
	while(ch!='n')
	{		
		ch='/';
		cout<<"Enter fraction,operation and second fraction: ";		
		cin>>f1.numerator>>ch>>f1.denominator>>op>>f2.numerator>>ch>>f2.denominator;
		switch(op)
		{
			case '+': res=fadd(f1,f2); break;
			case '-': res=fsub(f1,f2); break;
			case '*': res=fmul(f1,f2); break;
			case '/': res=fdiv(f1,f2); break;
		}
		cout<<"Result: "<<res;
		cout<<endl<<"Do you want to continue (y/n)? ";
		ch=getche();
		while(ch!='y' && ch!='n')
		{
			cout<<endl<<"press y or n: ";
			ch=getche();
		}
		cout<<endl;
	}	
	return 0;
}
