/*Напишите и протестируйте функцию по имени larger_of(), которая заменяет содержимое двух переменных double большим из их значений. Например, вызов larger_of(x,y) присвоит переменным x и y большее из их значений.*/
#include <stdio.h>
void larger_of (double *x, double *y)
{
	printf("Исходные данные: x = %lf; y = %lf.\n",*x,*y);
	if (*x>*y)
		*y=*x;
	else
		*x=*y;
}
int main(void)
{
	double x=10.898;
	double y=9.675;
	larger_of(&x,&y);
	printf("Содержимое x и y после вызова функции:\nx = %lf; y = %lf.\n",x,y);
	return 0;
}