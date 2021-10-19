/*6.Измените программу factor, приведенную в этой главе, таким образом, чтобы она циклически запрашивала ввод пользователем числа и вычисляла его факториал, пока пользователь не введет 0. В этом случае программа должна завершиться. При необходимости вы можете использовать соответствующие операторы программы factor в цикле do или while.*/
#include <iostream>
using namespace std;
int main(void)
{
	int j;
	unsigned int numb;
	unsigned long long fact;
	cout<<"Integer number or 0 to exit: ";
	cin>>numb;
	while(numb!=0)
	{
		for(j=numb,fact=1; j>0; j--)
			fact*=j;
		cout<<"Factorial = "<<fact;
		cout<<endl<<"Integer number or 0 to exit: ";
		cin>>numb;
	}
	return 0;
}
