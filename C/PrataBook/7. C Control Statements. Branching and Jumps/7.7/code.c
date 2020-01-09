/*Напишите программу, которая запрашивает количество часов, отработанных за неделю, и выводит значения общей суммы начислений, налогов и чистой зарплаты, исходя из перечисленных ниже утверждений:
а. основная тарифная ставка заработной платы = $10 / час;
б. сверхурочные часы (превышающие 40 часов в неделю) - коэффициент = 1.5;
в. налоговая ставка: 15% с первых $300, 20% со следующих $150, 25% с остатка.
Используйте константы #define и не беспокойтесь, если приведенный пример не соответствует действующему налогооблажению.*/
#define tarif 10
#define overtime 1.5
#define first300 45
#define second150 30
#include <stdio.h>
int main(void)
{
	int hours;
	float salary,over450;
	printf("Количество отработанных часов за неделю: ");
	scanf("%d",&hours);
	if (hours<=40)
		salary=hours*tarif;
	else
	{
		salary=40*tarif;
		hours-=40;
		salary+=hours*tarif*overtime;
	}
	printf("Общая зарплата: %.2f\n",salary);
	if (salary>=300 && salary <450)
		salary-=first300;
	else if (salary==450)
		salary=salary-first300-second150;
	else if (salary>450)
	{
		over450=salary-450;
		over450=over450*25/100;
		salary=salary-first300-second150-over450;
	}		
	printf("Зарплата с вычетом налогов: %.2f\n",salary);
	return 0;
}