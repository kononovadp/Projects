/*��� ��� ��������� ���������� 8, �� �� ���� ��� ���������� ����������� �������.*/
#include <stdio.h>
double power(double n, int p)
{	
	double pow=1;
	if ((n==0) && (p==0))
	{
		printf("��������� ���������� ����� 0 � ������� 0 �� ���������,\n"
		"������� ������������ ��������� ���������� 0 � ������� 1.\n");
		return 0;
	}
	if (abs(p)>0)
		pow=n*power(n,abs(p)-1);
	if (p<0)
		pow=1/pow;
	return pow;
}
int main(void)
{
	double n=100;
	int p=-1;
	printf("%lf � ������� %d = %lf",n,p,power(n,p));
	return 0;
}