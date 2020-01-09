/*Измените предположение а) в упражнении 7 так, чтобы программа предоставляла меню с тарифными ставками. Для выбора тарифной ставки используйте оператор switch. После запуска программы вывод должен быть подобным показанному ниже:
*************************************************************
Число, соответствующее желаемой тарифной ставке или действию:
1) $8.75/ч     2) $9.33/ч
3) $10.00/ч    4) 11.20/ч
5) Выход
*************************************************************
Если выбран вариант с 1 по 4 программа должна запрашивать количество отработанных часов. Программа должна повторяться до тех пор, пока не будет выбран вариант 5. При вводе чего-то отличного от вариантов 1-5 программа должна напомнить пользователю допустимые варианты для ввода и снова ожидать ввод. Для различных тарифных и налоговых ставок применяйте константы #define. */
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
	printf("1) $8.75/ч     2) $9.33/ч\n3) $10.00/ч    4) 11.20/ч\n5) Выход\n"
	"Номер желаемой тарифной ставки или действие: ");
	ch=getchar();
	while(ch!='5')
	{		
		switch(ch)
		{			
			case '1': calc_salary(tarif1); break;
			case '2': calc_salary(tarif2); break;
			case '3': calc_salary(tarif3); break;
			case '4': calc_salary(tarif4); break;
			case '5': break;
			case '\n': break;
			default: printf("Выберите корректное действие"); break;
		}
		if (ch!='\n')
			printf("\n**********************************************\n"
			"1) $8.75/ч     2) $9.33/ч\n3) $10.00/ч    4) 11.20/ч\n5) Выход\n"		
			"Номер желаемой тарифной ставки или действие: ");	
		ch=getchar();		
	}
	printf("Работа завершена.");
	return 0;	
}