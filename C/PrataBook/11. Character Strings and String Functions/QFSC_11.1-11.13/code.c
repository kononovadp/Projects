/*1. Нет символа конца строки ('\0'), это массив символов, а не строка.
2: Увидимся завтра в кафе.
видимся завтра в кафе.
Увидимс
идимс
3: о
но
сно
усно
кусно
Вкусно
4: За всю дорогу я смог осилить лишь часть.
5. а. Хо Хо Хо!оХ оХ оХ
5. б. char *x;
5. в. адресное значение;
5. г. *--pc - переход на предыдущий элемент, --*pc - уменьшить целочисленное значение символа по адресу pc;
5. д. Хо Хо Хо!!оХ оХ о
5. е. -
5. ж. аварийное завершение при попытке вывести несуществующий элемент.
6. Переменная sign и значение '$' 1 байт, значение "$" - 2 байта.
7. How are ya, sweetie? How are ya, sweetie? 
Beat the clock.
eat the clock.
Beat the clock. Win a toy.
Beat
chat
hat
at
t
t
at
How are ya, sweetie? 
8. faavrhee
*le*on*sm
9-12:
#include <stdio.h>
#include <string.h>
char *s_gets(char *st, int n)
{
	char *ret_val, *p;
	ret_val=fgets(st,n,stdin);
	p=ret_val;
	if(ret_val)
	{
		while(*p!='\n' && *p!='\0')
			p++;
		if(*p=='\n')
			*p='\0';
		else
			while(getchar()!='\n')
				continue;
	}
	return ret_val;
}
int my_strlen(char *s)
{
	int n=0;
	while(s[n]!='\0')
		n++;
	return n;
}
char *s_gets_strchr(char *st, int n)
{
	char *ret_val;
	ret_val=fgets(st,n,stdin);
	if(ret_val)
	{
		ret_val=strchr(st,'\n');
		if(*ret_val=='\n')
			*ret_val='\0';
		else
			while(getchar()!='\n')
				continue;
	}
	return ret_val-strlen(st);
}
char *find_space(char *s)
{
	while(s!=NULL)
		if(*s==' ')
			return s;
		else
			s++;
	return NULL;
}
	
int main(int n, char *arr[])
{
    char s[100];
	printf("Input string: ");
	char *p=s_gets_strchr(s,100);
	char *sp=find_space(s);
	printf("Output string: |%s| Length: %d\nOutput from space: |%s|",p,my_strlen(p),sp);
	return 0;
}*/
/* 13: compare.c -- эта программа будет работать */
#include <stdio.h>
#include <string.h>  // объявление strcmp()
#define SIZE 40
#define ANSWER "Grant"
char * s_gets(char * st, int n)
{
    char * ret_val;
    int i = 0;
    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else  // требуется наличие words[i] == '\0'
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}
int my_strcmp(char *s1, char *s2)
{
	if(strlen(s1)!=strlen(s2))
		return 1;
	while(*s1)
	{
		if(tolower(*s1)!=tolower(*s2))
			return 1;
		s1++;
		s2++;
	}
	return 0;
}
int main(void)
{	
	char try[SIZE];
    puts("Кто похоронен в могиле Гранта?");
    s_gets(try, SIZE);
    while (my_strcmp(try,ANSWER) != 0)
    {
        puts("Неправильно! Попытайтесь еще раз.");
        s_gets(try, SIZE);
    }
    puts("Теперь правильно!");
    return 0;
}
