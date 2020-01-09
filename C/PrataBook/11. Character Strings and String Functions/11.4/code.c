/*Разработайте и протестируйте функцию, подобную описанной в упражнении 3, за исключением того, что она принимает второй параметр, указывающий максимальное количество символов, которые могут быть прочитаны.*/
#include <stdio.h>
void add_inf_to_array(int n, char arr[])
{
	printf("Введите символы: ");
	int i=0;
	char ch;
	ch=getchar();
	while(ch!=' ' && ch!='\n' && ch!='	' && i!=n)
	{		
		arr[i]=ch;
		ch=getchar();
		i++;
	}
	arr[i]='\0';
}
void showstr(int n, char arr[n])
{
	char *p;
	while(arr[n]!='\0')
		n--;
	for(p=arr; p<arr+n; p++)
		putchar(*p);
}

int main(void)
{
    int n=10;
	char arr[n];
	add_inf_to_array(n, arr);
	showstr(n,arr);
    return 0;
}