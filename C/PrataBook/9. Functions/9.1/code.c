/*�������� ������� �� ����� min(x,y), ������� ���������� ������� �� ���� �������� ���� double. ������������� ��� ������� � ������� �������� ��������.*/
#include <stdio.h>
double min (double x, double y)
{
	if (x<y)
		return x;
	else
		return y;
}
int main(void)
{
	double x,y;
	printf("������ ����� � ��������� �������: ");
	scanf("%lf",&x);
	printf("������ ����� � ��������� �������: ");
	scanf("%lf",&y);
	printf("������� �� ���� ����� �������� %lf",min(x,y));
	return 0;
}