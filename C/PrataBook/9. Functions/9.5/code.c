/*�������� � ������������� ������� �� ����� larger_of(), ������� �������� ���������� ���� ���������� double ������� �� �� ��������. ��������, ����� larger_of(x,y) �������� ���������� x � y ������� �� �� ��������.*/
#include <stdio.h>
void larger_of (double *x, double *y)
{
	printf("�������� ������: x = %lf; y = %lf.\n",*x,*y);
	if (*x>*y)
		*y=*x;
	else
		*x=*y;
}
int main(void)
{
	double x=10.898;
	double y=9.675;
	larger_of(&x,&y);
	printf("���������� x � y ����� ������ �������:\nx = %lf; y = %lf.\n",x,y);
	return 0;
}