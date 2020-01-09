/*Напишите функцию по имени chline(ch,i,j), которая выводит требуемый символ в столбцах с i по j. Протестируйте эту функцию с помощью простого драйвера.*/
#include <stdio.h>
void chline(char ch, int i, int j)
{
	int k;
	for (k=i; k<=j; k++)
		if (k==ch)
		{
			printf("\"%c\" найден в таблице символов в интервале с %d по %d = %d",ch,i,j,ch);
			return;
		}
	printf("Символ \"%c\"в интервале с %d по %d не найден в таблице символов.",ch,i,j);
}
int main(void)
{
	chline('Y',65,90);
	return 0;
}