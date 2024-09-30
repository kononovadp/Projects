/*2. Напишите программу, предлагающую пользователю осуществить перевод температуры из шкалы Цельсия в шкалу Фаренгейта или наоборот, а затем осуществите преобразование. Используйте в программе переменные вещественного типа. Взаимодействие программы с пользователем может выглядеть следующим образом:
Нажмите 1 для перевода шкалы Цельсия в шкалу Фаренгейта.
2 для перевода шкалы Фаренгейта в шкалу Цельсия: 2
Введите температуру по Фаренгейту: 70
Значение по Цельсию: 21.111111*/
#include <iostream>
#include <conio.h>
using namespace std;
int main(void)
{
	char ch;
	double t;
	cout<<"Press 1 to convert Celsius temperature into degree Fahrenheit or"<<endl;
	cout<<"press 2 to convert Fahrenheit temperature into Celsius degree: ";
	ch=getche()-'0';
	if(ch==1)
		cout<<"\nEnter Celsius temperature: ";
	else
		if(ch==2)
			cout<<"\nEnter Fahrenheit temperature: ";
		else
		{
			cout<<"\nIncorrect choise.";
			return 0;
		}
	cin>>t;
	if(ch==1)
		cout<<"Fahrenheit temperature: "<<t*1.8+32;
	else
		cout<<"Celsius temperature: "<<(t-32)/1.8;
	return 0;
}
