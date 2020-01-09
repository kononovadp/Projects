/*Напишите программу копирования файлов, которая предлагает пользователю ввести имя текстового файла, выступающего в роли исходного, и имя выходного файла. Программа должна использовать функцию toupper() из ctype.h для перевода текста в верхний регистр во время его записи в выходной файл. Применяйте стандартный ввод-вывод и текстовый режим.*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main(void)
{
	char source_filename[200],target_filename[200];
	int ch;
    FILE *source_file, *target_file;
	printf("Имя исходного файла: ");
	scanf("%s",&source_filename);
	if((source_file=fopen(source_filename,"r"))==NULL)
	{
		printf("Не удалось найти файл.");
		exit(EXIT_FAILURE);
	}
	printf("Имя целевого файла: ");
	scanf("%s",&target_filename);
	target_file=fopen(target_filename,"w");
	do {
      ch = fgetc (f);
      putchar(ch);
    } while (ch != EOF);
	fclose(source_file);
	fclose(target_file);
    return 0;
}