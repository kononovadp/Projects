/*Модифицируйте программу в листинге 13.1, чтобы она предлагала пользователю ввести имя файла и читала его ответ вместо использования аргументов командной строки.*/
#include <stdio.h>
#include <stdlib.h> // прототип exit()

int main(void)
{
    int ch;         // место для хранения каждого символа по мере чтения
    FILE *fp;       // "указатель файла"
	char filename[100];
    unsigned long count = 0;
	printf("Ведите имя файла: ");
	scanf("%s",&filename);
    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("Не удается открыть %s\n", filename);
        exit(EXIT_FAILURE);
    }
    while ((ch = getc(fp)) != EOF)
    {
        putc(ch,stdout);  // то же, что и putchar(ch);
        count++;
    }
    fclose(fp);
    printf("\nФайл %s содержит %lu символов\n", filename, count);

    return 0;
}