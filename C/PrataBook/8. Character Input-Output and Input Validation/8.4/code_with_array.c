/*Напишите программу, которая читает ввод как поток символов, пока не встретит EOF. Программа должна сообщать среднее количество букв в словах. Не считайте пробельные символы в словах буквами. На самом деле также не должны учитываться и знаки препинания, но в данном упражнении об этом можно не беспокоиться. (Для учета знаков препинания можно воспользоваться функцией ispunct() из семейства ctype.h.)*/
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	int letters=0;
	int char_number=0;
	int j,i=0;
	int letters_count[1000];
	int average=0;
	char ch;
	while(scanf("%c",&ch)!=EOF)
	{
		if(ch==' ')
		{
			if (i==0)
				letters_count[i]=char_number;
			else
				letters_count[i]=char_number-letters_count[i-1]-1;
			char_number=letters_count[i];
			i++;
		}
		if(ispunct(ch)==0)
			char_number++;
	}
	printf("%d\n",char_number);
	letters_count[i]=char_number-letters_count[i-1]-1;
	for(j=0; j<=i; j++)
	{
		printf("%d  ",letters_count[j]);
		average+=letters_count[j];
	}
	printf("Среднее количество символов в словах: %d",average);
	return 0;	
}