/*Напишите функцию, которая возвращает разность между наибольшим и наименьшим элементами в массиве значений типа double. Протестируйте эту функцию с помощью простой программы.*/
#include <stdio.h>
double diff(double array[],int n)
{
	double min;
	double max;
	int i;
	for(i=0,min=array[0],max=array[0]; i<n; i++)
	{
		if (array[i]<min)
			min=array[i];
		if (array[i]>max)
			max=array[i];
	}
	return max-min;
}
int main(void)
{
   double source[5]={1.1,5.2,2.3,4.4,3.5};
   printf("difference between maximum and minimum array value: %.1lf",diff(source,5));
   return 0;
}