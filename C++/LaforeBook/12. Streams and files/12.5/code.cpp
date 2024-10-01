/*5. Создайте класс time, включающий себя целые значения часов, минут и секунд. Напишите метод get_time(), спрашивающий время у пользователя, и метод put_time(), выводящий время в формате 12:59:59. Внесите в функцию get_time() проверку на ошибки, чтобы минимизировать возможность неправильного ввода пользователем. Эта функция должна отдельно спрашивать часы, минуты и секунды, проверяя каждое введенное значение на наличие флагов ошибок ios, а также проверяя, укладывается ли значение в заданный диапазон. Для часов диапазон составляет от 0 до 23, а для минут и секунд — от 0 до 59. Не вводите данные в виде символьных строк с последующим конвертированием. Вводите значения сразу же как int. Это означает, что вы не сможете выявлять записи с ненужными здесь десятичными запятыми, но это в данной программе не так важно. В main() используйте цикл для получения значений времени от пользователя функцией get_time(), затем для их вывода - функцией put_time():
Введите часы: 8
Введите минуты: 2
Введите секунды: 39
Время = 8:02:39
Продолжить (y/n)? у
Введите часы: 28
Значение часов должно лежать между 0 и 23!
Введите часы: 1
Введите минуты: 10
Введите секунды: пять
Неправильно введены секунды!
Введите секунды: 5
Время = 1:10:0*/
#include <iostream>
#include <conio.h>
using namespace std;
class time1
{
	int hours,minutes,seconds;
	public:
	time1():hours(0),minutes(0),seconds(0){}
	void get_time()
	{
		cout<<"Hours (0-23): ";
		while(!(cin>>hours) || hours<0 || hours>23)
		{
			if(hours<0 || hours>23)
				cout<<"Incorrect count of hours, try again: ";
			else
				cout<<"Incorrect value, error code: "<<cin.rdstate()<<". Try again: ";
			cin.clear();
			cin.ignore(1000,'\n');
		}
		cout<<"Minutes (0-59): ";
		while(!(cin>>minutes) || minutes<0 || minutes>59)
		{
			if(minutes<0 || minutes>59)
				cout<<"Incorrect count of minutes, try again: ";
			else
				cout<<"Incorrect value, error code: "<<cin.rdstate()<<". Try again: ";
			cin.clear();
			cin.ignore(1000,'\n');
		}
		cout<<"Seconds (0-59): ";
		while(!(cin>>seconds) || seconds<0 || seconds>59)
		{
			if(seconds<0 || seconds>59)
				cout<<"Incorrect count of seconds, try again: ";
			else
				cout<<"Incorrect value, error code: "<<cin.rdstate()<<". Try again: ";
			cin.clear();
			cin.ignore(1000,'\n');
		}
	}
	void put_time()
	{
		cout<<"Your time: "<<hours<<":"<<minutes<<":"<<seconds<<endl;
	}
};
int main(void)
{	
	time1 MyTime;
	char ch=0;
	while(ch!='0')
	{
		MyTime.get_time();
		MyTime.put_time();
		cout<<"Press 1 to start again or 0 to exit: ";		
		ch=getch();
		while(ch!='0' && ch!='1')		
			ch=getch();
		cout<<ch<<endl;
	}
	return 0;
}
