/* *2. Возведение числа n в степень р — это умножение числа n на себя р раз. Напишите функцию с именем power(), которая в качестве аргументов принимает значение типа double для n и значение типа int для р и возвращает значение типа double. Для аргумента, соответствующего степени числа, задайте значение по умолчанию, равное 2, чтобы при отсутствии показателя степени при вызове функции число n возводилось в квадрат. Напишите функцию main(), которая запрашивает у пользователя ввод аргументов для функции power(), и отобразите на экране результаты ее работы.*/
#include <iostream>
#include <conio.h>
using namespace std;
double power(double n, int p)
{
	double r=1;
	if(p>0)
		r=n*power(n,p-1);	
	return r;
}
int main(void)
{
	double n;
	int p=2,DigitsCount=0,ten,i;
	char ch;
	int *digits=(int*)malloc(10*sizeof(int));
	cout<<"Float number: ";
	cin>>n;
	cout<<"Power: ";
	ch=getche();
	while(ch!=13)
	{
		digits[DigitsCount]=ch-'0';
		DigitsCount++;
		ch=getche();
	}
	if(DigitsCount>0)
	{
		for(i=0,ten=1,DigitsCount--; i<DigitsCount; i++)
			ten*=10;
		for(i=0,p=0,DigitsCount++; i<DigitsCount; i++,ten/=10)
			p=p+digits[i]*ten;
	}
	cout<<endl<<"Result = "<<power(n,p);
	free(digits);
	return 0;
}
