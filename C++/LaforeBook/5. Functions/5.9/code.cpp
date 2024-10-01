/*9. Переработайте программу из упражнения 8 так, чтобы функция swap() принимала в качестве аргументов значения типа time (см. упражнение 6).*/
#include <iostream>
using namespace std;
struct time
{
	int hours,minutes,seconds;
};
void swap(struct time* n1,struct time* n2)
{
	struct time* t;
	t=n1;
	n1=n2;
	n2=t;
}
int main(void)
{
	char ch;
	struct time t1,t2;
	cout<<"Time 1 in format hh:mm:ss: ";
	cin>>t1.hours>>ch>>t1.minutes>>ch>>t1.seconds;
	cout<<"Time 2 in format hh:mm:ss: ";
	cin>>t2.hours>>ch>>t2.minutes>>ch>>t2.seconds;
	cout<<"T1: "<<t1.hours<<':'<<t1.minutes<<':'<<t1.seconds;
	cout<<"; T2: "<<t2.hours<<':'<<t2.minutes<<':'<<t2.seconds<<'\n';
	swap(t1,t2);
	cout<<"After swap: "<<"T1: "<<t1.hours<<':'<<t1.minutes<<':'<<t1.seconds;
	cout<<"; T2: "<<t2.hours<<':'<<t2.minutes<<':'<<t2.seconds;
	return 0;
}
