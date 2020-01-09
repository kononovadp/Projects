/*Напишите и протестируйте в цикле функцию, которая возвращает количество ее вызовов.*/
#include <stdio.h>
int func()
{
	static int count;
	count++;
	return count;
}
int main(void)
{
    int i;
	for (i=0; i<5; i=func()) {}
	printf("%d\n",i);
	return 0;
}
