/*Напишите программу, которая читает символы из стандартного потока ввода вплоть до конца файла. Для каждого символа программа должна сообщать, является ли он буквой. Если символ - буква, программа должна вдобавок сообщить ее порядковый номер в алфавите. Например, буквы с и С будут иметь номер 3. Предусмотрите в программе функцию, которая принимает символ в качестве аргумента и возвращает его порядковый номер в алфавите, если он является буквой и -1 в противном случае.*/
#include <stdio.h>
#include <ctype.h>
int letter_number_in_alphabet(char ch)
{
	if (isalpha(ch))
	{
		if (isupper(ch))
			return ch-'A'+1;
		else
			return ch-'a'+1;
	}
	else
		return -1;
}
int main(void)
{
	char ch;
	int number_in_alphabet;
	printf("Input: ");
	while(scanf("%c",&ch)!=EOF && (ch!='\n'))
	{
		printf("%c - это ",ch);
		number_in_alphabet=letter_number_in_alphabet(ch);
		if (number_in_alphabet>-1)
			printf("буква под номером %d в алфавите\n",number_in_alphabet);
		else
			printf("не буква или буква не английского алфавита\n");
	}
	return 0;
}