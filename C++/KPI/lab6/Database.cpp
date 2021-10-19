#include "Database.h"
	bool Database::LoadFromFile(const char *file) //arranges "flat" database after loading from the file
	{
		ifstream f;
		f.open(file);
		string s;
		int i=0;
		Employee *ee;
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
			int id;
			v1>>id;//idglob;
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
			string dept=s.substr(0,k);
			dept=s.substr(0,k);//deptglob=s.substr(0,k);
			s=s.erase(0,k+1);
			k=s.find_first_of(";");
			temp=s.substr(0,k);
			istringstream v3 (temp, istringstream::in);
			int salary;
			v3>>salary;//salaryglob;
			s=s.erase(0,k+1);
			//cout<<post<<"|"<<id<<"|"<<name<<"|"<<lastname
			//<<"|"<<age<<"|"<<dept<<"|"<<salary<<endl;
			if(post==0)
				ee=new Employee(name,lastname,age,id);
			else
				ee=new Manager(name,lastname,age,id);
			ee->SetSalary(salary);//(salaryglob);
			ee->SetDepartment(dept);//(deptglob);
			ee->SetId(id);//(idglob);
			employees.push_back(ee);
		}
		f.close();
	}
	void Database::ArrangeSubordinates()
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
	Person* Database::HireEmployee(Person *p) //hire a new employee
	{
		employees.push_back(p);
	}
	void Database::DisplayDepartmentEmployees(string _department)
	{
		cout<<"Employees of the department "<<_department<<endl;
		vector<Person*>::iterator it = employees.begin();
		while (it != employees.end())
		{
			if (dynamic_cast<Employee*>(*it)->GetDepartment()==_department)
				dynamic_cast<Employee*>(*it)->Display(false);
			it++;
		}
	}
	bool Database::FireEmployee(int id) //fire the employee
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
	}
	void Database::DisplayAll()
	{
		for (int i=0; i<employees.size(); i++)	
		{			
			employees[i]->Display(false);
			cout<<"------------------------------------------"<<endl;
		}
	}