/*�������� ���������, ������� ������ ����� ����� �� ��� ���, ���� �� ���������� ����� 0. ����� ����������� ����� ��������� ������ �������� ����� ���������� ��������� ������ ����� ����� (�� ����������� 0), ������� �������� ������ ����� �����, ����� ���������� ��������� �������� ����� ����� � ������� �������� �������� �����.*/
#include <stdio.h>
int main(void)
{
	int n,even_numbers,odd_numbers,even_numbers_sum,odd_numbers_sum;
	scanf("%d",&n);
	for(even_numbers=0,odd_numbers=0,even_numbers_sum=0,odd_numbers_sum=0;
	n!=0; scanf("%d",&n))
	{
		if(n!=0 && n%2==0)
		{
			even_numbers++;
			even_numbers_sum+=n;
		}
		else
		{
			odd_numbers++;
			odd_numbers_sum+=n;
		}
	}
	printf("����� ���������� ������ �����: %d\n"
	"������� �������� ������ �����: %d\n"
	"����� ���������� �������� �����: %d\n"
	"������� �������� �������� �����: %d\n",even_numbers,even_numbers_sum/even_numbers,
	odd_numbers,odd_numbers_sum/odd_numbers);	
	return 0;
}
					
