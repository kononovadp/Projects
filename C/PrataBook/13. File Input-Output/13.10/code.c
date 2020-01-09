/*Напишите программу, открывающую текстовый файл, имя которого получается интерактивно. Организуйте цикл, который предлагает пользователю ввести позицию в файле. Затем программа должна вывести часть файла, начиная с этой позиции и заканчивая следующим символов новой строки. Цикл ввода должен завершаться при вводе отрицательного или нечислового значения.*/
#include <stdio.h>
#include <stdlib.h>
long int filesize(FILE *fp)
{
	fseek (fp, 0, SEEK_END);
	long int size=ftell(fp);
	fseek (fp, 0, SEEK_SET);
	return size;
}
int main(void)
{
    FILE *f;
	char file_name[40];
	printf("Имя файла: ");
	scanf("%s",&file_name);
	if((f=fopen(file_name,"r"))==NULL)
	{
		printf("Невозможно открыть файл.");
		exit(EXIT_FAILURE);
	}
	int n,ch,file_size=filesize(f);
	printf("Позиция в файле: ");	
	while((scanf("%d",&n))==1 && n>=0)
	{
		if(n>=file_size)
			printf("Файл не настолько велик.");
		else
		{
			fseek(f,n,SEEK_SET);
			while((ch=getc(f))!='\n' && ch!=EOF)
			putchar(ch);
		}
		printf("\nПозиция в файле: ");
	}
	fclose(f);	
    return 0;
}
