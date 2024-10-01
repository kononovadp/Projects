#include "Employee.h"
	Employee& Employee::operator=(const Employee &e)
	{
		SetSalary(e.salary);
		SetDepartment(e.department);
		SetId(e.id);
		f_name=e.f_name;
		l_name=e.l_name;
		age=e.age;
		return *this;
		
	}
	void Employee::SetSalary(int s)
	{
		salary=s;
	}
	void Employee::SetDepartment(string dept)
	{
		department=dept;
	}
	void Employee::SetId(int n)
	{
		id=n;
	}
	int Employee::GetId()
	{
		return id;
	}
	string Employee::GetDepartment()
	{
		return department;
	}
	void Employee::Display(bool b)
	{
		string space="";
		if (b==true)//if (displayfull==false)
			space="        ";
		cout<<space<<"Employee  "<<f_name<<" "<<l_name<<", age: "<<age<<endl
		<<space<<"Id: "<<id<<" Department: "<<department<<" Salary: "<<salary<<endl;
	}