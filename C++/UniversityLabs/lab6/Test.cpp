#include "Database.h"
int main()
{	
	cout<<"====================LoadFromFile===================="<<endl;
	Database db;
	db.LoadFromFile("1.txt");
	db.DisplayAll();
	cout<<"====================ArrangeSubordinates===================="<<endl;
	db.ArrangeSubordinates();
	db.DisplayAll();
	srand(time(NULL));
	int n=rand()%7;
	cout<<"====================FireEmployee("<<n<<")===================="<<endl;
	db.FireEmployee(n);
	db.DisplayAll();
	cout<<"====================DisplayDepartmentEmployees('IT')===================="<<endl;
	db.DisplayDepartmentEmployees("IT");
	cin.get();
}