/**3. Напишите программу, генерирующую следующий вывод:
10
20
19
Используйте представление числа 10 в виде целой константы. Для вывода числа 20 воспользуйтесь одной из арифметических операций с присваиванием, а для вывода числа 19 - операцией декремента.*/
#include<iostream>
using namespace std;
int main(void)
{
	const int c=10;
	int n;
	cout<<c<<endl;
	n=c*2;
	cout<<n<<'\n';
	n--;
	cout<<n;
	return 0;
}
