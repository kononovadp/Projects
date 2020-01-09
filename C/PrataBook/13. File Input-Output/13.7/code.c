/*Напишите программу, которая открывает два файла. Получать имена файлов можно либо через командную строку, либо предложив пользователю ввести их.
а. Сделайте так, чтобы эта программа выводила строку 1 первого файла, строку 1 второго файла, строку 2 первого файла строку 2 второго файла и т. д. пока не будет выведена последняя строка более длинного (по количеству строк) файла;
б. Модифицируйте программу так, чтобы строки с одиним и тем же номером выводились в одной экранной строке.*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 50
void part_a(FILE *f1, FILE *f2)
{
	char s1[SIZE],s2[SIZE];
	int ch1,ch2;	
	ch1=getc(f1);
	ch2=getc(f2);
	while(ch1!=EOF || ch2!=EOF)
	{
		putchar(ch1);		
		while((ch1=getc(f1))!='\n' && ch1!=EOF)
			putchar(ch1);
		if(ch2!='\n')
			putchar('\n');
		putchar(ch2);
		while((ch2=getc(f2))!='\n' && ch2!=EOF)
			putchar(ch2);
	}
}
void part_b(FILE *f1, FILE *f2)
{
	char s1[SIZE],s2[SIZE];
	int ch1,ch2,i,iterations_count=39;
	ch1=getc(f1);
	ch2=getc(f2);
	while(ch1!=EOF || ch2!=EOF)
	{		
		if(ch1!=EOF)
		{
			i=0;
			while(i++<iterations_count && ch1!='\n' && ch1!=EOF)
			{
				if(ch1!='\n' && ch1!=EOF)
					putchar(ch1);
				ch1=getc(f1);
			}
			while(ch1!='\n' && ch1!=EOF)
				ch1=getc(f1);
			ch1=getc(f1);
			putchar('|');
		}
		i=0;
		while(i++<iterations_count && ch2!='\n' && ch2!=EOF)
		{
			if(ch2!='\n' && ch2!=EOF)
				putchar(ch2);
			ch2=getc(f2);
		}
		while(ch2!='\n' && ch2!=EOF)
			ch2=getc(f2);
		ch2=getc(f2);
		putchar('\n');
	}
}
int main(int argv, char *argz[])
{
    FILE *f1,*f2;
	if((f1=fopen(argz[1],"r"))==NULL)
	{
		printf("Не удалось открыть файл %s",argz[1]);
		exit(EXIT_FAILURE);
	}
	if((f2=fopen(argz[2],"r"))==NULL)
	{
		printf("Не удалось открыть файл %s",argz[2]);
		exit(EXIT_FAILURE);
	}
	part_a(f1,f2);
	putchar('\n');
	for(int j=1; j<81; j++)
		putchar('-');	
	fseek(f1,0L,SEEK_SET);
	fseek(f2,0L,SEEK_SET);
	part_b(f1,f2);
	fclose(f1);
	fclose(f2);
	return 0;
}
