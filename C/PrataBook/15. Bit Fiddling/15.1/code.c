/*Напишите функцию, которая преобразует строку с двоичным представлением в числовое значение. Другими словами, если есть char *pbin="01001001", то переменную pbin можно передать этой функции в качестве аргумента, и функция должна возвратить значение 73 типа int.*/
#include <stdio.h>
int bintodec(char *bin)
{
	int n=0;
	int i;
	int power=strlen(bin)-1;
	for(i=0; i<strlen(bin); i++,power--)
		n+=bin[i]-'0'<<power;
	return n;
}
int main(void)
{
	char *pbin="01001001";
	printf("string %s in binary system = %d in decimal system",pbin,bintodec(pbin));
    return 0;
}