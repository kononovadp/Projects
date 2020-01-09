/*�������� ���������, ������� ����������� ���������� �����, ������������ �� ������, � ������� �������� ����� ����� ����������, ������� � ������ ��������, ������ �� ������������� ���� �����������:
�. �������� �������� ������ ���������� ����� = $10 / ���;
�. ������������ ���� (����������� 40 ����� � ������) - ����������� = 1.5;
�. ��������� ������: 15% � ������ $300, 20% �� ��������� $150, 25% � �������.
����������� ��������� #define � �� ������������, ���� ����������� ������ �� ������������� ������������ ���������������.*/
#define tarif 10
#define overtime 1.5
#define first300 45
#define second150 30
#include <stdio.h>
int main(void)
{
	int hours;
	float salary,over450;
	printf("���������� ������������ ����� �� ������: ");
	scanf("%d",&hours);
	if (hours<=40)
		salary=hours*tarif;
	else
	{
		salary=40*tarif;
		hours-=40;
		salary+=hours*tarif*overtime;
	}
	printf("����� ��������: %.2f\n",salary);
	if (salary>=300 && salary <450)
		salary-=first300;
	else if (salary==450)
		salary=salary-first300-second150;
	else if (salary>450)
	{
		over450=salary-450;
		over450=over450*25/100;
		salary=salary-first300-second150-over450;
	}		
	printf("�������� � ������� �������: %.2f\n",salary);
	return 0;
}