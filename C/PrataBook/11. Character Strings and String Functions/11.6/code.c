/*Напишите функцию по имени is_within(), которая в качестве двух своих параметров принимает символ и указатель на строку. Функция должна возвращать ненулевое значение, если заданный символ содержится в строке, и ноль в противном случае. Протестируйте функцию в завершенной программе, которая использует цикл для передачи входных значений созданной функции.*/
#include <stdio.h>
#include <stdbool.h>
#define SIZE 10
bool is_within(char arr[], char ch)
{
	char *p;	
	for(p=arr; *p!='\0'; p++)
		if(*p==ch)
			return true;
	return false;
}
int main(void)
{
    char arr[SIZE],ch;
	bool b;
	printf("Введите строку (пустая строка - выход): ");
	while(fgets(arr,SIZE,stdin)!=NULL && arr[0]!='\n')
	{		
		printf("Введите символ: ");
		scanf("%c",&ch);
		getchar();
		b=is_within(arr,ch);
		if(b==0)
			printf("Введенный символ не найден\n");
		else
			printf("Введенный символ найден\n");
		printf("Введите строку (пустая строка - выход): ");
	}
    return 0;
}