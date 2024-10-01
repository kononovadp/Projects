/*5. Начните с класса fraction из упражнений 11 и 12 главы 6. Напишите функцию main(), которая получает случайные дробные числа от пользователя, сохраняет их в массиве типа fraction, вычисляет среднее значение и выводит результат.*/
#include <iostream>
#include <conio.h>
using namespace std;
class fraction
{
	int num,den;
	public:
	void lowterms();
	fraction():num(0),den(0){}
	fraction(int n,int d):num(n),den(d){}
	void fadd(fraction fr)
	{
		if(num==0 || den==0)
		{
			if(num==0)
				num=fr.num;
			if(den==0)
				den=fr.den;
		}
		else
		{
			num=num*fr.den+den*fr.num;
			den=den*fr.den;
		}
		lowterms();
	}
	void fdiv(fraction fr)
	{
		if(fr.den==0)
			fr.den=1;			
		num=num*fr.den;
		den=den*fr.num;
	}
	void show()
	{
		cout<<num<<'/'<<den;
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
	const int n=3;
	fraction fr[n];
	fraction AverageFraction,devider(n,0);
	int i,num,den;
	char ch;
	cout<<"Enter "<<n<<" fractions:"<<endl;
	for(i=0; i<n; i++)
	{
		cout<<"fraction "<<i+1<<": ";
		cin>>num>>ch>>den;
		while(num==0 || den==0)
		{
			cout<<"numerator or denominator can't be 0, try again: ";
			cin>>num>>ch>>den;
		}
		fr[i]=fraction(num,den);
		AverageFraction.fadd(fr[i]);
	}
	cout<<"sum: ";
	AverageFraction.show();	
	AverageFraction.fdiv(devider);
	cout<<"; average fraction: ";
	AverageFraction.show();
	return 0;
}
