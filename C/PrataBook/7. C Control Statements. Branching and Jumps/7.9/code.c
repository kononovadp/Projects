/*�������� ���������, ������� ��������� � �������� ����� ������������� ����� ����� � ���������� ��� ������� �����, ������� ������ ��� ����� ���������� �����.*/
#include <stdio.h>
int main(void)
{
	int n,i,j,divisors;
	short b;
	printf("������������� ����� �����: ");
	scanf("%d",&n);
	printf("��� ������� ����� �� 1 �� %d:\n",n);
	while(--n >1)
	{
		divisors=0;
		for(i=1; i<n; i++)
			if(n%i==0)
				divisors++;
		if(divisors<2)
			printf("%d\n",n);
	}
	printf("��������� ���������");
	return 0;	
}