/*5. Напишите функцию с именем hms_to_secs(), имеющую три аргумента типа int: часы, минуты и секунды. Функция должна возвращать эквивалент переданного ей временного значения в секундах (типа long). Создайте программу, которая будет циклически запрашивать у пользователя ввод значения часов, минут и секунд и выводить результат работы функции на экран.*/
#include<iostream>
#include<conio.h>
using namespace std;
long hms_to_secs(int h,int m,int s)
{
	long r=h*3600;
	r=r+(m*60);
	r=r+s;
	return r;
}
int main(void)
{
	int h,m,s;
	long sc;
	char ch;
	do
	{
		cout<<"Hours: ";
		cin>>h;
		cout<<"Minutes: ";
		cin>>m;
		cout<<"Seconds: ";
		cin>>s;
		sc=hms_to_secs(h,m,s);
		cout<<h<<" hours "<<m<<" minutes "<<s<<" seconds = "<<sc<<" seconds.\nPress 0 to exit or 1 to continue: ";
		ch=getche();
		while(ch!='0' && ch!='1')
		{
			cout<<"\nIncorrect choise. Press 0 or 1: ";
			ch=getche();
		}
		putchar('\n');
	}while(ch!='0');
	return 0;
}
