/*�������� ���������, ������� ������ ������ ����� ����� � ������, ����� ���� ������� �� � �������� �������*/
#include <stdio.h>
int main(void)
{
	int i=0;
	int a[8];
	printf("������� ����� ������ 8 ����� �����:\n");
	for (i=0; i<8; i++)
		scanf("%d",&a[i]);
	printf("----------\n");
	for(i=7; i>-1; i--)
		printf("%d  ",a[i]);
	getchar();
	getchar();
	getchar();
	return 0;
}