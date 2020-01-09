/*Модифицируйте программу в листинге 13.3, стобы каждое слово было пронумеровано в соответствии с порядком его добавления в список, начиная с 1. Позаботьтесь о том, чтобы при втором запуске программы новая нумерация слов начиналась с того места, где была закончена нумерация при предыдущем запуске.*/
/* addaword.c -- использование fprintf(), fscanf() и rewind() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 41

int main(void)
{
    FILE *fp;
    char words[MAX];
	int number=0;
    if ((fp = fopen("wordy.txt", "a+")) == NULL)
    {
        fprintf(stdout, "Не удается открыть файл \"wordy.txt\".\n");
        exit(EXIT_FAILURE);
    }
	while(fscanf(fp,"%s",words) == 1)
		number++;
	rewind(fp);
    puts("Введите слова для добавления в файл; для завершения");
    puts("введите символ # в начале строки.");
    while ((fscanf(stdin,"%40s", words) == 1)  && (words[0] != '#'))
	{
        number++;
		fprintf(fp, "%d.%s\n",number,words);
		
	}
    puts("Содержимое файла:");
    rewind(fp);           /* возврат в начало файла */
    while (fscanf(fp,"%s",words) == 1)
		puts(words);
    puts("Готово!");
    if (fclose(fp) != 0)
        fprintf(stderr, "Ошибка при закрытии файла\n");

    return 0;
}
