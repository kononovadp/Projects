/*
2.�. int donut (int n);
2.�. int gear (int n1, int n2);
2.�. int guess(void);
2.�. void stuff_it(double n, double *a);
3.a. char n_to_char (int n);
3.�. int digits (double n1, int n2);
3.�. double *which(double *a1, double *a2);
3.�. int random(void);
4. int sum(int n1, int n2) { return n1+n2 }
5. double sum(double n1, double n2) { return n1+n2 } ���
int sum(int n1, int n2) { return (double)n1+(double)n2 }
6. alter (int *x, int *y) { int temp=*x+*y; *y-=*x; x=temp; }
7. void salami (int num)...
8. int biggest (int a, int b, int c) {
	if (a>b && a>c) return a; else
	if (b>a && b>c) return b; else return c; }
9.:*/
#include <stdio.h>
void menu();
int get_menu_point(int bottom_limit, int upper_limit)
{
	int n;
	if (scanf ("%d",&n)==0)
	{
		printf("\n�� ����� ���������� ������: ����� �� ���������.\n");
		return 4;
	}
	if (n<bottom_limit || n>upper_limit)
	{
		printf("������������ ��������. ��������� ����.\n");
		return 0;
	}
	else
		return n;
}
void menu()
{	
	int menu_point;
	while(menu_point!=4)
	{
		printf("�������� ���� �� ��������� ���������:\n"
		"1) ���������� �����	2) ����������� �����\n"
		"3) ������� �����	4) ����� �� ���������\n"
		"������� ����� ���������� ��������: ");
		menu_point=get_menu_point(1,4);
		printf("��������� ��������: ");	
		switch (menu_point)
		{
			case 0: printf("������ �����;\n"); break;
			case 1: printf("����������� ������;"); printf("\n"); break;
			case 2: printf("����������� ������;"); printf("\n"); break;
			case 3: printf("�������� ������;"); printf("\n"); break;
			case 4: printf("����� �� ���������."); break;		
		}
	}
}
int main(void)
{
	menu();
	return 0;
}