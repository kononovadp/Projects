/*6. Модифицируйте программу, описанную в упражнении 11 главы 4 «Структуры», складывающую два структурных значения типа time. Теперь программа должна включать в себя две функции. Первая, time_to_secs(), принимает в качестве аргумента значение типа time и возвращает эквивалентное значение в секундах типа long. Вторая, secs_to_time(), в качестве аргумента принимает число секунд, имеющее тип long, а возвращает эквивалентное значение типа time.*/
#include <iostream>
struct time
{
	int hours,minutes,seconds;
};
long time_to_secs(time t)
{
	return t.hours*3600+t.minutes*60+t.seconds;
}
time secs_to_time(long sec)
{
	time t;
	t.seconds=sec%60;
	sec-=t.seconds;
	sec/=60;
	t.minutes=sec%60;
	sec-=t.minutes;
	t.hours=sec/60;
	return t;
}
using namespace std;
int main(void)
{
	time t1,t2;
	unsigned long long int sec1,sec2;
	char ch;
	cout<<"Time 1 in format hh:mm:ss: ";
	cin>>t1.hours>>ch>>t1.minutes>>ch>>t1.seconds;
	cout<<"Time 2 in format hh:mm:ss: ";
	cin>>t2.hours>>ch>>t2.minutes>>ch>>t2.seconds;
	sec1=time_to_secs(t1);
	sec2=time_to_secs(t2);
	t2=secs_to_time(sec1+sec2);
	cout<<"Sum of two times: "<<t2.hours<<':'<<t2.minutes<<':'<<t2.seconds;
	return 0;
}
