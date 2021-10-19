/*12. Создайте калькулятор, выполняющей четыре арифметических действия над дробями (см. упражнение 9 главы 2 и упражнение 4 этой главы). Формулы, демонстрирующие выполнение арифметических операций над дробями, приведены ниже.
Сложение: a/b+c/d=(a*d+b*c)/(b*d)
Вычитание: a/b-c/d=(a*d-b*c)/(b*d)
Умножение: a/b-c/d=(a*c)/(b*d)
Деление: (a/b/c/d=(a*d)/(b*c)
Пользователь должен сначала ввести первый операнд, затем знак операции и второй операнд. После вычисления результата программа должна отобразить его на экране и запросить пользователя о его желании произвести еще одну операцию.*/
#include <iostream>
#include <conio.h>
using namespace std;
int main(void)
{
	char op,ch=0;
	double a,b,c,d,res;
	while(ch!='n')
	{		
		ch='/';
		cout<<"Enter fraction,operation and second fraction: ";		
		cin>>a>>ch>>b>>op>>c>>ch>>d;
		switch(op)
		{
			case '+': res=(a*d+b*c)/(b*d); break;
			case '-': res=(a*d-b*c)/(b*d); break;
			case '*': res=(a*c)/(b*d); break;
			case '/': res=(a*d)/(b*c); break;
		}
		cout<<"Result: "<<res;
		cout<<endl<<"Do you want to continue (y/n)? ";
		ch=getche();
		while(ch!='y' && ch!='n')
		{
			cout<<endl<<"press y or n: ";
			ch=getche();
		}
		cout<<endl;
	}
	return 0;
}
