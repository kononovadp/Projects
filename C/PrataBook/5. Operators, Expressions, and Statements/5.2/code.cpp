/*�������� ���������, ������� ����������� � ������������ ���� ������ �����, � ����� ������� ��� ����� �����, ������� � ����� ����� (� ������� ���) � ���������� ������, ������� ������ ���������� �������� �� 10 (������� ���). (�� ����, ���� �������� ����� 5, �� � ������ ������ �������������� ����� �� 5 �� 15). ���������� ���������� ��������� �������� ���� �� ����� ���������, ��������� ��������� ��� ��������� ����� ������.*/
#include <stdio.h>
#define ten 10
int main(void)
{
	int int1,int2;
	printf("������� �����: ");
	scanf("%d",&int1);
	int2=int1+ten+1;
	while(int1<int2)
	{
		printf("%5d",int1);
		int1++;
	}
	getchar();
	getchar();
}
 