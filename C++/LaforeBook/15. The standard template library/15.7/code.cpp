//7. В примере PLUSAIR мы показали применение версии accumulate() с четырьмя аргументами. Перепишите этот пример, используя версию с тремя аргументами.
// plusair.cpp
// использование алгоритма accumulate() и функционального объекта plus()
#include <iostream>
#include <list>
#include <numeric> //для accumulate()
using namespace std;
class airtime
{
	private:
	int hours; //от 0 до 23
	int minutes; //от 0 до 59
	public:
	airtime():hours(0),minutes(0){}
	airtime(int h,int m):hours(h),minutes(m){}
	void display() const{cout<<hours<<':'<<minutes;}
	void get()
	{
		char dummy;
		cout<<"\nTime (format 12:59): ";
		cin>>hours>>dummy>>minutes;
	}
	airtime operator+(const airtime right) const
	{
		int temph=hours+right.hours;//добавить компоненты
		int tempm=minutes+right.minutes;
		if(tempm>=60) //проверка наличия переноса
		{
			temph++;
			tempm-=60;
		}
		return airtime(temph,tempm); //возврат суммы
	}
	bool operator==(const airtime& at2) const
	{
		return (hours==at2.hours) && (minutes==at2.minutes);
	}
	bool operator<(const airtime& at2) const
	{
		return (hours<at2.hours) || (hours==at2.hours && minutes<at2.minutes);
	}
	bool operator!=(const airtime& at2) const
	{
		return !(*this==at2);
	}
	bool operator>(const airtime& at2) const
	{
		return !(*this<at2) && !(*this==at2);
	}
};
int main()
{
	char answer;
	airtime temp,sum;
	list<airtime> airlist; //список типа airtime
	do
	{
		temp.get(); //получить значения от пользователя
		airlist.push_back(temp);
		cout<<"Continue (y/n)? ";
		cin>>answer;
	}while(answer!='n');
	sum=accumulate(airlist.begin(),airlist.end(),airtime(0,0));
	cout<<"\nSum: ";
	sum.display(); //вывод суммы на экран
	cout<<endl;
	return 0;
}
