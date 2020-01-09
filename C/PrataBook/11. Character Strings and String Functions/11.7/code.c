/*Функция strncpy(s1,s2,n) копирует в точности n символов из строки s2 в строку s1, при необходимости усекая s2 или дополняя ее ненулевыми символами. Целевая строка может не содержать завершающего ненулевого символа, если длина строки s2 равна или больше n. Функция возвращает строку s1. Напишите свою версию этой функции и назовите ее mystrncpy(). Протестируйте функцию в завершенной программе, которая использует цикл для передачи входных значений созданной функции.*/
#include <stdio.h>
#define S1_SIZE 10
#define S2_SIZE 10
void mystrncpy(char s1[], char s2[], int n)
{
	char *p;
	int max_symbols_count,i;	
	if(S1_SIZE-strlen(s1)<n)
		max_symbols_count=S1_SIZE-strlen(s1);
	else
		max_symbols_count=n;
	for(p=s1+strlen(s1),i=0; i<max_symbols_count; i++,p++)
		*p=s2[i];
	*p='\0';
}
int main(void)
{
    char s1[S1_SIZE], s2[S2_SIZE];
	int n;
	printf("Строка 1: ");
	gets(s1,S1_SIZE,stdin);
	printf("Строка 2: ");
	fgets(s2,S2_SIZE,stdin);		
	while(s1[0]!='\0' && s2[0]!='\0')
	{		
		printf("Количество копируемых символов: ");
		scanf("%d",&n);
		getchar();
		mystrncpy(s1,s2,n);
		printf("Результат копирования строк: %s",s1);
		printf("\nСтрока 1: ");
		fgets(s1,S1_SIZE,stdin);
		s1[strlen(s1)-1]='\0';
		printf("Строка 2: ");
		fgets(s2,S2_SIZE,stdin);
		s2[strlen(s2)-1]='\0';
	}
    return 0;
}