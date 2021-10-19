/*8. Напишите программу, которая циклически будет запрашивать ввод пользователем денежных сумм, выраженных в фунтах, шиллингах и пенсах (см. упражнение 10 и 12 главы 2). Программа должна складывать введенные суммы и выводить на экран результат, также выраженный в фунтах, шиллингах и пенсах. После каждой итерации программа должна спрашивать пользователя, желает ли он продолжать работу программы. При этом рекомендуется использовать цикл do. Естественной формой взаимодействия программы с пользователем была бы следующая:
Введите первую сумму: J5.10.6
Введите первую сумму: J3.2.6
Всего: J8.13.0
Продолжить (y/n)?
Для того чтобы сложить две суммы, вам необходимо учесть заем одного шиллинга в том случае, если число пенсов окажется больше 11, и одного фунта, если чило шиллингов окажется больше 19.*/
#include <iostream>
#include <conio.h>
using namespace std;
int main(void)
{
	char ch;
	int FirstPound,FirstShilling,FirstPenny,SecondPound,SecondShilling,SecondPenny;
	int PoundSum,ShillingSum,PennySum;	
	do
	{
		ch='.';
		cout<<"First sum: J";
		cin>>FirstPound>>ch>>FirstShilling>>ch>>FirstPenny;
		cout<<"Second sum: J";
		cin>>SecondPound>>ch>>SecondShilling>>ch>>SecondPenny;
		PennySum=FirstPenny+SecondPenny;
		if(PennySum>11)
		{
			PennySum-=12;
			ShillingSum=1;
		}
		else
			ShillingSum=0;
		ShillingSum=ShillingSum+FirstShilling+SecondShilling;
		if(ShillingSum>19)
		{
			ShillingSum-=19;
			PoundSum=1;
		}
		else
			PoundSum=0;
		PoundSum=PoundSum+FirstPound+SecondPound;
		cout<<"Total: "<<PoundSum<<'.'<<ShillingSum<<'.'<<PennySum;
		cout<<endl<<"Do you want to continue (y/n)? ";
		ch=getche();
		while(ch!='y' && ch!='n')
		{
			cout<<endl<<"press y or n: ";
			ch=getche();
		}
		cout<<endl;
	}
	while(ch!='n');
	return 0;
}
