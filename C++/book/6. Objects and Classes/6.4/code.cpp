/*4. Создайте класс employee, используя упражнение 4 главы 4. Класс должен включать поле типа int для хранения номера сотрудника и поле типа float для хранения величины его оклада. Методы класса должны позволять пользователю вводить и отображать данные класса. Напишите функцию main(), которая запросит пользователя ввести данные для трех сотрудников и выведет полученную информацию на экран.*/
#include <iostream>
using namespace std;
class employee
{
	int number;
	float allowance;
	public:
	void SetData(int n,float a)
	{
		number=n;
		allowance=a;
	}
	void display()
	{
		cout<<"number = "<<number<<"; allowance = "<<allowance<<endl;
	}
};
int main(void)
{
	employee e1,e2,e3;
	int n;
	double a;
	cout<<"Number of the employee 1: ";
	cin>>n;
	cout<<"salary of the employee 1: ";
	cin>>a;
	e1.SetData(n,a);
	cout<<"Number of the employee 2: ";
	cin>>n;
	cout<<"salary of the employee 2: ";
	cin>>a;
	e2.SetData(n,a);
	cout<<"Number of the employee 3: ";
	cin>>n;
	cout<<"salary of the employee 3: ";
	cin>>a;
	e3.SetData(n,a);
	cout<<"Employee 1: ";
	e1.display();
	cout<<"Employee 2: ";
	e2.display();
	cout<<"Employee 3: ";
	e3.display();
	return 0;
}
