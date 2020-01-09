/*Напишите функцию по имени min(x,y), которая возвращает меньшее из двух значений типа double. Протестируйте эту функцию с помощью простого драйвера.*/
#include <stdio.h>
double min (double x, double y)
{
	if (x<y)
		return x;
	else
		return y;
}
int main(void)
{
	double x,y;
	printf("Первое число с плавающей запятой: ");
	scanf("%lf",&x);
	printf("Второе число с плавающей запятой: ");
	scanf("%lf",&y);
	printf("Меньшим из двух чисел является %lf",min(x,y));
	return 0;
}