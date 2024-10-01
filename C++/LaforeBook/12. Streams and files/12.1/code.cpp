//*1. Рассмотрите класс Distance из программы ENGLCON, глава 6 «Объекты и классы». Используя цикл, аналогичный приводимому в программе DISKFUN в этой главе, получите несколько значений от пользователя и запишите их в файл. Добавьте их к уже записанным там данным (при их наличии). При окончании пользователем ввода прочитайте файл и выведите на экран все значения.
#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;
class Distance //длина в английской системе
{
	int feet;
	float inches;
	public: //конструктор без аргументов
	Distance():feet(0),inches(0.0){}
	Distance(int ft, float in):feet(ft),inches(in){}
	void getdist() //ввод длины пользователем
	{
		cout<<"Pounds: "; cin>>feet;
		cout<<"Inches: "; cin>>inches;
		while(inches>11.0)
		{
			cout<<"Inches can't be more than 11: ";
			cin>>inches;
		}		
	}
	void showdist(){cout<<feet<<"\'-"<<inches<<'\"';}
	void add_dist(Distance dd1,Distance dd2)
	{
		inches=dd1.inches+dd2.inches;
		feet=0;
		if(inches>=12.0)
		{
			inches-=12.0;
			feet++;
		}
		feet += dd1.feet + dd2.feet;
	}
};
int main()
{
	char ch=0;
	Distance NewDistance;
	fstream file;
	file.open("distances.dat",ios::app | ios::out | ios::in | ios::binary);
	while(ch!='0')
	{
		NewDistance.getdist();
		cout<<"Press 1 to start again or 0 to exit: ";
		file.write(reinterpret_cast<char*>(&NewDistance),sizeof(NewDistance));
		ch=getch();
		while(ch!='0' && ch!='1')		
			ch=getch();
		cout<<ch<<endl;
	}
	cout<<"--------------------FILE:--------------------\n";
	file.seekg(0);
	file.read(reinterpret_cast<char*>(&NewDistance),sizeof(NewDistance));
	while(!file.eof())
	{
		NewDistance.showdist();
		cout<<endl;
		file.read(reinterpret_cast<char*>(&NewDistance),sizeof(NewDistance));
	}
	file.close();
	return 0;
}