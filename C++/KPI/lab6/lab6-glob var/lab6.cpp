#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <list>
#include <sstream>
#include <iterator>
#include <ctime>
#include <cstdlib>
using namespace std;
bool displayfull=true;
int idglob,salaryglob;
string deptglob;
//An abstract class
class Person
{
public:
	Person(){};
	Person(string _f_name, string _l_name, int _age) : 
	age(_age), f_name(_f_name), l_name(_l_name){}
	virtual void Display() //bool)
	{
		cout<<"Name: "<<f_name<<" Last name: "<<l_name<<" Age: "<<age<<endl;
	}
protected:
	string f_name;
	string l_name;
	int age;
};

class Employee : public Person
{
public:
	Employee() {}
	Employee(string _f_name, string _l_name, int _age, int _id) :
	Person(_f_name, _l_name, _age), id(_id){};
	Employee (const Employee &e){};
	Employee& operator=(const Employee &e)
	{
		SetSalary(salaryglob);
		SetDepartment(deptglob);
		SetId(idglob);
		f_name=e.f_name;
		l_name=e.l_name;
		age=e.age;
		return *this;
		
	}
	void SetSalary(int s)
	{
		salary=s;
	}
	void SetDepartment(string dept)
	{
		department=dept;
	}
	void SetId(int n)
	{
		id=n;
	}
	int GetId()
	{
		return id;
	}
	string GetDepartment()
	{
		return department;
	}
	virtual void Display()//(bool)
	{
		string space="";
		if (displayfull==false)
			space="        ";
		cout<<space<<"Employee  "<<f_name<<" "<<l_name<<", age: "<<age<<endl
		<<space<<"Id: "<<id<<" Department: "<<department<<" Salary: "<<salary<<endl;
	}
protected:
	string department;
	int salary;
	int id;
};

class Manager : public Employee {
public:
	Manager(){};
	Manager(string _f_name, string _l_name, int _age, int _id) : 
	Employee(_f_name, _l_name, _age, _id){};
	Manager(const Manager &m);
	Manager& operator=(const Manager &m);
	virtual void Display() //(bool)
	{
		cout<<"Manager  "<<f_name<<" "<<l_name<<", age: "<<age<<endl
		<<"Id: "<<id<<" Department: "<<department<<" Salary: "<<salary<<endl;
		if (subordinates.size()>0)
		{
			cout<<"Subordinates: "<<endl;
			DisplaySubordinates();
		}
	}

	void AddSubordinate(Person *p) //() //add an employee to the subordinates list
	{
		subordinates.push_back(p);
	/*	cout<<"New Employee of the manager "<<f_name<<" "<<l_name<<endl;
		string name,lname,dept; 
		int age,id,salary;
		cout<<"Name: ";
		cin>>name;
		cout<<"Last name: ";
		cin>>lname;
		cout<<"Age: ";
		cin>>age;
		cout<<"ID: ";
		cin>>id;
		cout<<"Salary: ";
		cin>>salary;
		dept=GetDepartment();
		Employee *eee=new Employee(name,lname,age,id);
		eee->SetSalary(salary);
		eee->SetDepartment(dept);
		eee->SetId(id);
		subordinates.push_back(eee);	*/		
	}
	void DisplaySubordinates()
	{
		displayfull=false;
		list<Person*>::iterator it = subordinates.begin();
		while (it != subordinates.end())
		{
			dynamic_cast<Person*>(*it)->Display();
			it++;
		}
		displayfull=true;
	}
	//Add here whatever you need
	bool DeleteEmployeeFromList(int id)
	{
		list<Person*>::iterator it = subordinates.begin();
		int i=0; 
		bool b;
		while (it != subordinates.end() 
			&& (subordinates.size()>0))
		{
			if(dynamic_cast<Employee*>(*it)->GetId()==id)
			{
				if(i==subordinates.size()-1)
				{
					subordinates.pop_back();
					return true;
				}
				else
				{					
					it=subordinates.erase(it);
					b=true;
				}				
			}
			else
			{
				it++;
				i++;
			}
		}
		if (b=false)
			return false;
		else
			return true;
	}
	int GetListSize()
	{
		return subordinates.size();
	}
private:
	list<Person *> subordinates;
};

