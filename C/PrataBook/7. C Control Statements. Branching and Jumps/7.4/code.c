/*���������� ��������� if else, �������� ���������, ������� ������ ������� ������, ���� �� �������� ������ #, �������� ������ ����� ��������������� ������, ���������� �������������� ��������������� ����� - ����� ���������������� ������� � � ����� �������� � ���������� ������������� �����.*/
#include <stdio.h>
int main(void)
{
	char ch,char_array[100];
	int j,i=0;
	int changes=0;
	while((ch=getchar())!='#')
	{
		char_array[i]=ch;
		i++;
	}
	
	printf("Output: ");
	for(j=0; j<i; j++)
		if (char_array[j]=='.'||char_array[j]=='!')
		{
			if (char_array[j]=='.')
				printf("!");
			else if(char_array[j]=='!')
				printf("!!");
			changes++;
		}
		else
			printf("%c",char_array[j]);
	printf("\nʊ��������� ������������� �����: %d",changes);
	return 0;
}
					
