/*�������� ���������, ������� ���������� ������������ ������ ��������� �����. �������������� ���������� �������, ����� �������� ���������, ������� ������� ������ � ���� ��������, �������� ����������� ����:
    A
   ABA
  ABCBA
 ABCDCBA
ABCDEDCBA
��� ������ ������ ����������� ������ �� ���������� �������. ��������, �������������� ������ ����� ����������� ����� ������� E. ���������: ��� ��������� ����� �������������� ������� ������. ��� ������������ ������ ���������� ��� ���������� �����: ���� ��� ����������� ���������, ������ - ��� ������ ���� � ������� ����������� � ������ ��� ������ ���� � ������� ��������. ���� � ����� ������� �� ������������ ASCII ��� �������� �� ���������, � ������� ����� ������������ � �������� �������, ��. ���������� � ���������� 3.*/
#include <stdio.h>
int main(void)
{
	printf("��������� �����: ");
	char ch,lA;
	int sp,i,j;	
	scanf("%c",&ch);
	sp=ch-'A';
	for (i=0; sp>=0; i++,sp--)
	{
		for(j=0; j<sp; j++)
			printf(" ");
		for(lA='A',j=0; j<i+1; j++,lA++)
			printf("%c",lA);
		for(lA-=2,j=0; j<i; j++,lA--)
			printf("%c",lA);
		printf("\n");
	}
	getchar();
	getchar();
	return 0;
}