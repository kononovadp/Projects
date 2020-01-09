/*Ниже приведена часть программы:
#include <stdio.h>
#define SIZE 1000
int main(void)
{
    int *pa;
	int size;
	int value;
	printf("Введите количество элементов: ");
	while (scanf("%d", &size)==1 && size>0)
	{
		printf("Введите значение для инициализации: ");
		scanf("%d",&value);
		pa=make_array(size, value);
		if (pa)
		{
			show_array(pa,size);
			free(pa);
		}
		printf("Введите количество элементов(<1 для завершения): ");
	}
	return 0;
}
Завершите программу, предоставив определение функций make_array() и show_array(); Функция make_array принимает два аргумента. Первый аргумент - это количество элементов в массиве значений int, а второй аргумент - значение, которое должно быть присвоено каждому элементу массива. Эта функция использует malloc() для создания массива подходящего размера, присваивает каждому элементу заданное значение и возвращает указатель на массив. Функция ahow_array() отображает содержимое массива по восемь элементов в строке.*/
#include <stdio.h>
int *make_array(int size, int value)
{
	int *p=(int*)malloc(size * sizeof(int));
	for(int i=0; i<size; i++)
		p[i]=value;
	return p;
}
void show_array(int *arr, int size)
{	
	for(int i=0; i<size; i++)
	{
		if(i>0 && i%8==0)
			printf("\n");
		printf("%d ",arr[i]);		
	}
}
int main(void)
{
    int *pa;
	int size;
	int value;
	printf("Введите количество элементов: ");
	while (scanf("%d", &size)==1 && size>0)
	{
		printf("Введите значение для инициализации: ");
		scanf("%d",&value);
		pa=make_array(size, value);
		if (pa)
		{
			show_array(pa,size);
			free(pa);
		}
		printf("\nВведите количество элементов(<1 для завершения): ");
	}
	return 0;
}