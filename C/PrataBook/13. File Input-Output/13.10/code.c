/*�������� ���������, ����������� ��������� ����, ��� �������� ���������� ������������. ����������� ����, ������� ���������� ������������ ������ ������� � �����. ����� ��������� ������ ������� ����� �����, ������� � ���� ������� � ���������� ��������� �������� ����� ������. ���� ����� ������ ����������� ��� ����� �������������� ��� ����������� ��������.*/
#include <stdio.h>
#include <stdlib.h>
long int filesize(FILE *fp)
{
	fseek (fp, 0, SEEK_END);
	long int size=ftell(fp);
	fseek (fp, 0, SEEK_SET);
	return size;
}
int main(void)
{
    FILE *f;
	char file_name[40];
	printf("��� �����: ");
	scanf("%s",&file_name);
	if((f=fopen(file_name,"r"))==NULL)
	{
		printf("���������� ������� ����.");
		exit(EXIT_FAILURE);
	}
	int n,ch,file_size=filesize(f);
	printf("������� � �����: ");	
	while((scanf("%d",&n))==1 && n>=0)
	{
		if(n>=file_size)
			printf("���� �� ��������� �����.");
		else
		{
			fseek(f,n,SEEK_SET);
			while((ch=getc(f))!='\n' && ch!=EOF)
			putchar(ch);
		}
		printf("\n������� � �����: ");
	}
	fclose(f);	
    return 0;
}
