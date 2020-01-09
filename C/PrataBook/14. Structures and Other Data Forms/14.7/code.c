/*Модифицируйте код в листинге 14.14 так, чтобы каждая запись читалась из файла и отображалась, чтобы была возможность удалить запись, и можно было изменить ее содержимое. Если вы удаляете запись, используйте освободившуюся позицию массива для чтения следующей записи. Чтобы разрешить изменение существующего содержимого, вместо режима "a+b" необходимо применять "r+b" и уделять больше внимания установке указателя в файле, не допуская перезаписывание существующих записей добавляемыми записями. Проще всего внести все изменения в данные, хранящиеся в памяти, и затем записать всю финальную информацию в файл. Один из возможных подходов к отслеживанию изменений предполагает добавление в структуру каталога члена, который указывает, должен ли он быть удален.*/
/* booksave.c -- сохранение содержимого структуры в файле */
#include<io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 40               /* максимальное количество книг */
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
void show_library(struct book *library, int count)
{
	FILE * pbooks;
    int size = sizeof (struct book);
	struct book current_book;
    if ((pbooks = fopen("book.dat", "rb")) == NULL)
    {
        fputs("Не удается открыть файл book.dat\n",stderr);
        exit(1);
    }	
	puts("===============Содержимое массива:===============");
	for(int i=0; i<count; i++)
		printf("%s авторства %s: $%.2f\n",library[i].title,
               library[i].author, library[i].value);	
	puts("===============Текущее содержимое файла book.dat:===============");
    rewind(pbooks);             /* переход в начало файла */	
	while(fread(&current_book,size,1,pbooks)==1)
		printf("%s авторства %s: $%.2f\n",current_book.title,current_book.author,current_book.value);
	fclose(pbooks);
}
int add_book(struct book *library, int count, int position)
{
	FILE *pbooks=fopen("book.dat", "r+b");
	int i,j,begin_position=position;
	int size = sizeof (struct book);
	struct book new_book,temp;
	fpos_t pos1,pos2;
	int previous_count=count;
	if (count == MAXBKS)
    {
        fputs("Файл book.dat заполнен.", stderr);
        return count;
    }
    puts("Введите названия новых книг.");
    puts("Нажмите [enter] в начале строки, чтобы закончить ввод.");
    while (count < MAXBKS && s_gets(new_book.title, MAXTITL) != NULL && new_book.title[0] != '\0')
    {
        puts("Теперь введите имя автора.");
        s_gets(new_book.author, MAXAUTL);
        puts("Теперь введите цену книги.");
        scanf("%f", &new_book.value);
		for(i=position; i<count+1; i++)
		{
			temp=library[i];
			library[i]=new_book;
			new_book=temp;
		}
        while (getchar() != '\n')
            continue; /* очистить входную строку */
        if (count < MAXBKS)
            puts("Введите название следующей книги.");
		position++;
		count++;
    }
    if(count>0)
    {
		rewind(pbooks);
		for(i=0; i<begin_position+1; i++)
		{
			fgetpos(pbooks,&pos1);
			fread(&temp,size,1,pbooks);
		}		
		for (i = begin_position; i < count; i++)
		{
            fsetpos(pbooks,&pos1);			
			fwrite(&library[i],size,1,pbooks);
			fgetpos(pbooks,&pos1);
		}
		printf("Добавлено в позицию %d\n",begin_position);
    }
    else
        puts("Вообще нет книг? Очень плохо.\n");
	fclose(pbooks);
	return count;    
}
void change_book(struct book *library,int count)
{
	FILE *pbooks=fopen("book.dat", "r+b");
	struct book lib;
	size_t read_result,size=sizeof(struct book);
	fpos_t pos;
	char title[MAXTITL];
	char author[MAXAUTL];
	float value;
	int i=0;
	printf("Название книги, данные о которой нужно изменить: ");
	gets(title);
	rewind(pbooks);
	fgetpos(pbooks,&pos);
	read_result=fread(&lib,size,1,pbooks);
	while((read_result==1)&&(strcmp(lib.title,title))!=0)
	{
		fgetpos(pbooks,&pos);
		read_result=fread(&lib,size,1,pbooks);
		i++;
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
	strcpy(library[i].title,lib.title);
	strcpy(library[i].author,lib.author);
	library[i].value=lib.value;
}
int remove_book(struct book *library, int *count)
{
	FILE *pbooks=fopen("book.dat", "r+b");	
	fpos_t pos1,pos2;
	int current_position=0;
	struct book lib;	
	size_t read_result,size = sizeof(struct book);
	char title[MAXTITL];
	printf("Название книги, данные о которой нужно удалить: ");
	gets(title);	
	while(current_position<*count && strcmp(library[current_position].title,title)!=0)
		current_position++;
	if(strcmp(library[current_position].title,title)!=0)
	{
		printf("Такой книги нет.\n");
		return *count;
	}
	for(int i=current_position; i<*count; i++)
		library[i]=library[i+1];
	*count-=1;	
	printf("Книга удалена в позиции %d\n",current_position);	
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
		return *count;
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
	return current_position;
}
int main(void)
{
	int count=0;
	int position=0;
	struct book library[MAXBKS];
	FILE *pbooks;
	if ((pbooks = fopen("book.dat", "rb")) == NULL)
	{
		pbooks = fopen("book.dat", "wb");
		fclose(pbooks);
	}
	pbooks = fopen("book.dat", "rb");
	size_t size = sizeof(struct book);
	char ch;
	rewind(pbooks);
	while(fread(&library[count],size,1,pbooks)==1)
		count++;
	position=count;
	fclose(pbooks);
	printf("1. Добавить книгу; 2. Удалить книгу;\n3. Изменить книгу; "
	       "4. Вывести информацию обо всех книгах; 5. Выйти из программы\n"
	       "Выбранное действие: ");
	ch=_getche();
	while(ch!='5')
	{		
		putchar('\n');
		switch(ch)
		{			
			case '1': count=add_book(library,count,position); break;
			case '2': position=remove_book(library,&count); break;
			case '3': change_book(library,count); break;
			case '4': show_library(library,count); break;	
			case '5': break;
			default: printf("Выберите корректное действие\n"); break;
		}
		if (ch!='\n')
			printf("*******************************************************************************\n"
			"1. Добавить книгу; 2. Удалить книгу;\n3. Изменить книгу; "
	        "4. Вывести информацию обо всех книгах; 5. Выйти из программы\n"
	        "Выбранное действие: ");	
		ch=_getche();
	}
    return 0;
}