/*Напишите программу, которая инициализирует двумерный массив значений типа double и использует одну из функций копирования из упражнения 2 для его копирования во второй двумерный массив. (Поскольку двумерный массив - это массив массивов, функция для копирования одномерных массивов может применяться с каждым подмассивом.)*/
#include <stdio.h>
#define rows 3
#define columns 5
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
   double source[rows][columns]={
	   {1.1,5.2,2.3,4.4,3.5},
	   {9.5,8.4,6.3,5.2,3.1},
	   {2.1,3.2,4.3,5.4,7.5}};
   double copy[rows][columns]={{0}}; 
   double *ptr;
   int i,j;
   printf("Исходный массив:");
   for(i=0; i<rows; i++)
   {
	   printf("\n");
	   for(j=0; j<columns; j++)
		   printf("%.1lf ",source[i][j]);
   }
   for(i=0,j=columns; i<rows; i++,j*=2)
	   copy_ptr(*copy+i,*source+i,j);
   printf("\nКопия:");   
   for(i=0; i<rows*columns; i+=columns)
   {
	   printf("\n");	   
	   for(ptr=*copy+i; ptr<*copy+columns+i; ptr++)
		   printf("%.1lf ",*ptr);	   
   }
   return 0;
}