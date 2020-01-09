/*�������� ���������, ������� �������������� ������ �������� ���� double � ����� �������� ��� ���������� � ��� ������ �������. (��� ������ ������� ������ ���� ��������� � ������� ���������.) ��� �������� ������ ����� �������������� ��������, � ������� ����������� ����� ������ � ���������. ��� �������� ������ ����� ����������� �������, � ������� ����������� ����� ������ � ����������� � ����������������� ����������. ������ ��� ������� ������ ��������� � �������� ���������� ��� �������� �������, ��� ��������� ������� � ���������� ���������, ���������� �����������. ������ ������� ������ ��������� � �������� ���������� ��� �������� �������, ��� ��������� ������� � ��������� �� �������, ��������� �� ��������� ��������� � �������� �������. � ������ ����������� ���� ���������� ������ ������� ������ ��������� ���:
double source [5]={1.1, 2.2, 3.3, 4.4, 5.5};
double target1[5];
double target2[5];
double target3[5];
copy_arr(target1, source, 5);
copy_ptr(target2, source, 5);
copy_ptrs(target3, source, source+5);*/
/* rain.c -- ������� ��������� ������ �� �����, ������� �������� �� ��� � �������
             �������� �� ����� �� ������ �� ������� �� ��������� ��� */
#include <stdio.h>
void copy_arr(double target[], double source[], int n)
{
	int i;
	for (i=0; i<n; i++)
		target[i]=source[i];
}
void copy_ptr(double target[], double source[], int n)
{
	double *tp=target;
	double *sp=source;
	int i;
	for(i=0; i<n; i++,tp++,sp++)
		*tp=*sp;
}
void copy_ptrs(double target[], double source[], double source_end[])
{
	for (; source<source_end; source++,target++)
		*target=*source;
}
int main(void)
{
    double source [5]={1.1, 2.2, 3.3, 4.4, 5.5};
	double target1[5];
	double target2[5];
	double target3[5];
	int i;
	copy_arr(target1, source, 5);
	printf("�������� ������: ");
	for(i=0; i<5; i++)
		printf("%.1lf ",source[i]);
	printf("\n������ ������: ");
	for(i=0; i<5; i++)
		printf("%.1lf ",target1[i]);
	copy_ptr(target2, source, 5);
	printf("\n������ ������: ");
	for(i=0; i<5; i++)
		printf("%.1lf ",target2[i]);
	copy_ptrs(target3, source, source+5);
	printf("\n������ ������: ");
	for(i=0; i<5; i++)
		printf("%.1lf ",target3[i]);
    return 0;
}