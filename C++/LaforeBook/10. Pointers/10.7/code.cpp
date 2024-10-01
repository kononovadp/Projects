//7. Модифицируйте класс person из программы PERSORT этой главы так, чтобы он включал в себя не только имя человека, но и сведения о его зарплате в виде поля salary типа float. Вам будет необходимо изменить методы setName() и printName() на setData() и printData(), включив в них возможность ввода и вывода значения salary, как это можно сделать с именем. Вам также понадобится метод getSalary(). Используя указатели, напишите функцию salsort(), которая сортирует указатели массива persPtr по значениям зарплаты. Попробуйте вместить всю сортировку в функцию salsort(), не вызывая других функций, как это сделано в программе PERSORT. При этом не забывайте, что операция -> имеет больший приоритет, чем операция *, и вам нужно будет написать if((*(pp+j))->getSalary()>(*(pp+k))->getSalary()){/*меняем указатели местами*/}
#include "../../accessories.h"
class person
{
	protected:
	string name;
	float salary;
	public:
	string GetName(){return name;}
	float GetSalary(){return salary;}
	void SetData()
	{
		cout<<"Name: ";		
		cin>>name;
		cout<<"salary: ";
		salary=GetFloatFromKeyboard();
	}
	void SetRandomData()
	{
		int RandomLength=GetRandomInt(1,10);
		for(int i=0; i<RandomLength; i++)
			name+=GetRandomInt('a','z');
		salary=GetRandomFloat(1000,100000);
	}
	void PrintData(){cout<<setw(10)<<name<<"; salary: "<<setw(10)<<salary<<endl;}    
};
void bsort(person** pp,int n)
{
	int j,k;
	for(j=0; j<n-1; j++)
		for(k=j+1; k<n; k++)
			if((*(pp+j))->GetSalary()>(*(pp+k))->GetSalary())
			{
				person* tempptr=*(pp+j);
				*(pp+j)=*(pp+k);
				*(pp+k)=tempptr;
			}
}
int main()
{	
	int i,n=0;
	char ch=0;
	person* persPtr[100];
	InitFloatingPointAndRandomNumbers();
	for(i=0; i<5 && ch!='0'; i++,n++)
	{
		persPtr[i]=new person;		
		persPtr[i]->SetData();
		if(i<4)
		{
			cout<<"\nPress 1 to continue input or 0 to stop it: ";		
			while((ch=getch())!='0' && ch!='1');
		}
		cout<<endl;
	}
	cout<<"UNSORTED LIST:\n";
	for(i=0; i<n; i++)
		persPtr[i]->PrintData();
	bsort(persPtr,i);
	cout<<"SORTED LIST:\n";
	for(i=0; i<n; i++)
		persPtr[i]->PrintData();
	return 0;
}
