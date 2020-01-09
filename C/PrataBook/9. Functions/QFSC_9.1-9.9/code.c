/*
2.а. int donut (int n);
2.б. int gear (int n1, int n2);
2.в. int guess(void);
2.г. void stuff_it(double n, double *a);
3.a. char n_to_char (int n);
3.б. int digits (double n1, int n2);
3.в. double *which(double *a1, double *a2);
3.г. int random(void);
4. int sum(int n1, int n2) { return n1+n2 }
5. double sum(double n1, double n2) { return n1+n2 } или
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
		printf("\nВы ввели нечисловые данные: выход из программы.\n");
		return 4;
	}
	if (n<bottom_limit || n>upper_limit)
	{
		printf("Некорректное значение. Повторите ввод.\n");
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
		printf("Выберите один из следующих вариантов:\n"
		"1) копировать файлы	2) переместить файлы\n"
		"3) удалить файлы	4) выйти из программы\n"
		"Введите номер выбранного варианта: ");
		menu_point=get_menu_point(1,4);
		printf("Выбранное действие: ");	
		switch (menu_point)
		{
			case 0: printf("повтор ввода;\n"); break;
			case 1: printf("копирование файлов;"); printf("\n"); break;
			case 2: printf("перемещение файлов;"); printf("\n"); break;
			case 3: printf("удаление файлов;"); printf("\n"); break;
			case 4: printf("выход из программы."); break;		
		}
	}
}
int main(void)
{
	menu();
	return 0;
}