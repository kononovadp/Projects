/* *3. Создайте класс с именем time, содержащий три поля типа int, предназначенные для хранения часов, минут и секунд. Один из конструкторов класса должен инициализировать поля нулевыми значениями, а другой конструктор — заданным набором значений. Создайте метод класса, который будет выводить значения полей на экран в формате 11:59:59, и метод, складывающий значения двух объектов типа time, передаваемых в качестве аргументов. В функции main() следует создать два инициализированных объекта (подумайте, должны ли они быть константными) и один неинициализированный объект. Затем сложите два инициализированных значения, а результат присвойте третьему объекту и выведите его значение на экран. Где возможно, сделайте методы константными.*/
#include <iostream>
using namespace std;
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
	Time SumOfTimes(Time t1,Time t2)
	{
		Time res;
		res.seconds=t1.seconds+t2.seconds;
		if(res.seconds>59)
		{
			res.seconds-=59;
			res.minutes=1;
		}
		res.minutes=res.minutes+t1.minutes+t2.minutes;
		if(res.minutes>59)
		{
			res.minutes-=59;
			res.hours=1;
		}
		res.hours=res.hours+t1.hours+t2.hours;
		return res;
	}
};
int main(void)
{
	Time t1(10,55,50),t2(10,55,10),t3;
	t1.ShowTime();
	cout<<" + ";
	t2.ShowTime();
	cout<<" = ";
	t3=t3.SumOfTimes(t1,t2);
	t3.ShowTime();
	return 0;
}
