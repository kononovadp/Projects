/* *1. Номер телефона, например (212)767-8900, можно условно разделить на три части: код города (212), номер телефонной станции (767) и номер абонента (8900). Напишите программу с использованием структуры, позволяющую раздельно хранить эти три части телефонного номера. Назовите структуру phone. Создайте две структурные переменные типа phone. Инициализацию одной из них произведите сами, а значения с другой запросите с клавиатуры. Затем выведите содержимое обеих переменных на экран. Результат работы программы должен выглядеть приблизительно так:
Введите код города, номер станции и номер абонента:
415 555 1212
Мой номер (212)767-8900
Ваш номер (415)555-1212*/
#include <iostream>
using namespace std;
struct phone
{
	int prefix;
	int NumberOfTelephoneStation;
	int CustomerNumber;
};
int main(void)
{
	struct phone p1;
	struct phone p2;
	p1.prefix=212;
	p1.NumberOfTelephoneStation=767;
	p1.CustomerNumber=8900;
	printf("Prefix: ");
	scanf("%d",&p2.prefix);
	printf("Number of telephone station: ");
	scanf("%d",&p2.NumberOfTelephoneStation);
	printf("Customer number: ");
	scanf("%d",&p2.CustomerNumber);
	printf("My number (%d)%d-%d\nYour number (%d)%d-%d",p1.prefix,p1.NumberOfTelephoneStation,p1.CustomerNumber, p2.prefix,p2.NumberOfTelephoneStation,p2.CustomerNumber);
	return 0;
}
