/*Модифицируйте упражнение по программированию 8 из главы 7 так, чтобы пункты меню помечались буквами, а не цифрами; для прекращения ввода используйте букву q вместо цифры 5.*/
#define tarif1 8.75
#define tarif2 9.33
#define tarif3 10.00
#define tarif4 11.20
#define overtime 1.5
#define first300 45
#define second150 30
#include <stdio.h>
void calc_salary(int const tarif)
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
	printf("Зарплата с вычетом налогов: %.2f",salary);
}
int main(void)
{
	char ch;
	printf("a) $8.75/ч     b) $9.33/ч\nc) $10.00/ч    d) 11.20/ч\nq) Выход\n"
	"Номер желаемой тарифной ставки или действие: ");
	ch=getchar();
	while(ch!='q')
	{		
		switch(ch)
		{			
			case 'a': calc_salary(tarif1); break;
			case 'b': calc_salary(tarif2); break;
			case 'c': calc_salary(tarif3); break;
			case 'd': calc_salary(tarif4); break;
			case 'q': break;
			case '\n': break;
			default: printf("Выберите корректное действие"); break;
		}
		if (ch!='\n')
			printf("\n**********************************************\n"
			"a) $8.75/ч     b) $9.33/ч\nc) $10.00/ч    d) 11.20/ч\nq) Выход\n"
			"Номер желаемой тарифной ставки или действие: ");	
		ch=getchar();		
	}
	printf("Работа завершена.");
	return 0;	
}