/**3. Модифицируйте класс time из упражнения 3 главы 6 так, чтобы вместо метода add_time() можно было использовать операцию + для складывания двух значений времени. Напишите программу для проверки класса*/
#include <iostream>
using namespace std;
int GetRandomInt(int min, int max)
{
	if(min==max)
		return min;
	return min+(rand()%(max-min));
}
class Time
{
	int hours,minutes,seconds;
	public:
	Time():hours(0),minutes(0),seconds(0){}
	Time(int h,int m,int s):hours(h),minutes(m),seconds(s){}
	void ShowTime()const
	{
		cout<<hours<<':'<<minutes<<':'<<seconds;
	}
	Time operator+(Time t2)
	{
		Time res;
		res.seconds=seconds+t2.seconds;
		if(res.seconds>59)
		{
			res.seconds-=60;
			res.minutes=1;
		}
		res.minutes=res.minutes+minutes+t2.minutes;
		if(res.minutes>59)
		{
			res.minutes-=60;
			res.hours=1;
		}
		res.hours=res.hours+hours+t2.hours;
		return res;
	}
};
int main(void)
{	
	Time t1,t2,result;
	for(int i=0; i<50; i++)
	{
		t1=Time(GetRandomInt(0,24),GetRandomInt(0,60),GetRandomInt(0,60));
		t2=Time(GetRandomInt(0,24),GetRandomInt(0,60),GetRandomInt(0,60));
		result=t1+t2;
		t1.ShowTime();
		cout<<" + ";
		t2.ShowTime();
		cout<<" = ";
		result.ShowTime();
		cout<<endl;
	}
	return 0;
}
