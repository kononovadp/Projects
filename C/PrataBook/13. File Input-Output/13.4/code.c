/*Напишите программу, которая последовательно отображает на экране содержимое всех файлов, перечисленных в командной строке. Для управления циклом используйте argc.*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char *argv[])
{
	FILE *f;
	int ch;
	for(int i=1; i<argc; i++)
	{		
		if((f=fopen(argv[i],"r"))==NULL)
		{
			printf("Файл %s не найден.\n",argv[i]);
			continue;
		}
		printf("СОДЕРЖИМОЕ ФАЙЛА %s:\n",argv[i]);
		while((ch=getc(f))!=EOF)
			putchar(ch);
		printf("\n---------------------------------------------\n");
	}
	fclose(f);
    return 0;
}