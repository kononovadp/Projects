/*Обобщите функцию to_binary() из листинга 9.8 до функции to_base_n(), которая принимает второй аргумент в диапазоне от 2 до 10. Она должна выводить число, переданное в первом аргументе в системе счисления с основанием, которое указано во втором аргументе. Например, вызов to_base_n(129,8) должен отобразить 201, т. е. восьмеричный эквивалент числа 129. Протестируйте готовую функцию в какой-нибудь программе.*/
#include <stdio.h>
void to_base_n(unsigned long n,int number_system)
{	
	int r;
	r=n%number_system;
	if (n>=number_system)
		to_base_n(n/number_system,number_system);
	printf("%d",r);
	return;
}
int main(void)
{
	int n=19867;
	int nsys=8;
	printf("%d в системе счисления с основанием %d = ",n,nsys);
	to_base_n(n,nsys);
	return 0;
}