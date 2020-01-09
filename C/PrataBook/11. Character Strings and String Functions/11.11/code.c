/*Напишите программу, которая читает до 10 строк и/или до появления EOF, в зависимости от того, что произойдет раньше. Функция должна предложить пользователю меню с пятью вариантами: вывод исходного списка строк, вывод строк согласно последовательности сопоставления ASCII, вывод строк в порядке возрастания длины, вывод строк в порядке возрастания длины первого слова в строке и выход из программы. Меню должно отображаться до тех пор, пока пользователь не выберет вариант выхода из программы. Программа должна действительно выполнять запрошенные действия.*/
#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#define STRINGS_SIZE 100
#define STRINGS_NUMBER 100
void show_array(char s[][STRINGS_SIZE], short choise)
{	
	switch(choise)
		{			
			case 1: printf("\nИсходный список строк:\n"); break;
			case 2: printf("\nСтроки согласно последовательности сопоставления ASCII:\n"); break;
			case 3: printf("\nСтроки в порядке возрастания длины:\n"); break;
			case 4: printf("\nСтроки в порядке возрастания длины первого слова:\n"); break;
		}
	printf("-----------------------------------------------------------------\n");	        
	int i=0;
	while(i<STRINGS_NUMBER && s[i][0]!='\0')
	{
		printf("%s\n",s[i]);
		i++;
	}
}
void sort_strings_length(char s[][STRINGS_SIZE], int str_count)
{
	int i,j;
	char temp[STRINGS_SIZE];
	bool b=true;
	while(b!=false)
	{
		b=false;
		for(i=0; i<str_count; i++)
			for(j=i+1; j<str_count; j++)
				if(strlen(s[i])>strlen(s[j]))
				{
					b=true;
					strcpy(temp,s[i]);
					strcpy(s[i],s[j]);
					strcpy(s[j],temp);
				}
	}
}
void sort_strings_ASCII(char s[][STRINGS_SIZE], int str_count)
{
	int i,j,n;
	char temp[STRINGS_SIZE]={"\0"};
	bool b=true;
	while(b!=false)
	{
		b=false;
		for(i=0; i<str_count; i++)
		{			
			j=0;
			if(strlen(s[i])<strlen(s[i+1]))
				n=strlen(s[i]);
			else
				n=strlen(s[i+1]);
			while(s[i][j]==s[i+1][j] && j<n)
				j++;
			if(s[i][j]>s[i+1][j])
			{
				b=true;
				strcpy(temp,s[i]);
				strcpy(s[i],s[i+1]);
				strcpy(s[i+1],temp);
			}
		}
	}
}
void sort_strings_first_word_length(char s[][STRINGS_SIZE], int str_count)
{
	int i,spaces_i,spaces_j;
	char temp[STRINGS_SIZE]={"\0"};
	bool b=true;
	while(b!=false)
	{
		b=false;
		for(i=0; i<str_count; i++)
		{
			spaces_i=0;
			while(s[i][spaces_i]!=' ' && s[i][spaces_i]!=',' &&	s[i][spaces_i]!='.'
			&& s[i][spaces_i]!='-' && s[i][spaces_i]!='!' && s[i][spaces_i]!='?'
			&& s[i][spaces_i]!=';')
				spaces_i++;
			spaces_j=0;
			while(s[i+1][spaces_j]!=' ' && s[i+1][spaces_j]!=',' &&	s[i+1][spaces_j]!='.'
			&& s[i+1][spaces_j]!='-' && s[i+1][spaces_j]!='!' && s[i+1][spaces_j]!='?'
			&& s[i+1][spaces_j]!=';')
				spaces_j++;
			if(spaces_i>spaces_j)
			{
				b=true;
				strcpy(temp,s[i]);
				strcpy(s[i],s[i+1]);
				strcpy(s[i+1],temp);
			}
		}
	}
}
int initialize_array(char s[STRINGS_NUMBER][STRINGS_SIZE])
{
	char ch;
	int i,j;
	for(i=0; i<STRINGS_NUMBER; i++)
	{		
		fgets(s[i],STRINGS_SIZE,stdin);
		if(s[i][0]=='\0')
			break;
		for(j=0; j<strlen(s[i]); j++)
			if(s[i][j]=='\n')
				s[i][j]='\0';
	}
	return i;
}
void copy_array(char target[][STRINGS_SIZE], char source[][STRINGS_SIZE])
{
	int i=0;
	while(i<STRINGS_NUMBER && source[i][0]!='\0')
	{
		strcpy(target[i],source[i]);
		i++;
	}
}
void menu()
{
	char source[STRINGS_NUMBER][STRINGS_SIZE]={"\0"};
	char working_array[STRINGS_NUMBER][STRINGS_SIZE]={"\0"};
	char ch;
	int count=initialize_array(source);
	printf("1. Вывод исходного списка строк;\n"
	"2. вывод строк согласно последовательности сопоставления ASCII\n"
	"3. вывод строк в порядке возрастания длины\n"
	"4. вывод строк в порядке возрастания длины первого слова в строке\n"
	"5. выход из программы.\n"
	"Выбранное действие: ");	
	ch=_getche();
	while(ch!='5')
	{		
		switch(ch)
		{			
			case '1': show_array(source,1); break;
			case '2': copy_array(working_array,source);	
			sort_strings_ASCII(working_array,count); show_array(working_array,2); break;
			case '3': copy_array(working_array,source);	
			sort_strings_length(working_array,count); show_array(working_array,3); break;case '4': copy_array(working_array,source);	
			sort_strings_first_word_length(working_array,count); 
			show_array(working_array,4); break;
			case '5': break;
			default: printf("\nВыберите корректное действие\n"); break;
		}
		if (ch!='\n')
			printf("*****************************************************************\n"
			"1. Вывод исходного списка строк;\n"
			"2. вывод строк согласно последовательности сопоставления ASCII\n"
			"3. вывод строк в порядке возрастания длины\n"
			"4. вывод строк в порядке возрастания длины первого слова в строке\n"
			"5. выход из программы.\n"
			"Выбранное действие: ");	
		ch=_getche();
	}
}
int main(void)
{
	menu();
    return 0;
}