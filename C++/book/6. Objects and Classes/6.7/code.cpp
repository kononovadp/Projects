/*7. В морской навигации координаты точки измеряются в градусах и минутах широты и долготы. Например, координаты бухты Папити на о. Таити равны 149 градусов 34.8 минут восточной долготы и 17 градусов 31.5 минут южной широты. Это записывается как 149°34.8' W, 17°31.5' S. Один градус равен 60 минутам (устаревшая система также делила одну минуту на 60 секунд, но сейчас минуту делят на обычные десятичные доли). Долгота измеряется величиной от 0 до 180 градусов восточнее или западнее Гринвича. Широта принимает значения от 0 до 90 градусов севернее или южнее экватора. Создайте класс angle, включающий следующие три поля: типа int для числа градусов, типа float для числа минут и типа char для указания направления (N, S, Е или W). Объект этого класса может содержать значение как широты, так и долготы. Создайте метод, позволяющий ввести координату точки, направление, в котором она измеряется, и метод, выводящий на экран значение этой координаты, например 179°59.9' Е. Кроме того, напишите конструктор, принимающий три аргумента. Напишите функцию main(), которая сначала создает переменную с помощью трехаргументного конструктора и выводит ее значение на экран, а затем циклически запрашивает пользователя ввести значение координаты и отображает введенное значение на экране. Для вывода символа градусов (°) можно воспользоваться символьной константой '\xF8'.*/
#include <iostream>
#include <conio.h>
using namespace std;
class angle
{
	int degree;
	double minutes;
	char direction;	
	public:
	angle(int de,double m,char di):degree(de),minutes(m),direction(di){}
	void SetData(int de,double m,char di)
	{
		degree=de;
		minutes=m;
		direction=di;
	}
	void ShowData()
	{
		cout<<degree<<"\xB0"<<minutes<<'\''<<direction;
	}
};
int main(void)
{	
	char d;
	int de;
	double m;
	angle a(179,59.9,'S');
	a.ShowData();
	do
	{
		cout<<endl<<"degree: ";
		cin>>de;
		while(de<0 || de>180)
		{
			cout<<"enter coorect degree from 0 to 180: ";
			cin>>de;
		}
		cout<<"minutes: ";
		cin>>m;
		while(m<0 || m>59)
		{
			cout<<"enter correct minutes from 0 to 59: ";
			cin>>m;
		}
		cout<<"direction: ";
		d=getche();
		while(d!='N' && d!='S' && d!='E' && d!='W')
		{
			cout<<endl<<"press N or S or E or W: ";
			d=getche();
		}
		a.SetData(de,m,d);
		cout<<endl<<"you entered ";
		a.ShowData();
		cout<<endl<<"press 1 to continue or 0 to stop: ";
		d=getche();
		while(d!='0' && d!='1')
		{
			cout<<endl<<"press 1 to continue or 0 to stop: ";
			d=getche();
		}
	}while(d!='0');
	return 0;
}
