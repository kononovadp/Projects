/*Напишите функцию, которая в качестве аргумента принимает имя массива элементов int, размер массива и значение, представляющее количество выборок. Функция должна случайным образом выбирать из массива указанное количество элементов и выводить их значения. Ни один элемент массива не должен выбираться более одного раза. Это эмулирует выбор чисел в лотерее или членов жюри. Если в данной реализации доступна функция time(), которая обсуждалась в главе 12, или подобная ей функция, то для вывода данных воспользуйтесь функцией srand(), чтобы инициализировать генератор случайных чисел rand(). Напишите простую программу для тестирования этой функции.*/
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
void get_random_elements(int *arr, int arr_size, int elements_count)
{
	int t,i,n=0;
	int chosen_elements[elements_count];
	bool b;
	while(n<elements_count)
	{
		t=rand()%elements_count;
		b=false;
		for(i=0; i<elements_count; i++)
			if(t==chosen_elements[i])
				b=true;
		if(b==false)
		{
			chosen_elements[n]=t;
			n++;
		}
	}
	for(i=0; i<elements_count; i++)
		printf("index = %d; element = %d\n",chosen_elements[i],arr[chosen_elements[i]]);
}
int main(void)
{    
	srand (time(NULL));
	int i,size=10;
	int elements_count=5;
	int arr[size];
	for(i=0; i<size; i++)
		arr[i]=rand()%20;
	for(i=0; i<size; i++)
		printf("%d\n",arr[i]);
	printf("Random chosen indexes and elements:\n");
	get_random_elements(arr,size,elements_count);
    return 0;
}