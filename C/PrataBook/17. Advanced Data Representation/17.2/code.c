/*Предположим, что в файле list.h (листинг 17.3) используется следующее определение списка:
typedef struct list
{
	Node *head;
	Node *end;
}List;
Перепишите функции в файле list.c (листинг 17.5), чтобы они соответствовали этому определению, и протестируйте результирующий код с помощью программы filme3.c (листинг 17.4).*/
// films3.c -- использование связного списка в стиле ADT 
// компилировать вместе с list.c                         
#include <stdio.h>
#include <stdlib.h>    // прототип для exit()    
#include <string.h>
#include "list.c"      // определение List, Item 
void showmovies(Item item)
{
    printf("Фильм: %s  Рейтинг: %d\n", item.title,
            item.rating);  
}
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
int main(void)
{
    List movies;
    Item temp;
    // инициализация 
    InitializeList(&movies);
    if (ListIsFull(&movies))
    {
        fprintf(stderr, "Доступная память отсутствует! Программа завершена.\n");
        exit(1);
    }
    // сбор и сохранение информации 
    puts("Введите название первого фильма:");
    while (s_gets(temp.title, TSIZE) != NULL && temp.title[0] != '\0')
    {
        puts("Введите свое значение рейтинга <0-10>:");
        scanf("%d", &temp.rating);
        while(getchar() != '\n')
            continue;
        if (AddItem(temp, &movies)==false)
        {
            fprintf(stderr, "Проблема с выделением памяти\n");
            break;
        }
        if (ListIsFull(&movies))
        {
            puts("Список полон.");
            break;
        }
        puts("Введите название следующего фильма (или пустую строку для прекращения ввода):");
    }
    // отображение 
    if (ListIsEmpty(&movies))
        printf("Данные не введены.");
    else
    {
        printf("Список фильмов:\n");
        Traverse(&movies, showmovies);
    }
    printf("Вы ввели %d фильмов.\n", ListItemCount(&movies));
    // очистка 
    EmptyTheList(&movies);
	printf("---------Список фильмов после удаления:---------\n");
	Traverse(&movies, showmovies);
    printf("Программа завершена.\n");

    return 0;
}
