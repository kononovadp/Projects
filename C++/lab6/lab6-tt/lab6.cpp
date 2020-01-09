#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <list>
using namespace std;

class Person{
public:
	Person(){};
	Person(string _f_name, string _l_name, int _age) : age(_age),
           f_name(_f_name), l_name(_l_name){	}
	virtual void Display(){cout<<f_name<<"  "<<l_name<<endl;};
	virtual string GetDepartment(){return " ";};
	virtual int GetId(){return 0;};
protected:
	string f_name;//first name
	string l_name;//last name
	int age;

};

class Employee : public Person{
	public:
	Employee(){};
	Employee(string _f_name, string _l_name, int _age, int _id) :
     Person(_f_name, _l_name, _age), id(_id){};
	
	 Employee(const Employee &e)
	{
	  *this=e;
	};
	
	Employee& operator=(const Employee &e)
	{ f_name=e.f_name;
	  l_name=e.l_name;
	  age=e.age;
	  department=e.department;
	  salary=e.salary;
	  id=e.id+1;
	};
	void SetSalary(int s){salary=s;}
	void SetDepartment(string dept){department=dept;}
	void SetId(int n){id=n;}
	int GetId(){return id;};
	string GetDepartment(){return department;};
	void Display(){
		cout<<"ID: "<<id<<" "<<department<<" - Employee "<<endl;
		cout<<"  First name: "<<f_name<<endl;
		cout<<"  Last name: "<<l_name<<endl;
		cout<<"  Age: "<<age<<"    Salary: "<<salary<<endl;
        cout<<"---------------------------------------------------------"<<endl;
	};
	void Display(int n){
		cout<<"                    ID: "<<id<<"  "<<f_name<<"   "<<l_name<<endl;
	
	};
//Add here whatever you need

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
		
	Manager(const Manager &m) 
	{   *this=m;
	};
	
	Manager& operator=(const Manager &m)
   {	f_name=m.f_name;
	  l_name=m.l_name;
	  age=m.age;
	  department=m.department;
	  salary=m.salary;
	  id=m.id+1;
		subordinates=m.subordinates;
	};
	
	void Display()
	{cout<<"ID: "<<id<<"  "<< department<<"  - Manager"<<endl;
		cout<<"  First name: "<<f_name<<"    Last name: "<<l_name<<endl;
		cout<<"  Age: "<<age<<endl;
		DisplaySubordinates();
	    cout<<"------------------------------------------------------------"<<endl;
	};
	
	//add an employee to the subordinates list
	Person* AddSubordinate(Person *p)
	{ list <Person *>::iterator it=subordinates.begin(); 
	int i=0;
		while (it!= subordinates.end())
		{if (dynamic_cast<Employee*>(*it)==p) i++;
		 ++it; 
		}
		
	 if (i==0) {subordinates.push_back(p);
	             return *subordinates.end();}
		else return NULL;
	}
	
	int DelSubordinate(int _id)
	{ list <Person *>::iterator it=subordinates.begin(); 
	int i=0;
		while (it!= subordinates.end())
		{if (dynamic_cast<Employee*>(*it)->GetId() ==_id)
		  {//cout<<"del "<<dynamic_cast<Employee*>(*it)->GetId()<<endl;
			it=subordinates.erase(it); i++;
			//cout<<"del OK - "<<i<<endl;
		  }
		  		else  ++it; 
		}
		
	return i;
	
	}
	
	
	void DisplaySubordinates()
	{cout<<"Subordinates:"<<endl;
		if (subordinates.empty())cout<<"                      none"<<endl;
		else
		 { list <Person *>::iterator it=subordinates.begin(); 
		    while (it!= subordinates.end()){
	            dynamic_cast<Employee*>(*it)->Display(10);
				 ++it; }
		 }
	};

private:
	list <Person *> subordinates;

};


