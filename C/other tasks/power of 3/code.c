/*������ 1. ��� � ������� n https://habrahabr.ru/post/108550/
������ ����������� ����� n. ����� ����� ����������� ����������� k, ��� ����� 3^k �������� �� ����� n ������ ������ ����� � ���������� ������. ��������, ��� n=1 ������� ����� k=10, ��� ��� 3^10=59049 � ��� ������ �� �������� ������, ������� �������� ���� ����. ��� n=2 ������� ����� k=35, ��� ��� 3^35=50031545098999707 � ��� ������ �� �������� ������, ���������� ��� ����.*/
#include <stdio.h>
#include <stdbool.h>
bool true_number(long long unsigned int number,int zero_count)
{
	int zk=0;
	if(number==0)
		if(zero_count==1)
			return true;
		else
			return false;
	while(number>0)
	{
		while((number%10>0) && (number>0))
			number/=10;
		zk=0;
		while((number%10==0) && (number>0))
		{
			zk++;
			number/=10;
		}
		if(zk==zero_count)
			return true;
	}
	return false;
}
long long unsigned int power(long long unsigned int number, int power)
{
	long long unsigned int i,res;
	for(i=0,res=1; i<power; i++)
		res*=number;
	return res;
}
int main(void)
{
	int n=2;
	int k=0;
	long long unsigned int r=1;
	while(true_number(r,n)!=true)
	{		
		k++;
		r=power(3,k);
	}
	printf("��� n = %d 3 � ������� %d = %lld",n,k,r);
    return 0;
}