/*Напишите программу, которая объявляет массив 3 х 5 значений типа int и инициализирует его значениями по вашему выбору. Программа должна вывести эти значения, удвоить все значения, после чего вывести новые значения. Напишите одну функцию для вывода значений и еще одну для удваивания значений. В качестве аргументов функции должны принимать имя массива и количество строк.*/
#include <stdio.h>
#define ROWS 3
#define COLS 5
void show_array(int arr[][COLS], int rows)
{
	int i;
	int *ptr;
	for(i=0; i<rows*COLS; i+=COLS)
	{
		printf("\n");
		for(ptr=*arr+i; ptr<*arr+COLS+i; ptr++)
			printf("%.1d ",*ptr);
	}
}
void double_array(int arr[][COLS], int rows)
{
	int i;
	int *ptr;
	for(i=0; i<rows*COLS; i+=COLS)
		for(ptr=*arr+i; ptr<*arr+COLS+i; ptr++)
			*ptr*=2;
}
int main(void)
{
   int array[ROWS][COLS]={
	   {2,4,5,8,1},
	   {1,0,4,6,2},
       {2,8,4,4,1}};
   printf("Исходный массив:");
   show_array(array,ROWS);
   double_array(array,ROWS);
   printf("\nУдвоенный массив:");
   show_array(array,ROWS);
   return 0;
}