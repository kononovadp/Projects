/*Напишите функцию, которая устанавливает значение каждого элемента массива в сумму соответствующих элементов двух других массивов. Другими словами, если массив 1 имеет значения 2, 4, 5 и 8, а массив 2 - значения 1, 0, 4 и 6, то эта функция присваивает массиву 3 значения 3, 4, 9 и 14. Функция должна принимать в качестве аргументов имена трех массивов и их размеры. Протестируйте эту функцию с помощью простой программы.*/
#include <stdio.h>
#define SIZE 4
void array_elements_sum(int size, int source1[size], int source2[size], int target[size])
{
	int i;
	for(i=0; i<size; i++)
		target[i]=source1[i]+source2[i];
}
void show_array(int size, int arr[size])
{
	int i;
	for(i=0; i<size; i++)
		printf("%d ",arr[i]);
}
int main(void)
{
   int array1[SIZE]={2,4,5,8};
   int array2[SIZE]={1,0,4,6};
   int array3[SIZE];
   printf("Первый массив: ");
   show_array(SIZE,array1);
   printf("\nВторой массив: ");
   show_array(SIZE,array2);
   array_elements_sum(SIZE,array1,array2,array3);
   printf("\nМассив суммы:  ");
   show_array(SIZE,array3);
   return 0;
}