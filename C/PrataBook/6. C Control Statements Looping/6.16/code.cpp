/*����� ������ ����� � ����� $100 ��� ������� 10%. (�� ���� ��������� ������� ������ ���������� 10% �� �������������� �����). ������ ���������� $100 ��� ������� 5%. (��� ������, ��� ��������� ���������� ������ ���������� 5% �� �������� �������, ����������� ���������� ������� ������). �������� ���������, ������� ���������, ������� ����� ���, ����� �� ����� ������ ��������� ����� �� ����� �����. ������� ����� ������ ����� ������� �� ��� ������.*/
#include <stdio.h>
int main(void)
{
	int i;
	float dafna,deydra;
	printf("| Year | Dafna | Deydra |\n");
	/*for(dafna=100,deydra=100,i=1; deydra>dafna; i++)
	{
		dafna+=10;
		deydra+=deydra/20;
		printf("| Year | Dafna | Deydra |\n");
		printf("%2d %3d %3d\n",i,dafna,deydra);
	}*/
	dafna=100.0;
	deydra=100.0;
	i=1;
	while(dafna>=deydra)
	{
		dafna+=10.0;
		deydra+=deydra/20.0;
		printf("%5d %7.0f %9.2f\n",i,dafna,deydra);
		i++;
	}
	getchar();
	return 0;
}