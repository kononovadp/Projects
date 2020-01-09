/*Разработайте и протестируйте функцию, которая читает первое слово из строки ввода в массив и отбрасывает остальную часть строки. Функция должна пропускать ведущие пробельные символы. Определите слово как последовательность символов, не содержащую символа пробела, табуляции или новой строки. Используйте функцию getchar(), а не scanf().*/
#include <stdio.h>
void add_inf_to_array(int n, char arr[])
{
	printf("Введите символы: ");
	int i=0;
	char ch;
	ch=getchar();
	while(ch!=' ' && ch!='\n' && ch!='	' && i<n)
	{		
		arr[i]=ch;
		ch=getchar();
		i++;
	}
	arr[i]='\0';
}
void showstr(int n, char arr[])
{
	char *p=arr;
	while(*p!='\0')
	{
		putchar(*p);
		p++;
	}
}
int main(void)
{
    int n=10;
	char arr[n];
	add_inf_to_array(n,arr);
	showstr(n,arr);
    return 0;
}