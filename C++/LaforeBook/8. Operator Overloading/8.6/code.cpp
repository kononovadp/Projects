/*6. Добавьте в класс time из упражнения 5 возможность вычитать значения времени, используя перегруженную операцию -, и умножать эти значения, используя тип float и перегруженную операцию **/
#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;
int GetRandomInt2(int min, int max)
{
	if(min==max)
		return min;
	return min+(rand()%(max-min));
}
class Time
{
	int hours,minutes,seconds;
	bool IsTimeNegative;
	public:
	Time():hours(0),minutes(0),seconds(0){IsTimeNegative=false;}
	Time(int h,int m,int s):hours(h),minutes(m),seconds(s){IsTimeNegative=false;}
	void ShowTime()const
	{
		if(IsTimeNegative==true)
			cout<<"-";
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
	Time operator-(Time time2)
	{
		Time res,t1=Time(hours,minutes,seconds);
		Time t2=Time(time2.hours,time2.minutes,time2.seconds);
		res.seconds=t1.seconds-t2.seconds;
		if(res.seconds<0)
		{
			res.seconds=60-res.seconds*-1;
			t2.minutes++;
		}
		res.minutes=t1.minutes-t2.minutes;
		if(res.minutes<0)
		{
			res.minutes=60-res.minutes*-1;
			t2.hours++;
		}
		res.hours=t1.hours-t2.hours;
		if(res.hours>=0)
			return res;
		t1=Time(time2.hours,time2.minutes,time2.seconds);
		t2=Time(hours,minutes,seconds);
		res.seconds=t1.seconds-t2.seconds;
		if(res.seconds<0)
		{
			res.seconds=60-res.seconds*-1;
			t2.minutes++;
		}
		res.minutes=t1.minutes-t2.minutes;
		if(res.minutes<0)
		{
			res.minutes=60-res.minutes*-1;
			t2.hours++;
		}
		res.hours=t1.hours-t2.hours;
		res.IsTimeNegative=true;
		return res;
	}
	Time operator*(Time t2)
	{
		Time res;
		res.seconds=seconds*t2.seconds;
		if(res.seconds>59)
		{
			res.seconds=res.seconds%60;
			t2.minutes+=res.seconds/60;
		}
		res.minutes=minutes*t2.minutes;
		if(res.minutes>59)
		{
			res.minutes=res.minutes%60;
			t2.hours+=res.minutes/60;
		}
		res.hours=hours*t2.hours;		
		return res;
	}
};
int main(void)
{	
	srand(time(0));
	Time t1,t2,result;
	for(int i=0; i<50; i++)
	{
		t1=Time(GetRandomInt2(0,24),GetRandomInt2(0,60),GetRandomInt2(0,60));
		t2=Time(GetRandomInt2(0,24),GetRandomInt2(0,60),GetRandomInt2(0,60));
		result=t1+t2;
		cout<<"--------------------"<<i+1<<"--------------------\n";
		t1.ShowTime();
		cout<<" + ";
		t2.ShowTime();
		cout<<" = ";
		result.ShowTime();
		result=t1-t2;
		cout<<endl;
		t1.ShowTime();
		cout<<" - ";
		t2.ShowTime();
		cout<<" = ";
		result.ShowTime();
		cout<<endl;
		result=t1*t2;
		t1.ShowTime();
		cout<<" * ";
		t2.ShowTime();
		cout<<" = ";
		result.ShowTime();
		cout<<endl;
	}
	return 0;
}
