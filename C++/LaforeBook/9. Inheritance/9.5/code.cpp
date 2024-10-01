/*5. Создайте производный класс employee2 от базового класса employee из программы EMPLOY этой главы. Добавьте в новый класс поле compensation типа double  и поле period типа enum для обозначения периода оплаты работы служащего: почасовая, понедельная или помесячная. Для простоты вы можете изменить классы laborer, manager и scientist так, чтобы они стали производными нового класса employee2. Однако заметим, что во многих случаях создание отдельного класса compensation и трех его производных классов manager2, scientist2 и laborer2 более соответствовало бы духу ООП. Затем можно применить множественное наследование и сделать так, чтобы эти три новых класса стали производными класса compensation и первоначальных классов manager, scientist и laborer. Таким путем можно избежать модификации исходных классов*/
#include "../../../../accessories.h"
const int LEN=80; //максимальная длина имени
class employee //некий сотрудник
{
	private:
	char name[LEN]; //имя сотрудника
	unsigned long number; //номер сотрудника
	public:
	void GetData()
	{
		cout<<"\nSurname: ";cin>>name;
		while(getchar()==13)
			continue;
		cout << "Number: ";cin>>number;
	}
	void PutData() const
	{
		cout<<"\nSurname: "<<name;
		cout<<"\nNumber: "<<number;
	}
};
class compensation
{
	double salary;
	enum period{hourly='h',weekly='w',monthly='m'};
	period CurrentPeriod;
	public:
	void GetData()
	{
		cout<<"Compensation: ";
		salary=GetFloatFromKeyboard();
		cout<<"\nPeriod (\"h\": hourly; \"w\": weekly; \"m\": monthly; ESC: exit): ";
		char ch=getch();
		while(ch!=27 && ch!=hourly && ch!=weekly && ch!=monthly)
			ch=getch();
		if(ch==27)
			exit(0);		
		switch(ch)
		{
			case hourly: cout<<"hourly"; CurrentPeriod=hourly; break;
			case weekly: cout<<"weekly"; CurrentPeriod=weekly; break;
			case monthly: cout<<"monthly"; CurrentPeriod=monthly; break;
		};
	}
	void PutData()
	{
		cout<<"\nCompensation: "<<salary<<endl;
		cout<<"Period: ";
		switch(CurrentPeriod)
		{
			case hourly: cout<<"hourly"; break;
			case weekly: cout<<"weekly"; break;
			case monthly: cout<<"monthly"; break;
		};			
	}
};
class manager:public employee //менеджер
{
	private:
	char title[LEN]; //должность, например вице-президент
	double dues; //сумма взносов в гольф-клуб
	public:
	void GetData()
	{
		employee::GetData();
		cout<< "Position: ";cin>>title;
		cout<< "Dues in golf club: ";cin>>dues;
	}
	void PutData() const
	{
		employee::PutData();
		cout<<"\nPosition: "<<title;
		cout<<"\nDues in golf club: "<<dues;
	}
};
class scientist:public employee //ученый
{
	private:
	int pubs; //количество публикаций
	public:
	void GetData()
	{
		employee::GetData();
		cout<<"Count of publications: ";cin>>pubs;
	}
	void PutData() const
	{
		employee::PutData();
		cout << "\nCount of publications: "<<pubs;
	}
};
class laborer:public employee{public: void GetData(){} void PutData(){}};
class manager2: private manager,private compensation
{
	public:
	void GetData()
	{
		manager::GetData();
		compensation::GetData();
	}
	void PutData()
	{
		manager::PutData();
		compensation::PutData();
	}
};
class scientist2: private scientist,private compensation
{
	public:
	void GetData()
	{
		scientist::GetData();
		compensation::GetData();
	}
	void PutData()
	{
		scientist::PutData();
		compensation::PutData();
	}
};
class laborer2: public laborer,private compensation
{
	public:
	void GetData(){}
	void PutData(){}
};
int main()
{
	manager2 m1,m2;	
	scientist2 s1;
	laborer2 l1;
	cout<<"The first manager";
	m1.GetData();
	cout<<"\nThe second manager";
	m2.GetData();
	cout<<"\nThe first scientist";
	s1.GetData();
	cout<<"\nThe first laborer";
	l1.GetData();
	cout<<"\nInformation about the first manager";
	m1.PutData();
	cout<<"\nInformation about the second manager";
	m2.PutData();
	cout<<"\nInformation about the first scientist";
	s1.PutData();
	cout<<"\nInformation about the first laborer";
	l1.PutData();
	cout<<endl;	
	return 0;
}
