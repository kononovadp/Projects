/*Разработайте и протестируйте функцию, которая извлекает из ввода следующие n символов (включая символы пробела, табуляции и новой строки), сохраняя результаты в массиве, адрес которого передается в качестве аргумента.*/
#include <stdio.h>
void add_inf_to_array(int n, char string[n])
{
	printf("Введите символы: ");
	fgets(string,n,stdin);
}

int main(void)
{
    int n=100;
	char arr[n];
	add_inf_to_array(n, arr);
	fputs(arr, stdout);
    return 0;
}