/*�������� ���������, ������� ������ ���� ��� ����� ��������, ���� �� �������� EOF. ��������� ������ �������� ������� ���������� ���� � ������. �� �������� ���������� ������� � ������ �������. �� ����� ���� ����� �� ������ ����������� � ����� ����������, �� � ������ ���������� �� ���� ����� �� ������������. (��� ����� ������ ���������� ����� ��������������� �������� ispunct() �� ��������� ctype.h.)*/
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	int letters=0;
	int char_number=0;
	int j,i=0;
	int letters_count[1000];
	int average=0;
	int symbols_count=0;
	char ch;
	while(scanf("%c",&ch)!=EOF)
	{
		if(ch==' ')
		{
			if (i==0)
				symbols_count=char_number;
			else
				symbols_count=char_number-symbols_count-1;
			average+=symbols_count;
			char_number=symbols_count;
			if (symbols_count>0)
			{
				i++;
				printf("����� %d: %d ����\n",i,symbols_count);
			}
		}
		if(ispunct(ch)==0)
			char_number++;
	}
	symbols_count=char_number-symbols_count-1;
	average+=symbols_count;
	printf("����� %d: %d ����\n",i+1,symbols_count);
	printf("������� ���������� ���� � ������: %d",average/(i+1));
	return 0;
}