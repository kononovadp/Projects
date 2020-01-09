#pragma once
#include "Manager.h"
#include <vector>
#include <fstream>
#include <sstream>
class Database
{
public:
	Database(){}; //creates “flat” database
	~Database(){};//no need in destructor
	bool LoadFromFile(const char *file); //arranges "flat" database after loading from the file
	void ArrangeSubordinates();
	Person* HireEmployee(Person *p); //hire a new employee
	void DisplayDepartmentEmployees(string _department);
	bool FireEmployee(int id); //fire the employee
	void DisplayAll();
private:
	vector<Person*> employees;
};