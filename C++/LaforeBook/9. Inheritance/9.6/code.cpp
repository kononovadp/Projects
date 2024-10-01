/*6. Вспомним программу ARROVER3 из главы 8. Сохраним класс safearay таким же и, используя наследование, добавим к нему возможность для пользователя определять верхнюю и нижнюю границы массива в конструкторе. Это похоже на упражнение 9 из главы 8, за исключением того, что применено наследование для создания нового класса (можно назвать его safehilo) взамен модификации исходного класса*/
#include <iostream>
using namespace std;
const int LIMIT=30; //размер массива
class safearray
{
	protected: int arr[LIMIT];
	public:
    int& operator[](int n)
	{
		if(n<0 || n>=LIMIT)
		{
			cout<<"\nIncorrect index!";
			exit(1);
		}
        return arr[n];
	}
};
class safehilo:public safearray
{
	int LowerIndex,UpperIndex;
	bool overflow;
	public:
	safehilo(int NewLowerIndex,int NewUpperIndex)
	{
		LowerIndex=NewLowerIndex;
		UpperIndex=NewUpperIndex;
	}
	bool GetOverflow(){return overflow;}
	int& operator[](int n)
	{
		overflow=false;
		if(n>=LowerIndex && n<=UpperIndex)			
			return arr[n];
		overflow=true;
		return arr[0];
	}
};
int main()
{
	safehilo sa1(5,20);
	int i;
	for(i=0; i<LIMIT; i++)
		sa1[i]=i*10;
	for(i=0; i<LIMIT; i++)
	{
		int temp=sa1[i];
		if(!sa1.GetOverflow())
			cout<<"Item with index "<<i<<" equals "<<temp<<endl;
		else
			cout<<"Item with index "<<i<<" doesn't exist\n";
	}
	return 0;
}
