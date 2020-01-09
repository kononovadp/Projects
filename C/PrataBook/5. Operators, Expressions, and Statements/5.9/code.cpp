/*�������� ���������, ������� ����������� � ������������ ���� �������� ����������� �� ����������. ��������� ������ ��������� �������� ����������� ��� ����� ���� double � ���������� ��� � ���� ��������� ���������������� ������� �� ����� Temperatures(). ��� ������� ������ ��������� ������������� �������� ����������� �� ������� � �� �������� � ���������� �� ������ ��� ��� �������� ����������� � ��������� �� ���� ������� ������ �� ���������� �����. ������� ������ ���������������� ������ �������� �������� ��������������� ������������� �����. ��� ������� �������� ����������� �� ���������� � � ����������� �� �������:
����������� �� ������� = 5.0 / 9.0 * (����������� �� ���������� - 32.0)
� ����� ��������, ������� ������ ����������� � �����, 0 ������������ ���������� ����, �. �. ����������� ������ ��������� ����������. ������� �������� ����������� �� ������� � ����������� �� ���������� ����� ���:
����������� �� �������� = ����������� �� ������� + 273.16
������� Temperatures() ������ ������������ const ��� �������� ������������� ������������� ���� ��������, ������� ���������� � ���������������. ����� ������������ ������������ ����������� ������������� ����� �������� �����������, � ������� main() ������ ���� ����������� ����, ������� ����������� ��� ����� ������� q ��� ������� ����������� ��������. �������������� ��� ������, ��� ������� scanf() ���������� ���������� ����������� �� ���������, ������� ��� ��������� 1, ���� ��������� �����, �� �� ����� ���������� 1, ����� ������������ ������ q. �������� == ��������� �������� �� ���������, ��� ��� �� ����� ��������� ��� ��������� ������������� �������� scanf() � 1.*/
#include <stdio.h>
void Temperatures(double t)
{
	printf("����������� �� ���������� = %.2f\n����������� �� �������: %.2f\n����������� �� ��������: %.2f\n",
	t,5.0/9.0*(t-32.0), 273.16+(5.0/9.0*(t-32.0)));
}
int main(void)
{
	double t;
	int n;
	printf("������� ��������� �������� ����������� �� ����������: ");
	scanf("%lf",&t);
	while (n>0)
	{
		Temperatures(t);
		printf("������� ��������� �������� ����������� �� ����������: ");
		n=scanf("%lf",&t);
	}
	printf("������");
	getchar();
	getchar();
	getchar();
	return 0;
}