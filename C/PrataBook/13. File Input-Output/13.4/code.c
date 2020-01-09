/*�������� ���������, ������� ��������������� ���������� �� ������ ���������� ���� ������, ������������� � ��������� ������. ��� ���������� ������ ����������� argc.*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main(int argc, char *argv[])
{
	FILE *f;
	int ch;
	for(int i=1; i<argc; i++)
	{		
		if((f=fopen(argv[i],"r"))==NULL)
		{
			printf("���� %s �� ������.\n",argv[i]);
			continue;
		}
		printf("���������� ����� %s:\n",argv[i]);
		while((ch=getc(f))!=EOF)
			putchar(ch);
		printf("\n---------------------------------------------\n");
	}
	fclose(f);
    return 0;
}