/*�������� ���������, ������� ����������� ����� � ������� � ���� � ������. ��� �������� 60 �������� ������������� ��������� ����������� #define ��� const. ����������� ���� while, ����� ���������� ������������ ����������� ���������� ����� �������� � ��� ����������� �����, ���� �������� �������� �������, ������� ��� ������ ����.*/
#include <stdio.h>
#define min_in_hour 60
int main(void)
{
	int minute=1;
	printf("���������� ����� (<=0 - �����): ");
	scanf("%d",&minute);
	while(minute>0)
	{		
		printf("��� ���������� %d ����� � %d �����",minute/min_in_hour, minute%min_in_hour);
		printf("\n���������� ����� (<=0 - �����): ");
		scanf("%d",&minute);
	}
	printf("��������� ���������");
	getchar();
	getchar();
}
 