class Database{
public:
	Database(){};
	~Database(){};//no need in destructor
	//creates "flat" database
bool LoadFromFile(const char *file)
	//arranges "flat" database after loading from the file
{
	ifstream in;
	in.open(file,ios::in);
	string s;
	while (!in.eof())
	{
		in>>s;
		
	    	int _id=0,ag=0,sal=0;
			int i=2,j=0;
			while(s[i]!=';') {_id=_id*10+s[i]-48; i++;}
			
			i++;j=i;
			while(s[i]!=';') {i++;}
			string f(s,j,i-j);
			
			i++;j=i;
			while(s[i]!=';') { i++;}
			string l(s,j,i-j);
			
			i++;
			while(s[i]!=';') {ag=ag*10+s[i]-48; i++;}
			
			i++;j=i;
			while(s[i]!=';') {i++;}
			string dep(s,j,i-j);
			
			i++;
			while(i<s.length()){sal=sal*10+s[i]-48; i++;}
			
			
	if (s[0]=='0')
		{
	    	Employee *p;
		   p=new Employee(f,l,ag,_id);
		   p->SetSalary(sal); p->SetDepartment(dep);
		   employees.push_back(p);
		  };
	if (s[0]=='1')
		{
		  Manager *p;
	       p=new Manager(f,l,ag,_id);
		   p->SetSalary(sal); p->SetDepartment(dep);
		   employees.push_back(p);
		};
         //  cout<<s<<endl;
		 //  p->Display(); 
	}
	in.close();
	return true;
}
	void ArrangeSubordinates()
	{ vector<Person*>::iterator it= employees.begin();
	 int i =0;
	 //*it=employees[0];
     while (it != employees.end())	 
	  { 
	    if (typeid(**it) == typeid(Manager))
		 { 	string dept = dynamic_cast<Manager*>(*it)->GetDepartment();
		    cout<<dynamic_cast<Manager*>(*it)->GetId()<<" manager "<<endl;
	    	
			vector<Person*>::iterator em = employees.begin();
			while (em != employees.end())
			 { 
		          if (typeid(**em) == typeid(Employee))
					 { if(dept == dynamic_cast<Employee*>(*em)->GetDepartment())
		                {  dynamic_cast<Manager*>(*it)->AddSubordinate(*em);
				            cout<<"   "<<dynamic_cast<Employee*>(*em)->GetId()<<" Yes "<<endl;
						}
				      else cout<<"   "<<dynamic_cast<Employee*>(*em)->GetId()<<"  Not dep"<<endl;
					 }
					 else cout<<"   "<<dynamic_cast<Manager*>(*em)->GetId()<<"   Not emp"<<endl;
				  *em++;
					 if( *em==*it) *em++;
			  }
			 
		 }
		 else cout<<dynamic_cast<Employee*>(*it)->GetId()<<" not manager "<<endl;
			
		*it++;
	   }	
	  
	};
	
//hire a new employee
	Person* HireEmployee(Person *p)
	{
    	employees.push_back(p); 
			return *employees.end();
	}
	
	void DisplayDepartmentEmployees(string _department)
	{ cout<<" Employees Department "<<_department<<":"<<endl;
	int j=0;
	for( int i=0; i<employees.size(); i++)
	    {if (employees[i]->GetDepartment()== _department)	
		     { employees[i]->Display(); j++;}
		}
		if (j==0)cout<<"Empty"<<endl;
	};
	
	//fire the employee
    bool FireEmployee(int id)
   {vector<Person*>::iterator em = employees.begin();
			while (em != employees.end())
			 { 
		       if(id == dynamic_cast<Employee*>(*em)->GetId())
		          {	employees.erase(em);}
			 else  { 
				     if (typeid(**em) == typeid(Manager)) dynamic_cast<Manager*>(*em)->DelSubordinate(id);
				     *em++;
			        }
			  }
			return 1;
	}

	void DisplayAll()
	{
	for( int i=0; i<employees.size(); i++)
		employees[i]->Display();
	};
//Add here whatever you need

private:
	vector <Person*> employees;
	
};



int main(){
	Database db;
	db.LoadFromFile("1.txt");
	db.DisplayAll();cin.get();
	
Employee *p=new Employee("New","Chel",33,5);p->SetSalary(2000);p->SetDepartment("Finans");
	db.HireEmployee(p);
	db.DisplayAll();cin.get();
	//db.ArrangeSubordinates();cin.get();
	
	
	Manager *m=new Manager("Manager","Serg",44,6);m->SetDepartment("Finans");
	//m->AddSubordinate(p);
	db.HireEmployee(m);
	
	Manager *M=new Manager("BIG Manager","Max",28,7);M->SetDepartment("Finans");
	//M->AddSubordinate(m);M->AddSubordinate(p);
	//M->Display();
	//M->DelSubordinate(7);
	db.HireEmployee(M);
	
	db.DisplayAll();cin.get();
	cout<<"* *********************************************** *"<<endl;
	
	db.ArrangeSubordinates();cin.get();
	cout<<"* *********************************************** *"<<endl;
	db.DisplayAll();cin.get();
	
	db.FireEmployee(6);db.DisplayAll();cin.get();
	db.DisplayDepartmentEmployees("Fin");
	
	
	//Manager m("Manager","Serg",44,6);m.SetDepartment("Finans"); m.Display();
//	Manager q;   q=m;    cout<<"* ***** *"<<endl;   q.Display();
//	Employee q(*p);	cout<<"* ***** *"<<endl; q.Display();
//	Manager f(m);    cout<<"* ***** *"<<endl;f.Display();
	
/*	cout<<"* *********************************************** *"<<endl;
	
*/
	cin.get();
}
