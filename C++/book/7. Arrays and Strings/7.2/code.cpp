/* *2. Создайте класс employee, который содержит имя (объект класса string) и номер (типа long) служащего. Включите в него метод getdata(), предназначенный для получения данных от пользователя и помещения их в объект, и метод putdata(), для вывода данных. Предполагаем, что имя не может иметь внутренних пробелов. Напишите функцию main(), использующую этот класс. Вам нужно будет создать массив типа employee, а затем предложить пользователю ввести данные до 100 служащих. Наконец, вам нужно будет вывести данные всех служащих.*/
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;
class employee
{
	string name;
	long id;
	public:
	void getdata(string s, long n)
	{
		name=s;
		id=n;
	}
	void putdata()
	{
		cout<<"Name: "<<name<<"; ID: "<<id;
	}
};	
int main(void)
{
	char ch=0,i=0,j,lim=100;
	long id;
	employee e[100];
	string s;	
	do
	{
		cout<<"Name of an employee: ";
		cin>>s;
		cout<<"ID: ";
		cin>>id;
		e[i].getdata(s,id);
		i++;
		if(i==lim)
			continue;
		cout<<"press 1 to continue or 0 to stop: ";
		ch=getch();
		while(ch!='1' && ch!='0')
		{
			cout<<endl<<"press 1 or 0: ";
			ch=getch();
		}
		cout<<endl;
	}while(i<lim && ch!='0');
	if(i==lim)
		cout<<"You can't add more than "<<+lim<<" employes"<<endl;
	cout<<"All employes: "<<endl;
	for(j=0; j<i; j++)
	{
		e[j].putdata();
		cout<<endl;
	}
	return 0;
}
