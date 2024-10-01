/* *3. Напишите функцию с именем zeroSmaller(), в которую передаются с помощью ссылок два аргумента типа int, присваивающую меньшему из аргументов нулевое значение. Напишите программу для проверки работы функции.*/
#include <iostream>
using namespace std;
void zeroSmaller(int& n1,int& n2)
{
	if(n1<n2)
		n1=0;
	else
		if(n2<n1)
			n2=0;
}
int main(void)
{
	int n1=70,n2=50;
	zeroSmaller(n1,n2);
	cout<<"n1 = "<<n1<<" n2 = "<<n2;
	return 0;
}
