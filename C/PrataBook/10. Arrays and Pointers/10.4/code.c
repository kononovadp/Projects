/*Напишите функцию, которая возвращает индекс наибольшего значения в массиве значений типа double. Протестируйте эту функцию с помощью простой программы.*/
#include <stdio.h>
int max_index(double array[],int n)
{
	double max=array[0];
	int max_ind=0;
	int i;
	for(i=0; i<n; i++)
		if (array[i]>max)
		{
			max=array[i];
			max_ind=i;
		}
	return max_ind;
}
int main(void)
{
   double source[5]={1.1,5.2,2.3,4.4,3.5};
   printf("maximum element index: %d",max_index(source,5));
   return 0;
}