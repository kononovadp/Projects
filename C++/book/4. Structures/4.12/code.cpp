/*12. Переработайте программу-калькулятор для дробей, описанную в упражнении 12 главы 3 так, чтобы каждая из дробей хранилась как значение переменной типа struct fraction, по аналогии с упражнением 8 этой главы.*/
#include <iostream>
#include <conio.h>
using namespace std;
int main(void)
{
	struct fract
	{
		int numerator;
		int denominator;
	};
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
			case '+': res=(f1.numerator*f2.denominator)+(f1.denominator*f2.numerator);
			res=res/(f1.denominator*f2.denominator);break;
			case '-': res=(f1.numerator*f2.denominator)-(f1.denominator*f2.numerator);
			res=res/(f1.denominator*f2.denominator); break;
			case '*': res=f1.numerator*f2.numerator;
			res=res/(f1.denominator*f2.denominator); break;
			case '/': res=f1.numerator*f2.denominator;
			res=res/(f1.denominator*f2.numerator); break;
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
