/*�������� ������� to_binary() �� �������� 9.8 �� ������� to_base_n(), ������� ��������� ������ �������� � ��������� �� 2 �� 10. ��� ������ �������� �����, ���������� � ������ ��������� � ������� ��������� � ����������, ������� ������� �� ������ ���������. ��������, ����� to_base_n(129,8) ������ ���������� 201, �. �. ������������ ���������� ����� 129. ������������� ������� ������� � �����-������ ���������.*/
#include <stdio.h>
void to_base_n(unsigned long n,int number_system)
{	
	int r;
	r=n%number_system;
	if (n>=number_system)
		to_base_n(n/number_system,number_system);
	printf("%d",r);
	return;
}
int main(void)
{
	int n=19867;
	int nsys=8;
	printf("%d � ������� ��������� � ���������� %d = ",n,nsys);
	to_base_n(n,nsys);
	return 0;
}