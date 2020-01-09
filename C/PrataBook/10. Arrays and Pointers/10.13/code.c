/*Напишите программу, которая предлагает пользователю ввести три набора по пять чисел double. (Для простоты можете полагать, что пользователь отвечает корректно и не вводит нечисловые данные.) Программа должна выполнять следующие ниже действия:
а. хранить информацию в массиве 3х5;
б. вычислять среднее для каждого набора из пяти значений;
в. вычислять среднее для всех значений;
г. определять наибольшее из 15 значений;
д. выводить результаты на экран.
Каждая значительная задача должна решаться посредством отдельной функции с использованием традиционного в языке С подхода к обработке массивов. Выполните задачу б) с помощью функции, которая вычисляет и возвращает среднее значение одномерного массива; воспользуйтесь циклом для вызова этой функции три раза. Функции, реализующие остальные задачи, должны принимать в качестве аргумента массив целиком, а функции, выполняющие задачи в) и г), должны возвращать ответ в вызывающую программу.*/
#include <stdio.h>
#define ROWS 3
#define COLS 5
void show_arr(double arr[ROWS][COLS])
{
	double *array_begin;
	for(array_begin=*arr; *arr<array_begin+COLS*ROWS; ++*arr)
	{
		if((*arr-array_begin)%COLS==0)
			printf("\n");
		printf("%.1lf ",**arr);	
	}	
}
double row_average_value(double arr[COLS])
{
	short i;
	double average=0;
	for(i=0; i<COLS; i++)
		average+=arr[i];
	return average/COLS;
}
double arr_average(double arr[ROWS][COLS])
{
	short i;
	double average,arr_average=0;
	for(i=1; i<ROWS+1; i++,arr++)
	{		
		printf("\nAverage value of the row %d = %.1lf",i,average=row_average_value(*arr));
		arr_average+=average;
	}
	return arr_average/ROWS;
}
double maximum_arrays_value(double arr[ROWS][COLS])
{
	double max,*array_begin;
	for(array_begin=*arr,max=**arr; *arr<array_begin+COLS*ROWS;++*arr)
		if(**arr>max)
			max=**arr;
	return max;
}
void input_elements_in_array(double arr[ROWS][COLS])
{
	double *ptr;
	for(ptr=*arr; ptr<*arr+ROWS*COLS; ptr++)
	{
		if((ptr-*arr)%COLS==0)
			printf("Enter five elements of the row %d:\n",(ptr-*arr)/5+1);		
		scanf("%lf",*&ptr);
	}
}
int main(void)
{
    double arr[ROWS][COLS];/*={
		{4.3,1.3,5.3,3.0,2.0},
        {8.5,8.2,1.2,1.6,2.4},
		{9.1,8.5,6.7,4.3,2.1}};*/
	input_elements_in_array(arr);
	printf("Array:");
	show_arr(arr);
	printf("\nAverage value of array elements = %2.1lf\nMaximum arrays value is %.1lf",arr_average(arr),maximum_arrays_value(arr));
    return 0;
}