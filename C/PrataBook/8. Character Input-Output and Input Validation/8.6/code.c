/*Модифицируйте функцию get_first() из листинга 8.8 так, чтобы она возвращала первый встречный непробельный символ. Протестируйте ее в какой-нибудь простой программе.*/
#include <stdio.h>
char get_first(void)
{
	int ch;
	while((ch=getchar())==' ')
		continue;
	return ch;
}
int main(void)
{
	printf("Символы: ");
	printf("Первый встречный непробельный символ: %c",get_first());
	return 0;
}