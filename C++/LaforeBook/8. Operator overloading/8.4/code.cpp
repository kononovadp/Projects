/**4. Создайте класс Int, основанный на упражнении 1 из главы 6. Перегрузите четыре целочисленных арифметических операции (+, -, * и /) так, чтобы их можно было использовать для операций с объектами класса Int. Если результат какой-либо из операций выходит за границы типа int (в 32-битной системе), имеющие значение от 2 14 7 483 648 до -2 147 483 648, то операция должна послать сообщение об ошибке и завершить программу. Такие типы данных полезны там, где ошибки могут быть вызваны арифметическим переполнением, которое недопустимо. Подсказка: для облегчения проверки переполнения выполняйте вычисления с использованием типа long double. Напишите программу для проверки этого класса*/
#include <iostream>
#include <limits.h>
using namespace std;
class Int
{
	int n;
	bool overflow;
	public: Int(){}
	Int(long double NewN)
	{		
		if(NewN>INT_MAX || NewN<INT_MIN)
			overflow=true;		
		else
		{			
			n=NewN;
			overflow=false;
		}
	}
	void show()
	{
		if(overflow==false)
			cout<<n;
		else
			cout<<"overflow";
	}
	Int operator+(Int operand){return (long double)n+(long double)operand.n;}
	Int operator-(Int operand){return (long double)n-(long double)operand.n;}
	Int operator*(Int operand){return (long double)n*(long double)operand.n;}
	Int operator/(Int operand){return (long double)n/(long double)operand.n;}
	Int operator++()
	{
		int PrevN=n;
		Int temp(++n);
		if(n<PrevN)
		{
			overflow=true;
			n=PrevN;
			temp.n=n;
			temp.overflow=true;
		}
		return temp;
	}
	Int operator++(int)
	{
		Int temp(n++);
		if(n<temp.n)
		{
			overflow=true;
			n=temp.n;
		}
		return temp;
	}
	Int operator--()
	{
		int PrevN=n;
		Int temp(--n);
		if(n>PrevN)
		{
			overflow=true;
			n=PrevN;
			temp.n=n;
			temp.overflow=true;
		}
		return temp;
	}
	Int operator--(int)
	{		
		Int temp(n--);
		if(n>temp.n)
		{
			overflow=true;
			n=temp.n;
		}
		return temp;
	}
};
void TestClass(Int n1,Int n2,char operation)
{
	//Int n1(operand1);
	//Int n2(operand2);
	Int result,N1PlusPlus,N2PlusPlus;
	n1.show();
	cout<<" "<<operation<<" ";
	n2.show();
	cout<<" = ";
	switch(operation)
	{
		case '+': result=n1+n2; result.show(); cout<<endl;
		N1PlusPlus=n1++;
		N2PlusPlus=n2++;
		cout<<"n1++: ";
		n1.show();
		cout<<"; N1PlusPlus=n1++: ";
		N1PlusPlus.show();		
		cout<<endl<<"n2++: ";
		n2.show();
		cout<<"; N2PlusPlus=n2++: ";
		N2PlusPlus.show();		
		N1PlusPlus=++n1;
		N2PlusPlus=++n2;
		cout<<"\n++n1: ";
		n1.show();
		cout<<"; N1PlusPlus=++n1: ";
		N1PlusPlus.show();		
		cout<<endl<<"++n2: ";
		n2.show();
		cout<<"; N2PlusPlus=++n2: ";
		N2PlusPlus.show();
		cout<<endl;
		break;
		case '-': result=n1-n2; result.show(); cout<<endl;
		N1PlusPlus=n1--;
		N2PlusPlus=n2--;
		cout<<"n1--: ";
		n1.show();
		cout<<"; N1PlusPlus=n1--: ";
		N1PlusPlus.show();		
		cout<<endl<<"n2--: ";
		n2.show();
		cout<<"; N2PlusPlus=n2--: ";
		N2PlusPlus.show();		
		N1PlusPlus=--n1;
		N2PlusPlus=--n2;
		cout<<"\n--n1: ";
		n1.show();
		cout<<"; N1PlusPlus=--n1: ";
		N1PlusPlus.show();		
		cout<<endl<<"--n2: ";
		n2.show();
		cout<<"; N2PlusPlus=--n2: ";
		N2PlusPlus.show();
		cout<<endl;
		break;
		case '*': result=n1*n2; result.show(); cout<<endl; break;
		case '/': result=n1/n2; result.show(); cout<<endl; break;
	}	
}
int main(void)
{
	Int n1(INT_MAX);
	Int n2(20);
	TestClass(n1,n2,'+');
	TestClass(n1,n2,'-');
	TestClass(n1,n2,'*');
	TestClass(n1,n2,'/');
	cout<<"----------------------------------------------------\n";
	Int n3(INT_MIN);
	Int n4(20);
	TestClass(n3,n4,'+');
	TestClass(n3,n4,'-');
	TestClass(n3,n4,'*');
	TestClass(n3,n4,'/');
	return 0;
}
