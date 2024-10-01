//*3. Начните с создания списка целых чисел. Используйте два обычных (не обратных) итератора: один для продвижения в прямом направлении, другой для продвижения в обратном направлении. Вставьте их в цикл while для переворачивания содержимого списка. Ради экономии нескольких выражений можно использовать алгоритм swap() (только при этом следует убедиться, что подход работает как с четными, так и с нечетными элементами). Чтобы посмотреть, как это делают настоящие профессионалы, взгляните на функцию reverse() в заголовочном файле ALGORITHM.
#include "../../accessories.h"
#include <algorithm>
#include <list>
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	list<int> IntList;
	int count=16,i,NewNumber;
	cout<<"----------LIST:----------\n";
	for(i=0; i<count; i++)
	{
		NewNumber=GetRandomInt(0,SHRT_MAX);
		IntList.push_back(NewNumber);
		cout<<i+1<<". "<<NewNumber<<endl;
	}
	list<int>::iterator it1=IntList.begin();
	list<int>::iterator it2=IntList.end();
	it2--;
	/*while(true)
	{
		cout<<"Swap "<<*it1<<" with "<<*it2<<endl;
		NewNumber=*it1;
		*it1=*it2;
		*it2=NewNumber;
		it1++;
		if(it1==it2)
			break;
		it2--;
		if(it1==it2)
			break;
	}*/
	while(it1!=it2)
	{
		cout<<"Swap "<<*it1<<" with "<<*it2<<endl;
		NewNumber=*it1;
		*it1=*it2;
		*it2=NewNumber;
		it1++;
		if(it1==it2)
			break;
		it2--;
	}
	cout<<"----------INVERTED LIST:----------\n";
	i=0;
	while(!IntList.empty())
	{
		cout<<++i<<". "<<IntList.front()<<endl;
		IntList.pop_front();
	}
	return 0;
}
