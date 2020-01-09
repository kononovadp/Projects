/*Напишите функцию, которая возвращает наибольшее значение в массиве значений типа int. Протестируйте эту функцию с помощью простой программы.*/
#include <stdio.h>
int max_elem(int array[],int n)
{
	int max=array[0];
	int i;
	for(i=0; i<n; i++)
		if (array[i]>max)
			max=array[i];
	return max;
}
int main(void)
{
   int source[5]={1,5,2,4,3};
   printf("maxmum: %d",max_elem(source,5));
   return 0;
}