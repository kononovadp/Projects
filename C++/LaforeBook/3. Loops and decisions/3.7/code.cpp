﻿/*7. Напишите программу, рассчитывающую сумму денег, которые вы получите при вложении начальной суммы с фиксированной процентной ставкой дохода через определенное количество лет. Пользователь должен вводить с клавиатуры начальный вклад, число лет и процентную ставку. Примером результата работы программы может быть следующий:
Введите начальный вклад: 3000
Введите число лет: 10
Введите процентную ставку: 5.5
Через 10 лет вы получите 5124.43 доллара.
В конце первого года вы получите 3000+(3000*0.055)=3165 долларов. В конце следующего года вы получите 3165+(3165*0.055)=3339.08 долларов. Подобные вычисления удобно производить с помощью цикла for.*/
#include <iostream>
using namespace std;
int main(void)
{
	double c,in;
	int i,y;
	cout<<"Contribution: ";
	cin>>c;
	cout<<"Years count: ";
	cin>>y;
	cout<<"Interest: ";
	cin>>in;
	for(i=0,in/=100; i<y; i++)
		c=c+(c*in);
	cout<<"In "<<y<<" you will get "<<c<<" dollars";
	return 0;
}