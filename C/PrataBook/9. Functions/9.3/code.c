/*Напишите функцию, которая принимает три аргумента: символ и два целых числа. Символ предназначен для вывода. Первое целое значение задает количество указанных символов в строке, а второе целое число устанавливает количество таких строк. Напишите программу, в которой используется эта функция.*/
#include <stdio.h>
void buildstring(char ch, int chars_number, int strings_number)
{
	int i,j;
	char string[100];
	for (i=1; i<strings_number+1; i++)
	{
		for (j=0; j<chars_number; j++)
			string[j]=ch;
		printf("Строка %d: %s\n",i,string);
		ch++;
	}
}
int main(void)
{
	buildstring('A',10,5);
	return 0;
}