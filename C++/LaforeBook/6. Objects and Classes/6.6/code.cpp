/*6. Расширьте содержание класса employee из упражнения 4, включив в него класс date и перечисление etype (см. упражнение 6 главы 4). Объект класса date будет использоваться для хранения даты приема сотрудника на работу. Перечисление будет использовано для хранения статуса сотрудника: лаборант, секретарь, менеджер и т. д. Последние два поля данных должны быть закрытыми в определении класса employee, как и номер и оклад сотрудника. Вам будет необходимо разработать методы getemploy() и putemploy(), предназначенные соответственно для ввода и отображения информации о сотруднике. Возможно, при создании методов вам понадобится ветвление switch для работы с перечисляемым типом etype. Напишите функцию main(), которая попросит пользователя ввести данные о трех сотрудниках, а затем выведет эти данные на экран.*/
#include <iostream>
#include <conio.h>
using namespace std;
class employee
{
	int number;
	float allowance;
	enum etype {laborer,secretary,manager,accountant,executive,researcher};
	etype post;
	class date
	{
		int day;
		int month;
		int year;
		public:
		void getdate(int d,int m,int y)
		{
			day=d;
			month=m;
			year=y;
		}
		void showdate()
		{
			cout<<day<<"/"<<month<<"/"<<year;
		}
	};
	date DateOfHire;
	public:
	void getemploy(int n,float a,char p,int d,int m,int y)
	{
		number=n;
		allowance=a;
		switch(p)
		{
			case 'l': post=laborer; break;
			case 's': post=secretary; break;
			case 'm': post=manager; break;
			case 'a': post=accountant; break;
			case 'e': post=executive; break;
			case 'r': post=researcher; break;
		}
		DateOfHire.getdate(d,m,y);
	}
	void putemploy()
	{
		cout<<"Employee "<<number<<"; post: ";
		switch(post)
		{
			case laborer: cout<<"laborer"; break;
			case secretary: cout<<"secretary"; break;
			case manager: cout<<"manager"; break;
			case accountant: cout<<"accountant"; break;
			case executive: cout<<"executive"; break;
			case researcher: cout<<"researcher"; break;
		}
		cout<<"; date of hire: ";
		DateOfHire.showdate();
	}
};
int main(void)
{
	int i,number,day,month,year;
	float allowance;
	char post;
	employee** e=(employee**)::operator new(3*sizeof(employee*));
	for(i=0; i<3; i++)
	{
		cout<<"Employee "<<i+1<<": "<<endl<<"ID: ";
		cin>>number;
		cout<<"Allowance: ";
		cin>>allowance;
		cout<<"First letter of a position (laborer, secretary, manager, accountant, executive, researcher): ";
		post=getche();
		while(post!='l' && post!='s' && post!='m' && post!='a' && post!='e' && post!='r')
		{
			cout<<endl<<"press correct letter: ";
			post=getche();
		}
		cout<<endl<<"Enter a date in format dd/mm/yyyy: ";
		scanf("%d/%d/%d",&day,&month,&year);
		e[i]=new employee;
		e[i]->getemploy(number,allowance,post,day,month,year);
	}
	cout<<"All employers:"<<endl;
	for(i=0; i<3; i++)
	{
		e[i]->putemploy();
		delete e[i];
		cout<<endl;
	}
	delete e;
	return 0;
}
