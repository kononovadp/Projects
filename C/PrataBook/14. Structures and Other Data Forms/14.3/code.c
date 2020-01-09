/*Измените программу из листинга 14.2, чтобы она сначала выводила описания книг в том порядке, в каком они вводились, затем в алфавитном порядке по названиям и, наконец, в порядке возрастания цены.*/
/* manybook.c -- каталог для нескольких книг */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100                /* максимальное количество книг */
struct book {                     /* установка шаблона book       */
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
};
char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n'); // поиск новой строки
        if (find)                // если адрес не равен NULL,
            *find = '\0';        // поместить туда нулевой символ
        else
            while (getchar() != '\n')
                continue;        // отбросить остаток строки
    }
    return ret_val;
}
void show_struct(int count,struct book *library)
{
	if (count > 0)
    {
        printf("Каталог ваших книг:\n");
        for (int index = 0; index < count; index++)
            printf("%s авторства %s: $%.2f\n", library[index].title,
                library[index].author, library[index].value);
    }
    else
        printf("Вообще нет книг? Очень плохо.\n");
}
void sort_struct_title(struct book *lib,int count)
{
	char temp[MAXTITL];
	bool b=false;
	int i;
	while(b==false)
	{
		b=true;		
		for(i=0; i<count-1; i++)
			if((strcmp(lib[i].title,lib[i+1].title))>0)
			{
				strcpy(temp,lib[i].title);
				strcpy(lib[i].title,lib[i+1].title);
				strcpy(lib[i+1].title,temp);
				b=false;
			}
	}			
}
void sort_struct_value(struct book *lib,int count)
{
	int temp;
	bool b=false;
	int i;
	while(b==false)
	{
		b=true;		
		for(i=0; i<count-1; i++)
			if(lib[i].value>lib[i+1].value)
			{
				temp=lib[i].value;
				lib[i].value=lib[i+1].value;
				lib[i+1].value=temp;
				b=false;
			}
	}			
}
int main(void)
{
    struct book library[MAXBKS];  /* массив структур типа book    */
    int count = 0;
    int index;

    printf("Введите название книги.\n");
    printf("Нажмите [enter] в начале строки, чтобы закончить ввод.\n");
    while (count < MAXBKS && s_gets(library[count].title, MAXTITL) != NULL
           && library[count].title[0] != '\0')
    {
        printf("Теперь введите ФИО автора.\n");
        s_gets(library[count].author, MAXAUTL);
        printf("Теперь введите цену.\n");
        scanf("%f", &library[count++].value);
        while (getchar() != '\n')
            continue;          /* очистить входную строку */
        if (count < MAXBKS)
            printf("Введите название следующей книги.\n");		
    }
    show_struct(count,library);
	sort_struct_title(library,count);
	printf("----------Отсортировано по названиям----------\n");
	show_struct(count,library);
	sort_struct_value(library,count);
	printf("----------Отсортировано по цене----------\n");
	show_struct(count,library);
    return 0;
}