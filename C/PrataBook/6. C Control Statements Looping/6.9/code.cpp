/*������������� ���������� 8 ���, ����� ��������� ������������ ������� ��� �������� ����������� ����������.*/
#include <stdio.h>
double calc (double n1, double n2)
{
	return(n1-n2)/(n1*n2);
}
int main(void)
{
	int n1=0;
	int n2=0;
	double d1, d2;
	while(printf("������ ����� � ��������� �������: "),n1=scanf("%lf",&d1),n1>0,
	printf("������ ����� � ��������� �������: "),n2=scanf("%lf",&d2),n2>0)
	{
		printf("(%lf - %lf) / (%lf * %lf)=%lf",d1,d2,d1,d2,calc(d1,d2));
		printf("\n");
	}
	printf("\n������.");
	getchar();
	getchar();
	getchar();
	getchar();
	return 0;
}