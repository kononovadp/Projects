/**1. Считая,что кубический фут равен 7,481 галлона, написать программу, запрашивающую у пользователя число галлонов и выводящую на экран эквивалентный объем в кубических футах*/
#include<iostream>
using namespace std;
int main(void)
{
	float gallon;
	cout<<"gallons count: ";
	cin>>gallon;
	cout<<endl<<"foots count: "<<gallon/7.481;
	return 0;
}
