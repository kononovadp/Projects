/*�������� ���������, ������� ������������ ���������� �������� �� ������� ������ �� ���������� ����� �����.*/
#include <stdio.h>
int main(void)
{
	int symbol_count=0;
	char ch;
	while(ch=getchar()!=EOF)
		symbol_count++;
	printf("���������� �������� � ��������� �����: %d",symbol_count);
	return 0;	
}