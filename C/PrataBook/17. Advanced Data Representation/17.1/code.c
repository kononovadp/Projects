/*Модифицируйте код в листинге 17.2 так, чтобы он отображал список фильмов как в исходном, так и в обратном порядке. Один из возможных подходов предусматривает изменение определения связного списка для обеспечения обхода списка в обоих направлениях. Другой подход заключается в применении рекурсии.*/
/* films2.c -- использование связного списка структур */
#include <stdio.h>
#include <stdlib.h>      /* содержит прототип функции malloc()   */
#include <string.h>      /* содержит прототип функции strcpy()   */
#define TSIZE    45      /* размер массива для хранения названия */

struct film {
    char title[TSIZE];
    int rating;
    struct film * next;  /* указывает на следующую структуру в списке */
};
char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');   // поиск новой строки
        if (find)                  // если адрес не равен NULL,
            *find = '\0';          // поместить туда нулевой символ
        else
            while (getchar() != '\n')
                continue;          // отбросить остаток строки
    }
    return ret_val;
}
void show_backwards(struct film *head, int count)
{
	struct film *current=head;
	for(int i=0; i<count-1; i++)
		current=current->next;
	printf("Фильм: %s  Рейтинг: %d\n",current->title, current->rating);
	if(count>1)
		show_backwards(head, count-1);
}
int main(void)
{
    struct film * head = NULL;
    struct film * prev, * current;
    char input[TSIZE];
	int count=0;
    /* Сбор и сохранение информации */
    puts("Введите название первого фильма:");
    while (s_gets(input, TSIZE) != NULL && input[0] != '\0')
    {
        current = (struct film *) malloc(sizeof(struct film));
        if (head == NULL)       /* первая структура      */
            head = current;
        else                    /* последующие структуры */
            prev->next = current;
        current->next = NULL;
        strcpy(current->title, input);
        puts("Введите свое значение рейтинга <0-10>:");
        scanf("%d", &current->rating);
        while(getchar() != '\n')
            continue;
        puts("Введите название следующего фильма (или пустую строку для прекращения ввода):");
        prev = current;
		count++;
    }

    /* Отображение списка фильмов */
    if (head == NULL)
	{
        printf("Данные не введены.");
		return 0;
	}
    else
        printf("Список фильмов в прямом порядке:\n");
    current = head;
    while (current != NULL)
    {
        printf("Фильм: %s  Рейтинг: %d\n",
               current->title, current->rating);
        current = current->next;
    }
	printf("----------------Список фильмов в обратном порядке---------:\n");
	show_backwards(head,count);
    /* Программа выполнена, поэтому можно освободить память */
    current = head;
    while (head != NULL)
    {
        current = head;
        head = current->next;
        free(current);
    }
    printf("Программа завершена.\n");

    return 0;
}