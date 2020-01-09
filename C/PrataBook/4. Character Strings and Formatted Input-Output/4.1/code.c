/* Напишите программу, которая запрашивает имя и фамилию, а затем выводит их в формате фамилия, имя. */
#include <stdio.h>
int main(void)
{
    char name[20],lastname[20];
	printf("Your name: ");
	scanf("%s",name);
	printf("Your lastname: ");
	scanf("%s",lastname);
	printf("Your name and lastname: %s, %s",lastname, name);
	getchar();
	getchar();
}