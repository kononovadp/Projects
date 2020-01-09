/*Напишите программу, которая читает входные данные до тех пор, пока не встретит EOF и выводит их на экран. Программа должна распознавать и реализовывать следующие аргументы командной строки:
-p Вывод входных данных в том виде, как есть.
-u Преобразование входных данных в верхний регистр.
-l Преобразование входных данных в нижний регистр.
Кроме того, если аргумент входной строки не указан, программа должна вести себя так, как если бы был зада аргумент -p.*/
#include <stdio.h>
#include<ctype.h>

int main(int n, char *arr[])
{
    char ch;
	if(n>2)
	{
		printf("Too many arguments!");
		exit();
	}
	if(arr[1]==NULL || strcmp(arr[1],"-p")==0)
		while((ch=getchar())!=EOF)
			putchar(ch);
		else
			if(strcmp(arr[1],"-u")==0)
				while((ch=getchar())!=EOF)
					putchar(toupper(ch));
				else
					if(strcmp(arr[1],"-l")==0)
						while((ch=getchar())!=EOF)
							putchar(tolower(ch));
						else
							printf("Incorrect arguments!\n");
	return 0;
}
