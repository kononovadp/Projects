/*Напишите программу, которая реализует меню с использованием массива указателей на функции. Например, выбор пункта а в меню должен активизировать функцию, на которую указывает первый элемент массива.*/
#include<io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int func1(int value, char *str)
{
	printf("Function named %s has number %d\n",str,value);
	return 1;
}
int func2(int value, char *str)
{
	printf("Function named %s has number %d\n",str,value);
	return 2;
}
int func3(int value, char *str)
{
	printf("Function named %s has number %d\n",str,value);
	return 3;
}
int func4(int value, char *str)
{
	printf("Function named %s has number %d\n",str,value);
	return 4;
}
int func5(int value, char *str)
{
	printf("Function named %s has number %d\n",str,value);
	return 5;
}
int main(void)
{
	char ch;
	int (*f1[5])(int,char[10]);
	f1[0]=func1;
	f1[1]=func2;
	f1[2]=func3;
	f1[3]=func4;
	f1[4]=func5;
	printf("a) first function; b) second function; c) third function;\n"
	"d) fourth function; e) fifth function\nYour choise (f - exit): ");
	ch=_getche();
	while(ch!='f')
	{		
		putchar('\n');
		switch(ch)
		{
			case 'a': f1[0](1,"func1"); break;
			case 'b': f1[1](2,"func2"); break;
			case 'c': f1[2](3,"func3"); break;
			case 'd': f1[3](4,"func4"); break;
			case 'e': f1[4](5,"func5"); break;
			case 'f': break;
			default: printf("Incorrect choise\n"); break;
		}
		if (ch!='\n')
			printf("*******************************************************************************\n"
			"a) first function; b) second function; c) third function;\n"
			"d) fourth function; e) fifth function\nYour choise: ");
		ch=_getche();
	}
    return 0;
}