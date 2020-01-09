/*Напишите программу, которая генерирует список из 100 случайных чисел в диапазоне от 1 до 10, отсортированный по убыванию. (Можете приспособить к типу int алгоритм сортировки из главы 11, только в этом случае сортируйте сами числа.)*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 100
int sort(int *arr)
{
	bool b=false;
	int temp;
	while(b!=true)
	{
		b=true;
		for(int i=0; i<SIZE-1; i++)
			if (arr[i]<arr[i+1])
			{
				temp=arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=temp;
				b=false;
			}
	}
}
int main(void)
{
    int arr[SIZE];
	srand(time(NULL));
	for(int i=0; i<SIZE; i++)
		printf("%d\n",arr[i]=rand()%10);
	sort(arr);
	printf("Отсортированный список:\n");
	for(int i=0; i<SIZE; i++)
		printf("%d\n",arr[i]);
}
