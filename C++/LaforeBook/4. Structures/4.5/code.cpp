/*5. Создайте структуру типа date, содержащую три поля типа int: месяц, день и год. Попросите пользователя ввести день, месяц и год в формате 31/12/2002, сохраните введенное значение в структурной переменной, а затем извлеките данные из этой переменной и выедите их на экран в том же формате, в каком они вводились.*/
#include <iostream>
using namespace std;
struct date
{	
	int day;
	int month;
	int year;
};
int main(void)
{
	struct date d;
	cout<<"Enter a date in the format dd/mm/yyyy: ";
	scanf("%d/%d/%d",&d.day,&d.month,&d.year);//cin>>d.day>>d.month>>d.year;	
	cout<<"Your date is "<<d.day<<'/'<<d.month<<'/'<<d.year;
	return 0;
}
