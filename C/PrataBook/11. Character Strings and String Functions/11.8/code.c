/*Напишите функцию string_in(), которая принимает в качестве аргумента два указателя на строки. Если вторая строка содержится внутри первой, функция должна возвратить адрес, с которого начинается вторая строка в первой строке. Например вызов string_in("данные", "ан") возвратит адрес символа а в строке данные. В противном случае функция должна возвратить нулевой указатель. Протестируйте функцию в завершенной программе, которая использует цикл для передачи входных значений созданной функции.*/
#include <stdio.h>
#define S1_SIZE 15
#define S2_SIZE 15
char *string_in(char s1[], char s2[])
{
	char *p_main,*p;
	int i;
	for(p_main=s1; p_main<s1+strlen(s1); p_main++)
	{
		for(p=p_main,i=0; p<p_main+strlen(s2); p++,i++)
			if(*p!=s2[i])
				break;
		if(i==strlen(s2))
			return p_main;
	}
	return NULL;
}
int main(void)
{
    char s1[S1_SIZE], s2[S2_SIZE],*p;
	printf("Строка 1: ");
	fgets(s1,S1_SIZE,stdin);
	s1[strlen(s1)-1]='\0';
	printf("Строка 2: ");
	fgets(s2,S2_SIZE,stdin);
	s2[strlen(s2)-1]='\0';	
	while(s1[0]!='\0' && s2[0]!='\0')
	{		
		p=string_in(s1,s2);
		if (p==NULL)
			printf("Строка не найдена");
		else
			printf("Строка найдена, первый символ искомой строки: %c",*p);			
		printf("\nСтрока 1: ");
		fgets(s1,S1_SIZE,stdin);
		s1[strlen(s1)-1]='\0';
		printf("Строка 2: ");
		fgets(s2,S2_SIZE,stdin);
		s2[strlen(s2)-1]='\0';
	}
    return 0;
}