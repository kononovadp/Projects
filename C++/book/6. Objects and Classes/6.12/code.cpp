/*12. Используйте преимущество ООП, заключающееся в том, что однажды созданный класс можно помещать в другие программы. Создайте новую программу, которая будет включать класс fraction, созданный в упражнении 11. Программа должна выводить аналог целочисленной таблицы умножения для дробей. Пользователь вводит знаменатель, а программа должна подобрать всевозможные целые значения числителя так, чтобы значения получаемых дробей находились между 0 и 1. Дроби из получившегося таким образом набора перемножаются друг с другом во всевозможных комбинациях, в результате чего получается таблица следующего вида (для знаменателя, равного 6):
1/6 1/3 1/2 2/3 5/6
-----------------------------------------
1/6 1/36 1/18 1/12 1/9 5/36
1/3 1/18 1/9 1/6 2/9 5/18
1/2 1/12 1/6 1/4 1/3 5/12
2/3 1/9 2/9 1/3 4/9 5/9
5/6 5/36 5/18 5/12 5/9 25/36*/
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <cmath>
using namespace std;
class fraction
{
	int num,den;
	struct fract
	{
		long num,den;
	};
	fract f1,f2;
	char operation;
	public:
	void lowterms();
	void fadd()
	{
		num=f1.num*f2.den+f1.den*f2.num;
		den=f1.den*f2.den;
	}
	void fsub()
	{
		num=f1.num*f2.den-f1.den*f2.num;
		den=f1.den*f2.den;
	}
	void fmul()
	{
		num=f1.num*f2.num;
		den=f1.den*f2.den;
	}
	void fdiv()
	{
		num=f1.num*f2.den;
		den=f1.den*f2.num;
	}
	void calc(int f1_num,int f1_den,int f2_num,int f2_den,char op)
	{
		f1.num=f1_num;
		f1.den=f1_den;
		f2.num=f2_num;
		f2.den=f2_den;
		operation=op;
		switch(operation)
		{
			case '+': fadd(); break;
			case '-': fsub(); break;
			case '*': fmul(); break;
			case '/': fdiv(); break;
		}
		cout<<endl<<f1.num<<'/'<<f1.den<<' '<<operation<<' '<<f2.num<<'/'<<f2.den<<" = "<<num<<'/'<<den;		
		lowterms();
		cout<<" = "<<num<<'/'<<den<<endl;
	}
	void MultiplicationTable(int n)
	{
		int i,j;
		for(i=1,f1.den=n,f2.den=n; i<=n; i++)
		{
			f1.num=i;
			for(j=1; j<=n; j++)
			{
				f2.num=j;
				fmul();
				lowterms();
				cout<<setw(3)<<right<<num<<"/"<<setw(3)<<left<<den<<right<<setw(5);
			}
			cout<<setw(0)<<endl;
		}
	}
};
void fraction::lowterms() //сокращение дроби
{
	long tnum, tden, temp, gcd;
	tnum = labs(num); //используем неотрицательные
	tden = labs(den); //значения (нужен cmath)
	if(tden == 0) //проверка знаменателя на 0
	{
		cout << "Недопустимый знаменатель!"; exit(1);
	}
	else
		if(tnum == 0) //проверка числителя на 0
		{
			num = 0; den = 1;
			return;
		}
//нахождение наибольшего общего делителя
	while(tnum != 0)
	{
		if(tnum < tden) //если числитель больше знаменателя,
		{
			temp = tnum;
			tnum = tden;
			tden = temp; //меняем их местами
		}
		tnum = tnum - tden; //вычитание
	}
	gcd = tden; //делим числитель и знаменатель на
	num = num / gcd; //полученный наибольший общий делитель
	den = den / gcd;
}
int main(void)
{
	fraction mp;
	mp.MultiplicationTable(6);
	return 0;
}
