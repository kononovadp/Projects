/*Модифицируйте и протестируйте функцию из упражнения 1, обеспечив в ней прекращение ввода после n символов либо при достижении первого символа пробела, табуляции или новой строки, в зависимости от того, что произойдет раньше. (Не ограничивайтесь только использованием scanf().) */
#include <stdio.h>
void add_inf_to_array(int n, char arr[])
{
	int i=0;
	printf("Enter symbols: ");	
	fgets(arr,n,stdin);	
	while(arr[i]!=' ' && arr[i]!='\n' && arr[i]!='	' && i!=n)
		i++;
	arr[i]='\0';
}
void showstr(int n, char arr[n])
{
	char *p=arr;
	while(*p!='\0')
		p++;
	for(; arr<p; arr++)
		putchar(*arr);
}
int main(void)
{
    int n=10;
	char arr[n];
	add_inf_to_array(n, arr);
	showstr(n,arr);
    return 0;
}