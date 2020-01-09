/*Напишите функцию, которая изменяет порядок следования содержимого массива значений типа double на противоположный и протестируйте ее в простой программе.*/
#include <stdio.h>
void invert_arr(double array[],int n)
{
	double temp;
	int i;
	for(i=0, n--; i<n-1; i++,n--)
	{
		temp=array[i];
		array[i]=array[n];
		array[n]=temp;
	}
	
}
int main(void)
{
   double source[5]={1.1,5.2,2.3,4.4,3.5};
   int i;
   for(i=0; i<5; i++)
	   printf("%lf ",source[i]);
   invert_arr(source,5);
   printf("\n");
   for(i=0; i<5; i++)
	   printf("%lf ",source[i]);
   return 0;
}