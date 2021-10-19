/*10. Создайте класс с именем ship, который будет содержать данные об учетном номере корабля и координатах его расположения. Для задания номера корабля следует использовать механизм, аналогичный описанному в упражнении 8. Для хранения координат используйте два поля типа angle (см. упражнение 7). Разработайте метод, который будет сохранять в объекте данные о корабле, вводимые пользователем, и метод, выводящий данные о корабле на экран. Напишите функцию main(), создающую три объекта класса ship, затем запрашивающую ввод пользователем информации о каждом из кораблей и выводящую на экран всю полученную информацию.*/
#include <iostream>
#include <conio.h>
using namespace std;
class ship
{
	int ID;
	class angle
	{
		int degree;
		double minutes;
		char direction;	
		public:
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
	angle longitude,latitude;
	public:
	ship(int n,int lo_de,double lo_mi,char lo_di,int la_de,double la_mi,char la_di):ID(n)
	{
		longitude.SetData(lo_de,lo_mi,lo_di);
		latitude.SetData(la_de,la_mi,la_di);
	}	
	void ShowData()
	{
		cout<<"Ship "<<ID<<": longitude ";
		longitude.ShowData();
		cout<<"; latitude: ";
		latitude.ShowData();
		cout<<endl;
	}
};
ship* GetShipInf()
{
	int id,lo_de,la_de;
	double lo_mi,la_mi;
	char lo_di,la_di;
	cout<<"Ship's ID: ";
	cin>>id;
	cout<<"longitude:"<<endl<<"degree (0-180): ";
	cin>>lo_de;
	while(lo_de<0 || lo_de>180)
	{
		cout<<"enter correct degree (0-180): ";
		cin>>lo_de;
	}
	cout<<"minutes (0-60): ";
	cin>>lo_mi;
	while(lo_mi<0 || lo_mi>59)
	{
		cout<<"enter correct minutes (0-59): ";
		cin>>lo_mi;
	}
	cout<<"direction (W or E): ";
	lo_di=getche();
	while(lo_di!='W' && lo_di!='E')
	{
		cout<<endl<<"press correct direction (W or E): ";
		lo_di=getche();
	}	
	cout<<endl<<"latitude:"<<endl<<"degree (0-180): ";
	cin>>la_de;
	while(la_de<0 || la_de>180)
	{
		cout<<"enter correct degree (0-180): ";
		cin>>la_de;
	}
	cout<<"minutes (0-60): ";
	cin>>la_mi;
	while(la_mi<0 || la_mi>59)
	{
		cout<<"enter correct minutes (0-59): ";
		cin>>la_mi;
	}
	cout<<"direction (S or N): ";
	la_di=getche();
	while(la_di!='S' && la_di!='N')
	{
		cout<<endl<<"press correct direction (W or E): ";
		la_di=getche();
	}
	ship *res=new ship(id,lo_de,lo_mi,lo_di,la_de,la_mi,la_di);
	return res;
}
int main(void)
{
	cout<<"Ship 1:"<<endl;
	ship *s1=GetShipInf();
	cout<<endl<<"Ship 2:"<<endl;
	ship *s2=GetShipInf();
	cout<<endl<<"Ship 3:"<<endl;
	ship *s3=GetShipInf();
	cout<<endl;
	s1->ShowData();
	s2->ShowData();
	s3->ShowData();
	return 0;
}
