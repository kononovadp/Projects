/*Ниже приведена часть программы, использующей функцию с переменным числом аргументов. Функция new_d_array() принимает аргумент типа int и переменное количество аргументов double. Она возвращает указатель на блок памяти, выделенный функцией malloc(). Аргумент int задает количество элементов, которые должны быть в динамическом масиве, а значения double предназначены для инициализации элементов, при этом первое значение присваивается первому элементу, второе - второму и т. д. Завершите программу, предоставив код для функций show_array() и new_d_array().*/
#include <stdio.h>
#include <stdarg.h>
double *new_d_array(int n,...)
{
	va_list list;
	va_start(list,n);
	double *arr=(double*)malloc(n*sizeof(double));
	for(int i=0; i<n; i++)
		arr[i]=va_arg(list,double);	
	return arr;
}
void show_array(double *arr, int n)
{
	for(int i=0; i<n; i++)
		printf("%lf\n",arr[i]);
	printf("------------------\n");
}
int main(void)
{
    double *p1;
	double *p2;
	p1=new_d_array(5, 1.2, 2.3, 3.4, 4.5, 5.6);
	p2=new_d_array(4, 100.0, 20.00, 8.08, -1890.0);
	show_array(p1,5);
	show_array(p2,4);
	free(p1);
	free(p2);
    return 0;
}