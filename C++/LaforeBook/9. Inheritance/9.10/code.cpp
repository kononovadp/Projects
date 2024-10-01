/*10. В программе EMPMULT этой главы существует только один тип должности менеджера. В любой серьезной компании кроме менеджеров существуют еще и управляющие. Создадим производный от класса manager класс executive. (Мы предполагаем, что управляющий — это главный менеджер). Добавочными данными этого класса будут размер годовой премии и количество его акций в компании. Добавьте подходящие методы для этих данных, позволяющие их вводить и выводить*/
#include "../../../../accessories.h"
const int LEN=80;
class student
{
	char school[LEN];
	char degree[LEN];
	public:
	void getedu()
	{
		cout<<"\nName of an educational institution: ";
		cin>>school;
		char ch=0;
		cout<<"Degree:\n1. incomplete higher education;\n2. bachelor;\n3. master;\n4. candidate of science.\nYour choice: ";
		while(ch<'1' || ch>'4')
			ch=getch();
		switch(ch)
		{
			case '1':strcpy(degree,"incomplete higher education"); break;
			case '2':strcpy(degree,"bachelor"); break;
			case '3':strcpy(degree,"master"); break;
			case '4':strcpy(degree,"candidate of science"); break;
		}
		cout<<degree;
	}
	void putedu() const
	{
		cout<<"\nEducational institution: "<<school;
		cout<<"\nDegree: "<<degree;
	}
};
class employee
{
	private:
	char name[LEN];
	unsigned long number;
	public:
    void getdata()
	{
        cout<<"\nSurname: ";
		cin>>name;
        cout<<"Number: ";
		number=GetIntFromKeyboard();
	}
    void putdata() const
	{
        cout<<"\nSurname: "<<name;
        cout<<"\nNumber: "<<number;
	}
};
class manager:public employee,public student
{
	private:
    char title[LEN];
    double dues;
	public:
    void getdata()
	{
		employee::getdata();
		cout<<"\nPosition: ";
		cin>>title;
		cout<<"Dues in a golf club: ";
		dues=GetFloatFromKeyboard();
		student::getedu();
	}
	void putdata()const
	{
		employee::putdata();
		cout<<"\nPosition: "<<title;
		cout<<"\nDues in a golf club: "<<dues;
		student::putedu();
	}
};
class executive: private manager
{
	double AnnualBonus;
	int CountOfStocks;
	public:
	void getdata()
	{
		manager::getdata();
		cout<<"\nAnnual bonus: ";
		AnnualBonus=GetFloatFromKeyboard();
		cout<<"\nCount of stocks: ";
		CountOfStocks=GetIntFromKeyboard();
	}
	void putdata()const
	{
		employee::putdata();
		cout<<"\nAnnual bonus: "<<AnnualBonus<<"\nCount of stocks: "<<CountOfStocks;
		student::putedu();
	}
};
class scientist:private employee,private student
{
	private:
	int pubs;
	public:
	void getdata()
	{
		employee::getdata();
		cout<<"\nCount of publications: ";
		pubs=GetIntFromKeyboard();
		student::getedu();
	}
	void putdata() const
	{
		employee::putdata();
		cout<<"\nCount of publications: "<<pubs;
		student::putedu();
	}
};
class laborer:public employee{};
int main()
{
	manager m1;
	scientist s1,s2;
	laborer l1;
	executive executive1;
	cout<<"Manager 1";
	m1.getdata();
	cout<<"\nScientist 1";
	s1.getdata();
	cout<<"\nScientist 2";
	s2.getdata();
	cout<<"\nLaborer 1";
	l1.getdata();
	cout<<"\nExecutive";
	executive1.getdata();
	cout<<"----------------------------------------------------------------------\n";
	cout<<"Information about manager 1";
	m1.putdata();
	cout<<"\n--------------------\nInformation about scientist 1";
	s1.putdata();
	cout<<"\n--------------------\nInformation about scientist 2";
	s2.putdata();
	cout<<"\n--------------------\nInformation about laborer 1";
	l1.putdata();
	cout<<"\n--------------------\nInformation about executive";
	executive1.putdata();
	return 0;
}