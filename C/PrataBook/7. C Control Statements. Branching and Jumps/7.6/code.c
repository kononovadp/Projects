/*�������� ���������, ������� ������ ������� ������, ���� �� �������� ������ #, � �������� ���������� ��������� ������������������ ei. �� �������: ��� ��������� ������ ���������� ���������� ������, � ����� ������� ������� ������. ��������� �� �� ������� ������������������ ����� "Receive your eieio award#".*/
#include <stdio.h>
int main(void)
{
	char ch,char_array[100];
	int j,i=0;
	int ei=0;
	while((ch=getchar())!='#')
	{
		char_array[i]=ch;
		i++;
	}
	for(j=1; j<i; j++)
		if (char_array[j-1]=='e' && char_array[j]=='i')
			ei++;
	printf("\n���������� ei: %d",ei);
	return 0;
}