// Program lab4.cpp
#include <stdio.h>
#define n 255 // ������� ����� � ����������� ����
typedef unsigned char byte; // ��� ������ � ������� ��������������� ��� char
extern "C" void BigShowN(byte* p1, int p2); //������� ���������� ����� ���������
int main()
{
	byte x[n], y[n]; //�������� �����
	for (int i = 0; i<n; i++)
	{
		x[i] = i;
		y[i] = 0;
	}
	printf("x=");
	BigShowN(x, n);
	printf("y=");
	BigShowN(y, n);
	return 0;
}