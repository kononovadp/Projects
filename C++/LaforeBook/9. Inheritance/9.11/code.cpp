/*11. В различных ситуациях иногда требуется работать с двумя числами, объединенными в блок. Например, каждая из координат экрана имеет горизонтальную составляющую (x) и вертикальную (y). Представьте такой блок чисел в качестве структуры pair, которая содержит две переменные типа int. Теперь предположим, что мы хотим иметь возможность хранить переменные типа pair в стеке. То есть мы хотим иметь возможность положить переменную типа pair в стек путем вызова метода push() с переменной типа pair в качестве аргумента и вынуть ее из стека путем вызова метода pop(), возвращающего переменную типа pair. Начнем с класса Stack2 программы STAKEN из этой главы. Создадим производный от него класс pairStack. В нем будут содержаться два метода: перегружаемый метод push() и перегружаемый метод pop(). Метод pairStack::push() должен будет сделать два вызова метода Stack2::push(), чтобы сохранить оба числа из пары, а метод pairStack::pop() должен будет сделать два вызова метода Stack2::pop()*/
#include <iostream>
using namespace std;
struct pair2{int x; int y;};
class Stack
{
	protected:
	enum {MAX=10};
	int st[MAX];
	int top;
	public:
	Stack(){top=-1;}
	void push(int var){st[++top]=var;}
	int pop(){return st[top--];}
};
class Stack2:public Stack
{
	public:
	void push(int var)
	{
		if(top>=MAX-1)
		{
			cout<<"Error: the stack is empty";
			exit(1);
		}
		Stack::push(var);
	}
	int pop()
	{
		if(top<0)
		{
			cout<<"Error: the stack is empty\n";
			exit(1);
		}
		return Stack::pop();
	}
};
class pairStack:private Stack2
{
	public:
	void push(struct pair2 coordinate)
	{
		Stack2::push(coordinate.x);
		Stack2::push(coordinate.y);
	}
	struct pair2 pop()
	{
		struct pair2 coordinate;
		coordinate.y=Stack2::pop();
		coordinate.x=Stack2::pop();
		return coordinate;
	}
};
int main()
{
	pairStack stack;
	struct pair2 coordinate;	
	int i,x=10,y=15;
	for(i=0; i<4; i++,x+=7,y+=12)
	{
		coordinate.x=x;
		coordinate.y=y;
		stack.push(coordinate);
	}
	for(i=0; i<5; i++)
	{
		coordinate=stack.pop();
		cout<<"["<<coordinate.x<<"; "<<coordinate.y<<"]\n";
	}
	return 0;
}