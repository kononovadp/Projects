/*Модифицируйте программу из листинга 13.6, чтобы вместо интерактивного интерфейса она использовала интерфейс командной строки.*/
/* randbin.c -- произвольный доступ, двоичный ввод-вывод */
#include <stdio.h>
#include <stdlib.h>
#include "D:\Projects\C\my_library\user_functions.h"
#define ARSIZE 1000
int main(int argc, char *argv[])
{
    double numbers[ARSIZE];
    double value;
    int i;
    long pos;
    FILE *iofile;
    // создание набора значений double
    for(i = 0; i < ARSIZE; i++)
        numbers[i] = 100.0 * i + 1.0 / (i + 1);
    // попытка открыть файл
    if ((iofile = fopen(argv[2], "wb")) == NULL)
    {
        fprintf(stderr, "Не удается открыть файл %s для вывода.\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    // запись в файл массива в двоичном формате
    fwrite(numbers, sizeof (double), ARSIZE, iofile);
    fclose(iofile);
    if ((iofile = fopen(argv[2], "rb")) == NULL)
    {
        fprintf(stderr,
                "Не удается открыть файл %s для произвольного доступа.\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    // чтение избранных элементов из файла
	i=strtoint(argv[1]);
    pos = (long) i * sizeof(double); // вычисление смещения
    fseek(iofile, pos, SEEK_SET);    // переход в нужную позицию
    fread(&value, sizeof (double), 1, iofile);
    printf("По индексу %d находится значение %f.\n", i, value);
    fclose(iofile);
    puts("Программа завершена.");
    return 0;
}
