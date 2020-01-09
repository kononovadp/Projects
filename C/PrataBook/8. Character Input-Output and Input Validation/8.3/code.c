/*Напишите программу, которая читает ввод как поток символов, пока не встретит EOF. Программа должна сообщать количество прописных букв, количество строчных букв и количество остальных символов во входных данных. Можете предполагать, что числовые значения для строчных букв являются последовательными, и то же самое справедливо для прописных букв. Либо для большей переносимости можете использовать классификационные функции из библиотеки ctype.h.*/
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	int upper_letters=0;
	int small_letters=0;
	int other_symbols=0;	
	char ch;
	while(scanf("%c",&ch)!=EOF)	
	{		
		printf("%c=%d; ",ch,ch);
		if ((ch>=65 && ch<=90)||(ch<=-33 && ch>=-64))//(isupper(ch)==1)
			upper_letters++;
		else
			if((ch>=61 && ch<=122)||(ch<=-1 && ch>=-32))//if (islower(ch)==1)
				small_letters++;
			else
				other_symbols++;
	}
	printf("\nПрописных букв: %d\nСтрочных букв: %d\nОстальных символов: %d",upper_letters,small_letters,other_symbols);
	return 0;	
}