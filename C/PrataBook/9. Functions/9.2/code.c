/*�������� ������� �� ����� chline(ch,i,j), ������� ������� ��������� ������ � �������� � i �� j. ������������� ��� ������� � ������� �������� ��������.*/
#include <stdio.h>
void chline(char ch, int i, int j)
{
	int k;
	for (k=i; k<=j; k++)
		if (k==ch)
		{
			printf("\"%c\" ������ � ������� �������� � ��������� � %d �� %d = %d",ch,i,j,ch);
			return;
		}
	printf("������ \"%c\"� ��������� � %d �� %d �� ������ � ������� ��������.",ch,i,j);
}
int main(void)
{
	chline('Y',65,90);
	return 0;
}