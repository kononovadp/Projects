/*5. Пополните класс time, рассмотренный в упражнении 3, перегруженными операциями увеличения (++) и уменьшения (--), которые работают в обеих, префиксной и постфиксной, формах записи и возвращают значение. Дополните функцию main(), чтобы протестировать эти операции*/
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
	public:
	Time():hours(0),minutes(0),seconds(0){}
	Time(int h,int m,int s):hours(h),minutes(m),seconds(s){}
	void ShowTime()const
	{
		cout<<setw(2)<<hours<<':'<<setw(2)<<minutes<<':'<<setw(2)<<seconds;
	}
	Time operator+(Time t2)
	{
		Time res;
		res.seconds=seconds+t2.seconds;
		if(res.seconds>59)
		{
			res.seconds-=59;
			res.minutes=1;
		}
		res.minutes=res.minutes+minutes+t2.minutes;
		if(res.minutes>59)
		{
			res.minutes-=59;
			res.hours=1;
		}
		res.hours=res.hours+hours+t2.hours;
		return res;
	}
	Time operator++()
	{
		seconds++;
		if(seconds==60)
		{
			minutes++;
			seconds=0;
		}
		if(minutes==60)
		{
			hours++;
			minutes=0;
		}
		return Time(hours,minutes,seconds);
	}
	Time operator++(int)
	{
		Time PrevTime(hours,minutes,seconds);
		seconds++;
		if(seconds==60)
		{
			minutes++;
			seconds=0;
		}
		if(minutes==60)
		{
			hours++;
			minutes=0;
		}
		return PrevTime;
	}
	Time operator--()
	{
		seconds--;
		if(seconds<0)
		{
			seconds=59;
			minutes--;
		}
		if(minutes<0)
		{
			minutes=59;
			hours--;
		}
		if(hours<0)
			hours=0;
		return Time(hours,minutes,seconds);
	}
	Time operator--(int)
	{
		Time PrevTime(hours,minutes,seconds);
		seconds--;
		if(seconds<0)
		{
			seconds=59;
			minutes--;
		}
		if(minutes<0)
		{
			minutes=59;
			hours--;
		}
		if(hours<0)
			hours=0;
		return PrevTime;
	}
};
int main(void)
{
	srand(time(0));
	Time CurTime,NewTime;
	for(int i=0; i<50; i++)
	{
		CurTime=Time(GetRandomInt2(0,24),GetRandomInt2(0,60),GetRandomInt2(0,60));
		CurTime.ShowTime();
		cout<<";\n++CurTime: ";
		NewTime=++CurTime;
		CurTime.ShowTime();
		cout<<"; NewTime=++CurTime: ";
		NewTime.ShowTime();
		cout<<";\nCurTime++: ";
		NewTime=CurTime++;
		CurTime.ShowTime();
		cout<<"; NewTime=CurTime++: ";
		NewTime.ShowTime();
		cout<<";\n--CurTime: ";
		NewTime=--CurTime;
		CurTime.ShowTime();
		cout<<"; NewTime=--CurTime: ";
		NewTime.ShowTime();
		cout<<";\nCurTime--: ";
		NewTime=CurTime--;
		CurTime.ShowTime();
		cout<<"; NewTime=CurTime--: ";
		NewTime.ShowTime();
		cout<<"\n-----------------------------------------\n";
	}	
	return 0;
}
