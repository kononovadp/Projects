/*������������� ���������� �� ���������������� 8 �� ����� 7 ���, ����� ������ ���� ���������� �������, � �� �������; ��� ����������� ����� ����������� ����� q ������ ����� 5.*/
#define tarif1 8.75
#define tarif2 9.33
#define tarif3 10.00
#define tarif4 11.20
#define overtime 1.5
#define first300 45
#define second150 30
#include <stdio.h>
void calc_salary(int const tarif)
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
	printf("�������� � ������� �������: %.2f",salary);
}
int main(void)
{
	char ch;
	printf("a) $8.75/�     b) $9.33/�\nc) $10.00/�    d) 11.20/�\nq) �����\n"
	"����� �������� �������� ������ ��� ��������: ");
	ch=getchar();
	while(ch!='q')
	{		
		switch(ch)
		{			
			case 'a': calc_salary(tarif1); break;
			case 'b': calc_salary(tarif2); break;
			case 'c': calc_salary(tarif3); break;
			case 'd': calc_salary(tarif4); break;
			case 'q': break;
			case '\n': break;
			default: printf("�������� ���������� ��������"); break;
		}
		if (ch!='\n')
			printf("\n**********************************************\n"
			"a) $8.75/�     b) $9.33/�\nc) $10.00/�    d) 11.20/�\nq) �����\n"
			"����� �������� �������� ������ ��� ��������: ");	
		ch=getchar();		
	}
	printf("������ ���������.");
	return 0;	
}