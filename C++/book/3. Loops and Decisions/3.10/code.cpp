﻿/*10. Модифицируйте программу, описанную в упражнении 7, так, чтобы вместо вычисления текущей суммы на вашем счете она вычисляла, сколько лет потребуется для того, чтобы при заданной процентной ставке и величине начального вклада сумма на вашем счете достигла запрашиваемого вами значения. Для хранения найденного числа лет используйте переменную целого типа (можно отбросить дробную часть значения, полученного в результате расчета). Самостоятельно выберите тип цикла, подходящий для решения задачи.*/
#include <iostream>
using namespace std;
int main(void)
{
	double c,in,rs;
	int i,y=0;
	cout<<"Contribution: ";
	cin>>c;
	cout<<"Interest: ";
	cin>>in;
	cout<<"Required sum: ";
	cin>>rs;
	in/=100;
	while(c<rs)
	{
		c=c+(c*in);
		y++;
	}
	cout<<"You will get "<<rs<<" dollars in "<<y<<" years";
	return 0;
}