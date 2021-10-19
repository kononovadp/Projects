/*9. Создайте структуру с именем time. Три ее поля, имеющие тип int, будут называться hours, minutes и seconds. Напишите программу, которая просит пользователя ввести время в формате часы, минуты, секунды. Можно запрашивать на ввод как три значения сразу, так и выводить для каждой величины отдельное приглашение. Программа должна хранить время в структурной переменной типа time и выводить количество секунд в введенном времени, определяемое следующим образом: long totalseсs = t1.hours*3600 + t1.minutes*60 + t1.seconds*/
#include <iostream>
using namespace std;
int main(void)
{
	struct time
	{
		int hours,minutes,seconds;
	};
	struct time t;
	char ch;
	cout<<"Time in format hh:mm:ss: ";
	cin>>t.hours>>ch>>t.minutes>>ch>>t.seconds;
	cout<<"\nseconds count: "<<t.hours*3600+t.minutes*60+t.seconds;
	return 0;
}
