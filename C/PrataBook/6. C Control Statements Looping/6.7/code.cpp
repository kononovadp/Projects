/*Напишите программу, которая читает слово в символьный массив, а затем выводит это слово в обратном порядке. Подсказка: воспользуйтесь функцией strlen() (глава 4) для вычисления индекса последнего символа массива.*/
#include <stdio.h>
#include <conio.h>
#define size 50
int main(void)
{
	int n,i=0;
	char arr[size];
	char ch;
	printf("Слово: ");
	while(ch!=13)
	{
		ch=getche();
		arr[i]=ch;
		i++;
	}
	printf("\n");
	while(i-- >0)
		printf("%c",arr[i]);
	getchar();
	return 0;
}