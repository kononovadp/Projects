/*Модифицируйте код в листинге 14.14 так, чтобы каждая запись читалась из файла и отображалась, чтобы была возможность удалить запись, и можно было изменить ее содержимое. Если вы удаляете запись, используйте освободившуюся позицию массива для чтения следующей записи. Чтобы разрешить изменение существующего содержимого, вместо режима "a+b" необходимо применять "r+b" и уделять больше внимания установке указателя в файле, не допуская перезаписывание существующих записей добавляемыми записями. Проще всего внести все изменения в данные, хранящиеся в памяти, и затем записать всю финальную информацию в файл. Один из возможных подходов к отслеживанию изменений предполагает добавление в структуру каталога члена, который указывает, должен ли он быть удален.*/
/* booksave.c -- сохранение содержимого структуры в файле */
#include<io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 10               /* максимальное количество книг */
struct book {                   /* определение шаблона book */
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
        find = strchr(st, '\n');    // поиск новой строки
        if (find)                   // если адрес не равен NULL,
            *find = '\0';           // поместить туда нулевой символ
        else
            while (getchar() != '\n')
                continue;           // отбросить остаток строки
    }
    return ret_val;
}
int show_library(struct book *library)
{
	int count = 0;
    int index, filecount;
	filecount = count;
    FILE * pbooks;
    int size = sizeof (struct book);
    if ((pbooks = fopen("book.dat", "rb")) == NULL)
    {
        fputs("Не удается открыть файл book.dat\n",stderr);
        exit(1);
    }
    rewind(pbooks);             /* переход в начало файла */
    while (count < MAXBKS && fread(&library[count],size,1,pbooks)==1)
    {
        if (count == 0)
            puts("Текущее содержимое файла book.dat:");
        printf("%s авторства %s: $%.2f\n",library[count].title,
               library[count].author, library[count].value);
        count++;
    }
	fclose(pbooks);
	return count;
}
void add_book(struct book *library, int count)
{
	FILE *pbooks=fopen("book.dat", "a+b");
	int filecount=count;
	int size = sizeof (struct book);
	if (count == MAXBKS)
    {
        fputs("Файл book.dat заполнен.", stderr);
        return;
    }
    puts("Введите названия новых книг.");
    puts("Нажмите [enter] в начале строки, чтобы закончить ввод.");
    while (count < MAXBKS && s_gets(library[count].title, MAXTITL) != NULL
           && library[count].title[0] != '\0')
    {
        puts("Теперь введите имя автора.");
        s_gets(library[count].author, MAXAUTL);
        puts("Теперь введите цену книги.");
        scanf("%f", &library[count++].value);
        while (getchar() != '\n')
            continue;           /* очистить входную строку */
        if (count < MAXBKS)
            puts("Введите название следующей книги.");
    }
    if (count > 0)
    {
        puts("Каталог ваших книг:");
        for (int index = 0; index < count; index++)
            printf("%s авторства %s: $%.2f\n",library[index].title,
                   library[index].author, library[index].value);
        fwrite(&library[filecount], size, count - filecount,
                   pbooks);
    }
    else
        puts("Вообще нет книг? Очень плохо.\n");
    fclose(pbooks);
}
void change_book(void)
{
	FILE *pbooks=fopen("book.dat", "r+b");
	struct book lib;
	size_t read_result,size=sizeof(struct book);
	fpos_t pos;
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
	printf("Название книги, данные о которой нужно изменить: ");
	gets(title);
	rewind(pbooks);
	fgetpos(pbooks,&pos);
	read_result=fread(&lib,size,1,pbooks);
	while((read_result==1)&&(strcmp(lib.title,title))!=0)
	{
		fgetpos(pbooks,&pos);
		read_result=fread(&lib,size,1,pbooks);
	}
	if(strcmp(lib.title,title)!=0)
	{
		printf("Такой книги нет.\n");
		return;
	}
	printf("Введите новые данные или пустую строку, чтобы оставить предыдущую информацию.\nНовое название книги: ");
	gets(title);
	if(strlen(title)>0)
		strcpy(lib.title,title);
	printf("Новый автор книги: ");
	gets(author);
	if(strlen(author)>0)
		strcpy(lib.author,author);
	printf("Новая цена книги: ");
	scanf("%f",&value);
	if(value>0)
		lib.value=value;
	fsetpos(pbooks,&pos);
	fwrite(&lib,1,size,pbooks);
	fclose(pbooks);
}
void remove_book(void)
{
	FILE *pbooks=fopen("book.dat", "r+b");	
	fpos_t pos1,pos2;
	int i=0;
	struct book lib,lib_arr[10];	
	size_t read_result,size = sizeof(struct book);
	char title[MAXTITL];
	printf("Название книги, данные о которой нужно удалить: ");
	gets(title);
	rewind(pbooks);
	fgetpos(pbooks,&pos1);
	read_result=fread(&lib,size,1,pbooks);
	while((read_result==1)&&(strcmp(lib.title,title))!=0)
	{
		fgetpos(pbooks,&pos1);
		read_result=fread(&lib,size,1,pbooks);
	}
	if(strcmp(lib.title,title)!=0)
	{
		printf("Такой книги нет.\n");
		return;
	}
	while(fread(&lib,size,1,pbooks)==1)
	{
		fgetpos(pbooks,&pos2);
		fsetpos(pbooks,&pos1);
		fwrite(&lib,size,1,pbooks);
		fgetpos(pbooks,&pos1);
		fsetpos(pbooks,&pos2);
	}
	int handle=_fileno(pbooks);
	long filesize=_filelength(handle);
	_chsize(handle,filesize-size);
	fclose(pbooks);
}
int main(void)
{
    struct book library[MAXBKS];
	int count=0;
	char ch;	
	printf("1. Добавить книгу; 2. Удалить книгу;\n3. Изменить книгу; "
	       "4. Вывести информацию обо всех книгах; 5. Выйти из программы\n"
	       "Выбранное действие: ");
	ch=_getche();
	while(ch!='5')
	{		
		putchar('\n');
		switch(ch)
		{			
			case '1': add_book(library,count); break;
			case '2': remove_book(); break;
			case '3': change_book(); break;
			case '4': show_library(library); break;	
			case '5': break;
			default: printf("\nВыберите корректное действие\n"); break;
		}
		if (ch!='\n')
			printf("*****************************************************************\n"
			"1. Добавить книгу; 2. Удалить книгу;\n3. Изменить книгу; "
	        "4. Вывести информацию обо всех книгах; 5. Выйти из программы\n"
	        "Выбранное действие: ");	
		ch=_getche();
	}
    return 0;
}