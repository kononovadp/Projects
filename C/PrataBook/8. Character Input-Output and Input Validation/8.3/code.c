/*�������� ���������, ������� ������ ���� ��� ����� ��������, ���� �� �������� EOF. ��������� ������ �������� ���������� ��������� ����, ���������� �������� ���� � ���������� ��������� �������� �� ������� ������. ������ ������������, ��� �������� �������� ��� �������� ���� �������� �����������������, � �� �� ����� ����������� ��� ��������� ����. ���� ��� ������� ������������� ������ ������������ ����������������� ������� �� ���������� ctype.h.*/
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
	printf("\n��������� ����: %d\n�������� ����: %d\n��������� ��������: %d",upper_letters,small_letters,other_symbols);
	return 0;	
}