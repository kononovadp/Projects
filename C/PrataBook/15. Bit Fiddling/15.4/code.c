/*Напишите функцию, которая принимает два аргумента типа int: значение и позицию бита. Функция должна возвращать 1, если бит в этой позиции равен 1, и 0 в противном случае. Протестируйте функцию в какой-нибудь программе.*/
#include <stdio.h>
#include <stdbool.h>
bool bit_activated(int number, int position)
{
	while(position-->0)
	{
		if(number==0)
		{
			printf("Число слишком большое для такой позиции.\n");
			return false;
		}
		number>>=1;
	}
	if((number&1)==1)
		return true;
	else
		return false;
}
int main(void)
{
	int number=683;
	int position=3;
	printf("В числе %d бит в позиции %d ",number,position);
	if(bit_activated(number,position)==true)
		printf("включен.");
	else
		printf("выключен.");
    return 0;
}