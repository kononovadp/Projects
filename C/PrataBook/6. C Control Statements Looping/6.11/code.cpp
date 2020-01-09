/*Напишите программу, которая читает восемь целых чисел в массив, после чего выводит их в обратном порядке*/
#include <stdio.h>
int main(void)
{
	int i=0;
	int a[8];
	printf("Введите через пробел 8 целых чисел:\n");
	for (i=0; i<8; i++)
		scanf("%d",&a[i]);
	printf("----------\n");
	for(i=7; i>-1; i--)
		printf("%d  ",a[i]);
	getchar();
	getchar();
	getchar();
	return 0;
}