﻿/*7. Одним из недостатков C++ является отсутствие для бизнес-программ встроенного типа для денежных значений, такого, как $173 698 001.32. Такой денежный тип должен иметь возможность для хранения числа с фиксированной десятичной точкой точностью около 17 знаков, которого было бы достаточно для хранения национального долга в долларах и центах. К счастью, встроенный тип C++ long double имеет точность 19 цифр, поэтому мы можем использовать его как базисный для класса money, даже используя плавающую точку. Однако нам нужно будет добавить возможность ввода и вывода денежных значений с предшествующим им знаком доллара и разделенными запятыми группы по три числа: так проще читать большие числа. Первым делом при разработке такого класса напишем метод mstold(), который принимает денежную строку, то есть строку, представляющую собой некоторое количество денег типа "$1 234 567 890 123.99" в качестве аргумента и возвращает эквивалентное ее значению число типа long double. Вам нужно будет обработать денежную строку как массив символов и, просматривая ее символ за символом, скопировать из нее только цифры (0-9) и десятичную точку в другую строку. Игнорируется все остальное, включая знак доллара и запятые. Затем вы можете использовать библиотечную функцию _atold() (заметим, что здесь название функции начинается с символа подчеркивания — заголовочные файлы STDLIB.H или MATH.H) для преобразования новой строки к числу типа long double. Предполагаем, что денежное значение не может быть отрицательным. Напишите функцию main() для проверки метода mstold(), которая несколько раз получает денежную строку от пользователя и выводит соответствующее число типа long double.*/
#include <iostream>
#include <string.h>
#include <conio.h>
using namespace std;
long long int StrToLongInt(char s[])
{
	int len=strlen(s)-1;
	long long int res=0,mult=1;
	while(len>-1)
	{
		res=res+((s[len]-'0')*mult);
		mult*=10;
		len--;
	}
	return res;
}
long double mstold(char s[])
{
	int len=strlen(s);
	char temp[100];
	int i,j,k,TempLen=0;
	long long int ip,dp;
	long double res;
	for(i=0; i<len && s[i]!='.'; i++)
	{
		k=s[i]-'0';
		temp[i]=0;
		if((k<=9 && k>=0)|| s[i]=='.')
			temp[TempLen++]=s[i];
	}
	temp[TempLen]=0;
	ip=StrToLongInt(temp);
	TempLen=0;
	while(i++<len)
		temp[TempLen++]=s[i];
	temp[TempLen]=0;
	if(TempLen==0)
		return (long double)ip;
	res=(long double)StrToLongInt(temp);
	for(i=1; i<TempLen; i++)
		res/=10;	
	return res+ip;
}
using namespace std;
int main(void)
{
	char ch,str[200];
	cout.setf(ios::fixed);
	do
	{
		cout<<"Sum: ";		
		cin.get(str,200);
		cout<<str<<" = "<<mstold(str);
		cout<<endl<<"enter 1 to continue or 0 to exit: ";
		cin>>ch;
		while(ch!='0' && ch!='1')
		{
			cout<<"enter 0 or 1: ";
			cin>>ch;
		}
		cin.get();
	}while(ch!='0');
	return 0;
}
