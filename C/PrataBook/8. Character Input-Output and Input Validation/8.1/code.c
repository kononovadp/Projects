/*Напишите программу, которая подсчитывает количество символов во входных данных до достижения конца файла.*/
#include <stdio.h>
int main(void)
{
	int symbol_count=0;
	char ch;
	while(ch=getchar()!=EOF)
		symbol_count++;
	printf("Количество символов в текстовом файле: %d",symbol_count);
	return 0;	
}