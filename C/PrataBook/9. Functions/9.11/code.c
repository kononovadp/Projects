/*�������� � ������������� ������� Fibonacci(), � ������� ��� ���������� ����� ��������� ������ �������� ����������� ����.*/
#include <stdio.h>
void Fibonacci(int n)
{	
	int previous_result=0;
	int current_result=1;
	n/=2;
	printf("%d\n",previous_result);
	while (n>0)
	{		
		current_result+=previous_result;
		previous_result+=current_result;
		printf("%d\n%d\n",current_result,previous_result);
		n--;
	}
}
int main(void)
{
	Fibonacci(20);
	return 0;
}