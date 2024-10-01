#pragma once
#include "Manager.h"
#include <list>
	void Manager::Display(bool)
	{
		cout<<"Manager  "<<f_name<<" "<<l_name<<", age: "<<age<<endl
		<<"Id: "<<id<<" Department: "<<department<<" Salary: "<<salary<<endl;
		if (subordinates.size()>0)
		{
			cout<<"Subordinates: "<<endl;
			DisplaySubordinates();
		}
	}

	void Manager::AddSubordinate(Person *p) //() //add an employee to the subordinates list
	{
		subordinates.push_back(p);
	}
	void Manager::DisplaySubordinates()
	{
		list<Person*>::iterator it = subordinates.begin();
		while (it != subordinates.end())
		{
			dynamic_cast<Person*>(*it)->Display(true);
			it++;
		}
	}
	//Add here whatever you need
	bool Manager::DeleteEmployeeFromList(int id)
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
	int Manager::GetListSize()
	{
		return subordinates.size();
	}