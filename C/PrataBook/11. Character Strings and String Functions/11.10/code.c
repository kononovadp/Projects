/*Напишите функцию, которая принимает строку в качестве аргумента и удаляет из нее все пробелы. Протестируйте эту функцию в программе, которая использует цикл для чтения строк до тех пор, пока не будет введена пустая строка. Программа должна применять эту функцию к каждой входной строке и отображать результат.*/
#include <stdio.h>
#define S1_SIZE 100
void delete_char(char s[], int position, int count)
{
	int i,j;
	for(i=0; i<count; i++)
		for(j=position; j<strlen(s); j++)
			s[j]=s[j+1];
}
void delete_spaces(char s[])
{
	int i,j,n;
	for(i=0; i<strlen(s); i++)
	{
		if(s[i]==' ')
		{
			j=i;
			n=0;
			while(s[j]==' ')
			{
				j++;
				n++;
			}
			delete_char(s,i,n);
		}
	}
}
int main(void)
{
    char s1[S1_SIZE];
	printf("Строка 1: ");
	fgets(s1,S1_SIZE,stdin);
	s1[strlen(s1)-1]='\0';	
	while(s1[0]!='\0')
	{		
		delete_spaces(s1);
		printf("Строка без пробелов: %s",s1);
		printf("\nСтрока 1: ");
		fgets(s1,S1_SIZE,stdin);
		s1[strlen(s1)-1]='\0';		
	}
    return 0;
}