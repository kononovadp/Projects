/*Модифицируйте упражнение 8 так, чтобы программа использовала функцию для возврата результатов вычислений.*/
#include <stdio.h>
double calc (double n1, double n2)
{
	return(n1-n2)/(n1*n2);
}
int main(void)
{
	int n1=0;
	int n2=0;
	double d1, d2;
	while(printf("Первое число с плавающей запятой: "),n1=scanf("%lf",&d1),n1>0,
	printf("Второе число с плавающей запятой: "),n2=scanf("%lf",&d2),n2>0)
	{
		printf("(%lf - %lf) / (%lf * %lf)=%lf",d1,d2,d1,d2,calc(d1,d2));
		printf("\n");
	}
	printf("\nГотово.");
	getchar();
	getchar();
	getchar();
	getchar();
	return 0;
}