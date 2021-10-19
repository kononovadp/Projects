/* *4. Напишите функцию, принимающую в качестве аргументов два значения типа Distance и возвращающую значение наибольшего из аргументов (необходимую информацию можно найти в примере RETSTRC).*/
#include <iostream>
using namespace std;
struct Distance // длина в английской системе
{
	int feet;
	float inches;
};
struct Distance GetMaxDistance(Distance d1,Distance d2)
{
	if(d1.feet>d2.feet)
		return d1;
	else
		return d2;
}
int main(void)
{
	struct Distance d1,d2,m;
	d1.feet=5;
	d1.inches=d1.feet*12;
	d2.feet=7;
	d2.inches=d2.feet*12;
	m=GetMaxDistance(d1,d2);
	cout<<"Max feet = "<<m.feet<<"; Max inches = "<<m.inches;
	return 0;
}
