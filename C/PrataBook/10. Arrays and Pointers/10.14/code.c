/*Выполните упражнение 13, но используйте в качестве параметров функций массивы переменной длины.*/
#include <stdio.h>
void show_arr(int rows, int cols, double arr[rows][cols])
{
	double *array_begin;
	for(array_begin=*arr; *arr<array_begin+cols*rows; ++*arr)
	{
		if((*arr-array_begin)%cols==0)
			printf("\n");
		printf("%.1lf ",**arr);	
	}
}
double row_average_value(int rows, int cols, double arr[cols])
{
	short i;
	double average=0;
	for(i=0; i<cols; i++)
		average+=arr[i];
	return average/cols;
}
double arr_average(int rows, int cols, double arr[rows][cols])
{
	short i;
	double average,arr_average=0;
	for(i=1; i<rows+1; i++,arr++)
	{		
		printf("\nAverage value of the row %d = %.1lf",i,average=row_average_value(rows,cols,*arr));
		arr_average+=average;
	}
	return arr_average/rows;
}
double maximum_arrays_value(int rows, int cols, double arr[rows][cols])
{
	double max,*array_begin;
	for(array_begin=*arr,max=**arr; *arr<array_begin+cols*rows;++*arr)
		if(**arr>max)
			max=**arr;
	return max;
}
void input_elements_in_array(int rows, int cols, double arr[rows][cols])
{
	double *ptr;
	for(ptr=*arr; ptr<*arr+rows*cols; ptr++)
	{
		if((ptr-*arr)%cols==0)
			printf("Enter five elements of the row %d:\n",(ptr-*arr)/5+1);		
		scanf("%lf",*&ptr);
	}
}
int main(void)
{
    int rows=3;
	int cols=5;
	double arr[rows][cols];
	input_elements_in_array(rows,cols,arr);
	printf("Array:");
	show_arr(rows,cols,arr);
	printf("\nAverage value of array elements = %2.1lf\nMaximum arrays value is %.1lf",arr_average(rows,cols,arr),maximum_arrays_value(rows,cols,arr));
    return 0;
}