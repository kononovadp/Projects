/*11. Используя структуру time из упражнения 9, напишите программу, которая получает от пользователя два значения времени в формате 12:59:59, сохраняет их в переменных типа struct time, затем переводит оба значения в секунды, складывает их, переводит сумму в исходный формат, сохраняет его в переменной типа time и выводит полученный результат на экран в формате 12:59:59.*/
#include <iostream>
using namespace std;
struct time
{
	int hours,minutes,seconds;
};
unsigned long long int GetSecondsCount(struct time t)
{
	return t.hours*3600+t.minutes*60+t.seconds;
}
int main(void)
{
	
	struct time t1,t2;
	unsigned long long int sec1,sec2;
	char ch;
	cout<<"Time 1 in format hh:mm:ss: ";
	cin>>t1.hours>>ch>>t1.minutes>>ch>>t1.seconds;
	cout<<"Time 2 in format hh:mm:ss: ";
	cin>>t2.hours>>ch>>t2.minutes>>ch>>t2.seconds;
	sec1=GetSecondsCount(t1);
	sec2=GetSecondsCount(t2);
	sec1+=sec2;
	t2.seconds=sec1%60;
	sec1-=t2.seconds;
	sec1/=60;
	t2.minutes=sec1%60;
	sec1-=t2.minutes;
	t2.hours=sec1/60;
	cout<<"Sum of two times: "<<t2.hours<<':'<<t2.minutes<<':'<<t2.seconds;
	return 0;
}
