/*Напишите программу, которая читает входные данные до тех пор, пока не встретится EOF, и выводит количество слов, количество прописных букв, количество строчных букв, количество знаков препинания и количество цифр. Используйте семейство функций ctype.h.*/
#include <stdio.h>
#include <ctype.h>
#define STRINGS_SIZE 100
#define STRINGS_NUMBER 100
void different_symbols_count(char s[], int *words, int *uppercase_letters,
int *small_letters, int	*punctuation_symbols, int *numbers)
{
	int i;	
	for(i=0; i<strlen(s); i++)
		if(isupper(s[i]))
			++*uppercase_letters;
		else
			if(islower(s[i]))
				++*small_letters;
			else
				if(ispunct(s[i]))
					++*punctuation_symbols;
				else
					if(isdigit(s[i]))
						++*numbers;
	for(i=0; i<strlen(s); i++)
	{
		while(s[i]!=' ')
			i++;			
		++*words;		
		while(s[i]==' ')
			i++;
	}
}
int main(void)
{
	int words=0;
	int uppercase_letters=0;
	int small_letters=0;
	int punctuation_symbols=0;
	int numbers=0;
	int i,j;
	char s[STRINGS_SIZE][STRINGS_NUMBER];
	for(i=0; i<STRINGS_NUMBER; i++)
	{		
		fgets(s[i],STRINGS_SIZE,stdin);
		if(s[i][0]=='\0')
			break;
		for(j=0; j<strlen(s[i]); j++)
			if(s[i][j]=='\n')
				s[i][j]='\0';
		printf("%s\n",s[i]);
		different_symbols_count(s[i],&words,&uppercase_letters,&small_letters,
		&punctuation_symbols,&numbers);
	}
	printf("-----------------------------------------------------------------\n");
	printf("Количество слов: %d\nКоличество прописных букв: %d\n"
	"Количество строчных букв: %d\nКоличество знаков препинания: %d\n"
	"Количество цифр: %d",words,uppercase_letters,small_letters,punctuation_symbols,
	numbers);
    return 0;
}