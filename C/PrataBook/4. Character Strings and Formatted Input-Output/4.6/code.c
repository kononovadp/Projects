/*Напишите программу, которая запрашивает имя пользователя и его фамилию. Сделайте так, чтобы она выводила введенные имена в одной строке и количество символов в каждом слове в следующей строке. Выровняйте каждое количество символов по окончанию соответствующего имени, как показано ниже:
Иван Петров
   4      6
Затем сделайте так, чтобы программа выводила ту же информацию, но с количеством символов, выровненным по началу каждого слова:
Иван Петров
4    6*/
#include <stdio.h>
#include <conio.h>
int main(void)
{
	char name[20],surname[20];
	printf("Введите имя: ");
	scanf("%s",name);
	printf("Введите фамилию: ");
	scanf("%s",surname);
	printf("%s %s\n%*d%*d\n%s %s\n%-*d %-d",name, surname, strlen(name),strlen(name), 
	strlen(surname)+1,strlen(surname),name,surname,strlen(name),strlen(name),strlen(surname));
	getchar();
	getchar();
	return 0;
}