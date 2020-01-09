/*Воспользуйтесь одной из функций копирования из упражнения 2 для копирования элементов с 3-го по 5-й семиэлементного массива в массив, состоящий из трех элементов. Суму функцию изменять не нужно; просто подберите правильные фактические аргументы. (Фактическими аргументами не обязательно должны быть имя массива и его размер. Ими только должны быть адрес элемента и количество обрабатываемых элементов.)*/
#include <stdio.h>
#define source_size 7
#define target_size 3
void copy_ptr(double target[], double source[], int n)
{
	double *tp=target;
	double *sp=source;
	int i;
	for(i=0; i<n; i++,tp++,sp++)
		*tp=*sp;
}
int main(void)
{
   double source[source_size]={1.1,5.2,2.3,4.4,3.5,9.5,8.4};
   double target[target_size];
   double *ptr;
   printf("Исходный массив: ");
   for(ptr=source; ptr<source+source_size; ptr++)
	   printf("%.1lf ",*ptr);
   copy_ptr(target,source+2,3);
   printf("\nКопия: ");   
   for(ptr=target; ptr<target+target_size; ptr++)
	   printf("%.1lf ",*ptr);
   return 0;
}