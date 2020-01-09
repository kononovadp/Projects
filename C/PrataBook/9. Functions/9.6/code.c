/*Напишите и протестируйте функцию, которая принимает в качестве аргументов адреса трех переменных double и помещает наименьшее значение в первую переменную, среднее значение - во вторую, а наибольшее значение - в третью.*/
#include <stdio.h>
void larger_of (double *x, double *y, double *z)
{
	double temp;
	int i;
	printf("Исходные данные: x = %lf; y = %lf; z = %lf;\n",*x,*y,*z);	
	for (i=0; i<2; i++)
	{
		if (*x>*y)
		{
			temp=*x;
			*x=*y;
			*y=temp;
		}
		if (*y>*z)
		{
			temp=*y;
			*y=*z;
			*z=temp;
		}
	}	
}
int main(void)
{
	double x=9.675;
	double y=5.075;
	double z=10.898;
	larger_of(&x,&y,&z);
	printf("Содержимое x, y и z после вызова функции:\nx = %lf; y = %lf; z = %lf.\n",x,y,z);
	return 0;
}