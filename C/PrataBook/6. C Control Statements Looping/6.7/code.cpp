/*�������� ���������, ������� ������ ����� � ���������� ������, � ����� ������� ��� ����� � �������� �������. ���������: �������������� �������� strlen() (����� 4) ��� ���������� ������� ���������� ������� �������.*/
#include <stdio.h>
#include <conio.h>
#define size 50
int main(void)
{
	int n,i=0;
	char arr[size];
	char ch;
	printf("�����: ");
	while(ch!=13)
	{
		ch=getche();
		arr[i]=ch;
		i++;
	}
	printf("\n");
	while(i-- >0)
		printf("%c",arr[i]);
	getchar();
	return 0;
}