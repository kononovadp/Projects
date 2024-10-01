//6. В упражнении 3 два обычных итератора использовались для переворачивания содержимого контейнера. Теперь используйте один прямой и один обратный контейнер для выполнения того же задания, на сей раз в применении к вектору.
#include "../../accessories.h"
#include <algorithm>
#include <vector>
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	vector<int> IntVector;
	int count=16,i,NewNumber;
	cout<<"----------VECTOR:----------\n";
	for(i=0; i<count; i++)
	{
		NewNumber=GetRandomInt(0,SHRT_MAX);
		IntVector.push_back(NewNumber);
		cout<<i+1<<". "<<NewNumber<<endl;
	}
	vector<int>::iterator it1=IntVector.begin();
	vector<int>::reverse_iterator it2=IntVector.rbegin();
	for(i=0; i<IntVector.size()/2; i++)//while(true)
	{
		cout<<"Swap "<<*it1<<" with "<<*it2<<endl;
		NewNumber=*it1;
		*it1=*it2;
		*it2=NewNumber;
		it1++;		
		it2++;
	}
	cout<<"----------INVERTED VECTOR:----------\n";
	i=0;
	for(i=0; i<IntVector.size(); i++)	
		cout<<i+1<<". "<<IntVector[i]<<endl;
	return 0;
}
