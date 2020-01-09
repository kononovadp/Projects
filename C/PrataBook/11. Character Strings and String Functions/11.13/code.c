/*Напишите программу, которая повторяет на экране аргументы командной строки в обратном порядке. Другими словами, если аргументами командной строки являются до скорого свидания, данная программа должна вывести на экран скорого свидания до.*/
#include <stdio.h>
#include <ctype.h>
#define STRINGS_SIZE 100
#define STRINGS_NUMBER 100

int main(int argc, char *argv[])
{
	int i;
	for(i=argc-1; i>0; i--)
		printf("%s ",argv[i]);
    return 0;
}