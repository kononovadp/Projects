/*Напишите программу, которая инициализирует двумерный массив 3 х 5 значений типа double и использует функцию, основанную на массивах переменной длины, для копирования этого массива во второй двумерный массив. Кроме того, напишите функцию, основанную на массивах переменной длины, для отображения содержимого этих двух массивов. В общем случае обе функции должны быть способны обрабатывать произвольные массивы N x M. (Если вы не имеете доступа к компилятору, поддерживающему массивы переменной длины, примените традиционный подход С с функциями, которые могут обрабатывать массивы N x 5).*/
#include <stdio.h>
#define ROWS 3
#define COLS 5
void copy_var_arr(int rows, int cols, double source[rows][cols],double target[rows][cols])
{
	int i,j;
	for(i=0; i<rows; i++)
		for(j=0; j<cols; j++)
			target[i][j]=source[i][j];
}
void show_arr(int rows, int cols, double arr[rows][cols])
{
	int i;
	double *ptr;
	for (i=0; i<rows*cols; i+=cols)
	{
		printf("\n");
		for(ptr=*arr+i; ptr<*arr+cols+i; ptr++)
			printf("%.1lf ",*ptr);
	}
}
int main(void)
{
   int rows_var=3;
   int cols_var=5;
   double source[ROWS][COLS]={
	   {4.3,4.3,4.3,3.0,2.0},{8.5,8.2,1.2,1.6,2.4},{9.1,8.5,6.7,4.3,2.1}};
   double target[rows_var][cols_var];
   printf("Исходный массив:");
   show_arr(ROWS,COLS,source);
   copy_var_arr(rows_var,cols_var,source,target);
   printf("\nКопия:");
   show_arr(rows_var,cols_var,target);   
   return 0;
}