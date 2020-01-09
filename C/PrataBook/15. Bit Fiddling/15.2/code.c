/*Напишите функцию, которая читает две строки с двоичным представлением как аргументы командной строки и выводит результаты применения операции ~ к каждому числу, а также результаты применения операций &, | и ^ к паре чисел. Отобразите результаты в виде двоичных строк. Если командная строка недоступна, обеспечьте в программе интерактивный ввод строк.*/
#include <stdio.h>
#include <string.h>
void equalize_string(char *s1, char *s2)
{
	int i,j,zero_count;
	if(strlen(s1)>strlen(s2))
	{
		zero_count=strlen(s1)-strlen(s2);
		for(j=0; j<zero_count; j++)
		{
			for(i=strlen(s2); i>-1; i--)
				s2[i+1]=s2[i];
			s2[0]='0';
		}
	}
	else
		if (strlen(s2)>strlen(s1))
		{
			zero_count=strlen(s2)-strlen(s1);
			for(j=0; j<zero_count; j++)
			{
				for(i=strlen(s1); i>-1; i--)
					s1[i+1]=s1[i];
				s1[0]='0';
			}
		}
		else
			return;	
}
char *operation_not(char *number)
{
    char *s=(char*)malloc(strlen(number)*sizeof(char));
	for(int i=0; i<strlen(number); i++)
		s[i]='0'+(number[i]-'0'^1);
	s[strlen(number)]='\0';	
	return s;
}
char *operation_and(char *n1,char *n2)
{
	char *s=(char*)malloc(strlen(n1)*sizeof(char));
	for(int i=0; i<strlen(n1); i++)
		s[i]='0'+((n1[i]-'0') & (n2[i]-'0'));
	s[strlen(n1)]='\0';
	return s;
}
char *operation_or(char *n1,char *n2)
{
    char *s=(char*)malloc(strlen(n1)*sizeof(char));
	for(int i=0; i<strlen(n1); i++)
		s[i]='0'+((n1[i]-'0') | (n2[i]-'0'));
	s[strlen(n1)]='\0';
	return s;
}
char *operation_xor(char *n1,char *n2)
{
    char *s=(char*)malloc(strlen(n1)*sizeof(char));
	strcpy(s,"");
	for(int i=0; i<strlen(n1); i++)
		s[i]='0'+((n1[i]-'0') ^ (n2[i]-'0'));
	s[strlen(n1)]='\0';
	return s;
}
int main(void)
{
	int i;
	char s1[40]="1001001";
	char s2[40]="10101";
	printf("Source operands: %s %s\n",s1,s2);
	printf("Operation ~:     %s %s\n",operation_not(s1),operation_not(s2));
	equalize_string(s1,s2);
	printf("%s and %s = %s\n",s1,s2,operation_and(s1,s2));
	printf("%s or %s = %s\n",s1,s2,operation_or(s1,s2));
	printf("%s xor %s = %s\n",s1,s2,operation_xor(s1,s2));
    return 0;
}