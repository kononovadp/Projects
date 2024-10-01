/*11. Модифицируйте калькулятор, созданный в упражнении 12 главы 5 так, чтобы вместо структуры fraction использовался одноименный класс. Класс должен содержать методы для ввода и вывода данных объектов, а также для выполнения арифметических операций. Кроме того, необходимо включить в состав класса функцию, приводящую дробь к несократимому виду. Функция должна находить наибольший общий делитель числителя и знаменателя и делить числитель и знаменатель на это значение. Код функции, названной lowterms(), приведен ниже:
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
Можно вызывать данную функцию в конце каждого метода, выполняющего арифметическую операцию, либо непосредственно перед выводом на экран результата. Кроме перечисленных методов, вы можете включить в класс конструктор с двумя аргументами, что также будет полезно.*/
#include <iostream>
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
	char op,ch=0;
	double res;
	int f1_num,f1_den,f2_num,f2_den;
	fraction fr;
	while(ch!='n')
	{
		cout<<"First fraction: ";
		cin>>f1_num>>ch>>f1_den;
		cout<<"Second fraction: ";
		cin>>f2_num>>ch>>f2_den;
		cout<<"operation: ";
		op=getche();
		while(op!='+' && op!='-' && op!='*' && op!='/')
		{
			cout<<endl<<"press correct operation: ";
			op=getche();
		}
		fr.calc(f1_num,f1_den,f2_num,f2_den,op);
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
