/*Напишите функцию, которая заменяет содержимое указанной строки этой же строкой но с обратным порядком следования символов. Протестируйте функцию в завершенной программе, которая использует цикл для передачи входных зхначений заданной функции.*/
#include <stdio.h>
#define S1_SIZE 15
void invert_string(char s1[])
{
	char temp;
	int i;
	for(i=0; i<strlen(s1)/2; i++)
	{
		temp=s1[i];
		s1[i]=s1[strlen(s1)-i-1];
		s1[strlen(s1)-i-1]=temp;
	}
}
int main(void)
{
    char s1[S1_SIZE];
	printf("Строка 1: ");
	fgets(s1,S1_SIZE,stdin);
	s1[strlen(s1)-1]='\0';	
	while(s1[0]!='\0')
	{		
		invert_string(s1);
		printf("Инвертированная строка: %s",s1);
		printf("\nСтрока 1: ");
		fgets(s1,S1_SIZE,stdin);
		s1[strlen(s1)-1]='\0';		
	}
    return 0;
}