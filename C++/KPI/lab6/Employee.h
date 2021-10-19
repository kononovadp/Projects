#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
class Person
{
public:
	Person(){};
	Person(string _f_name, string _l_name, int _age) : 
	age(_age), f_name(_f_name), l_name(_l_name){}
	virtual void Display(bool)
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
	Employee& operator=(const Employee &e);
	void SetSalary(int s);
	void SetDepartment(string dept);
	void SetId(int n);
	int GetId();
	string GetDepartment();
	virtual void Display(bool b);
protected:
	string department;
	int salary;
	int id;
};