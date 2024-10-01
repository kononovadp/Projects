/*5. Взяв в качестве основы структуру из упражнения 5 главы 4, создайте класс date. Его данные должны размещаться в трех полях типа int: month, day и year. Метод класса getdate() должен принимать значение для объекта в формате 12/31/02, а метод showdate() — выводить данные на экран.*/
#include <iostream>
using namespace std;
class date
{	
	int day;
	int month;
	int year;
	public:
	void getdate(int d,int m,int y)
	{
		day=d;
		month=m;
		year=y;
	}
	void showdate()
	{
		cout<<day<<"/"<<month<<"/"<<year;
	}
};
int main(void)
{
	date data;
	int d,m,y;
	cout<<"day: ";
	cin>>d;
	cout<<"month: ";
	cin>>m;
	cout<<"year: ";
	cin>>y;
	data.getdate(d,m,y);
	data.showdate();
	return 0;
}
