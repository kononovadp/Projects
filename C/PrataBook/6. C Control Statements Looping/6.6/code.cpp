/*�������� ��������� ��� ������ �������, � ������ ������ ������� ������������ ����� �����, ��� ������� � ��� ���. ��������� � ������������ ������� � ������ ������� �������. ����������� ���� for.*/
#include <stdio.h>
int main(void)
{
	int i, n1, n2;	
	printf("������ ������ ������� ��������� � ����� �����: ");
	scanf("%d",&n1);
	printf("������� ������ ������� ��������� � ����� �����: ");
	scanf("%d",&n2);
	for(i=0; n1<=n2; n1++)		
		printf("%-5d | %-5d | %-5d\n",n1,n1*n1,n1*n1*n1);
	getchar();
	getchar();
	return 0;
}