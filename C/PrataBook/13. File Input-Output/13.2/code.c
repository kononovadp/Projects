/*Напишите программу копирования файлов, которая получает имя исходного файла и имя копии из командной строки. Используйте стандартный ввод-вывод и двоичный режим.*/
#include <stdio.h>
#include <stdlib.h> // прототип exit()
long int filesize(FILE *fp)
{
	fseek (fp, 0, SEEK_END);
	long int size=ftell(fp);
	fseek (fp, 0, SEEK_SET);
	return size;
}
int main(int argc, char *argv[])
{
	char ch;
    FILE *fp;
	FILE *fp2;
	long size,i;
    if ((fp = fopen(argv[1], "rb")) == NULL)
    {
        printf("Не удается открыть %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
	fp2=fopen(argv[2], "wb");
	for(size=filesize(fp),i=0; i<size; i++)
	{
		ch = getc(fp);
        fprintf(fp2,"%c",ch);
	}
    fclose(fp);
	fclose(fp2);
    return 0;
}