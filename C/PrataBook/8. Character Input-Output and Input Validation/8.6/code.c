/*������������� ������� get_first() �� �������� 8.8 ���, ����� ��� ���������� ������ ��������� ������������ ������. ������������� �� � �����-������ ������� ���������.*/
#include <stdio.h>
char get_first(void)
{
	int ch;
	while((ch=getchar())==' ')
		continue;
	return ch;
}
int main(void)
{
	printf("�������: ");
	printf("������ ��������� ������������ ������: %c",get_first());
	return 0;
}