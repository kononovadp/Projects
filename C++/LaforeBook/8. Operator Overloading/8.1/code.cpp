/**1. Добавьте в класс Distance из программы ENGLPLUS этой главы перегруженную операцию -, которая вычисляет разность двух интервалов. Она должна позволять выполнение выражений типа dist3 = dist1-dist2;. Предполагаем, что эта операция никогда не будет использоваться для вычитания большего интервала из меньшего (так как отрицательного интервала быть не может)*/
// englplus.cpp
// перегрузка операции + для сложения переменных типа Distances
#include <iostream>
using namespace std;
class Distance	// класс английских мер длины
{
	int feet;
	float inches;
	public:
	Distance():feet(0),inches(0.0){}
	Distance(int ft, float in):feet(ft),inches(in){}
	void getdist()
	{
		cout<<"footes: ";cin>>feet;
		cout<<"inches: ";cin>>inches;
	}
	void showdist(){cout<<feet<<"\'-"<<inches<< '\"';}
	Distance operator+(Distance) const;
	Distance operator-(Distance) const;
};
Distance Distance::operator+(Distance d2) const //сложение двух длин
{
	int f=feet+d2.feet; //складываем футы
	float i=inches+d2.inches; //складываем дюймы
	if(i>=12.0) //если дюймов стало больше 12
	{
		i-=12.0; //то уменьшаем дюймы на 12
		f++; //и увеличиваем футы на 1
	}
	return Distance(f, i); //создаем и возвращаем временную переменную
}
Distance Distance::operator-(Distance d2) const //сложение двух длин
{
	int f=feet-d2.feet; //отнимаем футы
	float i=inches-d2.inches; //отнимаем дюймы
	if(i<=12.0) //если дюймов стало меньше 12
	{
		i+=12.0; //то уменьшаем дюймы на 12
		f--; //и увеличиваем футы на 1
	}
	return Distance(f,i); //создаем и возвращаем временную переменную
}
int main()
{
	Distance dist1, dist3, dist4; //определяем переменные
	dist1.getdist(); //получаем информацию
	Distance dist2(11, 6.25); //определяем переменную с конкретным значением
	dist3=dist1-dist2; //складываем две переменные
	dist4=dist1-dist2-dist3; //складываем несколько переменных
	cout<<"dist1 = ";dist1.showdist();cout<<endl;
	cout<<"dist2 = ";dist2.showdist();cout<<endl;
	cout<<"dist3 = ";dist3.showdist();cout<<endl;
	cout<<"dist4 = ";dist4.showdist();cout<<endl;
	return 0;
}
