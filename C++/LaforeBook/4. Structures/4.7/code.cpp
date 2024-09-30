/*7. Добавьте  поля  типа enum  etype(см.  упражнение  6) и struct  date (см.  упражнение  5) в  структуру employee из  упражнения  4.  Организуйте  программу таким  образом,  чтобы  пользователь  вводил  4  пункта  данных  о  каждом  из трех сотрудников:  его  номер,  величину  зарплаты,  его  должность  и  дату принятия  на  работу.  Программа  должна  хранить  введенные  значения в  трех переменных типа employee и выводить их содержимое на экран.*/
#include <iostream>
#include <conio.h>
struct date
{
	int day;
	int month;
	int year;
};
enum etype {laborer,secretary,manager,accountant,executive,researcher};
struct employee
{
	int number;
	float allowance;
	struct date d;
	etype post;
};
using namespace std;
int main(void)
{
	char i,ch;
	struct employee *e=(struct employee*)calloc(sizeof(struct employee),3);
	for(i=0; i<3; i++)
	{
		cout<<"ID of employee "<<i+1<<": ";
		cin>>e[i].number;
		cout<<"Allowance: ";
		cin>>e[i].allowance;
		cout<<"Enter a date in format dd/mm/yyyy: ";
		scanf("%d/%d/%d",&e[i].d.day,&e[i].d.month,&e[i].d.year);
		cout<<"First letter of a position (laborer, secretary, manager, accountant, executive, researcher): ";
		ch=getche();
		switch(ch)
		{
			case 'l': e[i].post=laborer; break;
			case 's': e[i].post=secretary; break;
			case 'm': e[i].post=manager; break;
			case 'a': e[i].post=accountant; break;
			case 'e': e[i].post=executive; break;
			case 'r': e[i].post=researcher; break;
		}
		cout<<endl;
	}
	cout<<"============================================================";
	for(i=0; i<3; i++)
	{
		cout<<endl<<"ID of employee "<<i+1<<": "<<e[i].number<<"; allowance: "<<e[i].allowance;
		cout<<';'<<endl<<"date: "<<e[i].d.day<<'/'<<e[i].d.month<<'/'<<e[i].d.year;
		cout<<';'<<endl<<"post: ";
		switch(e[i].post)
		{
			case laborer: cout<<"laborer"; break;
			case secretary: cout<<"secretary"; break;
			case manager: cout<<"manager"; break;
			case accountant: cout<<"accountant"; break;
			case executive: cout<<"executive"; break;
			case researcher: cout<<"researcher"; break;
			default: cout<<"incorrect letter"; break;
		}
		cout<<';'<<endl<<"------------------------------------------------------------";
	}
	free(e);
	return 0;
}
