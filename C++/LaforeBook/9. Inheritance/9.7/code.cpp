/*7. Вспомним программу COUNTEN2 из этой главы. В ней можно увеличивать и уменьшать счетчик, используя префиксные операции. Используя наследование, добавьте возможность использования постфиксных операций для случаев увеличения и уменьшения. (Описание постфиксных операций высможете найти в главе 8.)*/
#include <iostream>
using namespace std;
class Counter
{
	protected: unsigned int count;
	public:
    Counter():count(){}
    Counter(int c):count(c){}
    unsigned int get_count()const{return count;}
    Counter operator++(){return Counter(++count);}
};
class CountDn:public Counter
{
	public:
    CountDn():Counter(){}
    CountDn(int c):Counter(c){}
    CountDn operator--(){return CountDn(--count);}
};
class PrefixAndPostfixCounter:public Counter
{
	public:
	PrefixAndPostfixCounter():Counter(){}
    PrefixAndPostfixCounter(int c):Counter(c){}
	PrefixAndPostfixCounter operator--(){return PrefixAndPostfixCounter(--count);}
    PrefixAndPostfixCounter operator--(int){return PrefixAndPostfixCounter(count--);}
	PrefixAndPostfixCounter operator++(){return PrefixAndPostfixCounter(++count);}
    PrefixAndPostfixCounter operator++(int){return PrefixAndPostfixCounter(count++);}
};
int main()
{
	PrefixAndPostfixCounter c1;
	PrefixAndPostfixCounter c2(100);
	cout<<"\nc1 = "<<c1.get_count();
	cout<<"\nc2 = "<<c2.get_count();
	++c1; ++c1; ++c1;
	cout<<"\nc1 = "<<c1.get_count();
	--c2; --c2;
	cout<<"c2 = "<<c2.get_count();
	PrefixAndPostfixCounter c3=--c2;
	cout<<"\nc3 = "<<c3.get_count();
	c3++; c3++; c3++;
	cout<<"\nc3 = "<<c3.get_count();
	c3--; c3--;
	cout<<"\nc3 = "<<c3.get_count();
	cout<<endl;
	return 0;
}