class Database
{
public:
	Database(){}; //creates “flat” database
	~Database(){};//no need in destructor
	bool LoadFromFile(const char *file) //arranges "flat" database after loading from the file
	{
		ifstream f;
		f.open(file);
		string s;
		int i=0;
		while(!f.eof())
		{
			f>>s;
			string temp=s.substr(0,1);
			istringstream v0 (temp, istringstream::in);
			int post;
			v0>>post;
			s=s.erase(0,2);
			int k=s.find_first_of(";");
			temp=s.substr(0,k);
			istringstream v1 (temp, istringstream::in);
			//int id;
			v1>>idglob;
			s=s.erase(0,k+1);
			k=s.find_first_of(";");
			string name=s.substr(0,k);
			s=s.erase(0,k+1);
			k=s.find_first_of(";");
			string lastname=s.substr(0,k);
			s=s.erase(0,k+1);
			k=s.find_first_of(";");
			temp=s.substr(0,k);
			istringstream v2 (temp, istringstream::in);
			int age;
			v2>>age;
			s=s.erase(0,k+1);
			k=s.find_first_of(";");
			//string dept=s.substr(0,k);
			deptglob=s.substr(0,k);
			s=s.erase(0,k+1);
			k=s.find_first_of(";");
			temp=s.substr(0,k);
			istringstream v3 (temp, istringstream::in);
			//int salary;
			v3>>salaryglob;
			s=s.erase(0,k+1);
			//cout<<post<<"|"<<id<<"|"<<name<<"|"<<lastname
			//<<"|"<<age<<"|"<<dept<<"|"<<salary<<endl;
			if (post==0)
			{
				//Employee ee(name,lastname,age,idglob);
				//ee=ee;
				Employee *ee=new Employee(name,lastname,age,idglob);
				/*Employee t=*ee;
				Employee t1=t;
				t=t1;
				Employee *t2=&t;
				employees.push_back(t2);*/
				ee->SetSalary(salaryglob);
				ee->SetDepartment(deptglob);
				ee->SetId(idglob);
				employees.push_back(ee);
			}
			else
			{
				Manager *ee=new Manager(name,lastname,age,idglob);				
				ee->SetSalary(salaryglob);
				ee->SetDepartment(deptglob);
				ee->SetId(idglob);
				employees.push_back(ee);
			}
		}
		f.close();
	}
	void ArrangeSubordinates()
	{
		vector<Person*>::iterator it = employees.begin();
		while (it != employees.end())
		{
			if (typeid(**it) == typeid(Manager))
			{
				string t=dynamic_cast<Manager*>(*it)->GetDepartment();
				vector<Person*>::iterator it2 = employees.begin();
				while (it2 != employees.end())
				{					
					if ((typeid(**it2) == typeid(Employee))
					&&((dynamic_cast<Employee*>(*it2)->GetDepartment()==t)))
						dynamic_cast<Manager*>(*it)->AddSubordinate(*it2);//subordinates.push_back(*it2);
					it2++;
				}				
			}								
			it++;		
		}
	}
	Person* HireEmployee(Person *p) //hire a new employee
	{
		employees.push_back(p);
	}
	void DisplayDepartmentEmployees(string _department)
	{
		cout<<"Employees of the department "<<_department<<endl;
		vector<Person*>::iterator it = employees.begin();
		while (it != employees.end())
		{
			if (dynamic_cast<Employee*>(*it)->GetDepartment()==_department)
				dynamic_cast<Employee*>(*it)->Display();
			it++;
		}
	}
	bool FireEmployee(int id) //fire the employee
	{
		if (employees.size()==0)
			return false;
		vector<Person*>::iterator it = employees.begin();
		int i=0; 
		bool b;
		while (it != employees.end() 
			&& (employees.size()>0))
		{
			if (typeid(**it) == typeid(Manager)
			&& (dynamic_cast<Manager*>(*it)->GetListSize()>0))
				dynamic_cast<Manager*>(*it)->DeleteEmployeeFromList(id);
			if(dynamic_cast<Employee*>(*it)->GetId()==id)
			{
				if(i==employees.size()-1)
				{
					employees.pop_back();
					return true;
				}
				else
				{					
					employees.erase(it);
					b=true;
				}
			}
			else
			{
				it++;
				i++;
			}
		}
		if (b=false)
			return false;
		else
			return true;
		/*vector<Person*>::iterator it = employees.begin();
		for (int i=0; i<employees.size()-1; i++)
		{
			if (typeid(**it) == typeid(Manager))
				dynamic_cast<Manager*>(*it)->DeleteEmployeeFromList(id);
			it++;			
		}
		if (dynamic_cast<Employee*>(*it)->GetId()==id)
		{			
			while(dynamic_cast<Employee*>(*it)->GetId()==id)
			{   
				employees.pop_back();
				it--;				
			}
		}
		else
		{
			vector<Person*>::iterator it = employees.begin();
			while (it != employees.end())
			{			
				if(dynamic_cast<Employee*>(*it)->GetId()==id)
					it=employees.erase(it);					
				it++;			
			}
		}*/
	}
	void DisplayAll()
	{
		for (int i=0; i<employees.size(); i++)	
		{			
			employees[i]->Display();
			cout<<"------------------------------------------"<<endl;
		}
	}
private:
	vector<Person*> employees;
};

int main()
{	
	Database db;
	db.LoadFromFile("1.txt");
	//db.ArrangeSubordinates();
	/*Manager *m=new Manager("Slim","Joe",53,7);
	m->SetSalary(2000);
	m->SetDepartment("Marketing");
	m->SetId(8);
	db.HireEmployee(m);*/
	//m.AddSubordinate();
	db.ArrangeSubordinates();
	db.DisplayAll();	
	cout<<"===================================================="<<endl;
	//db.FireEmployee(4);
	db.FireEmployee(0);
	db.DisplayAll();
	//db.DisplayDepartmentEmployees("PR");
	
	cin.get();
}