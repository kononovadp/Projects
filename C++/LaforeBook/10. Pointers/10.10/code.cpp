/*10. Описанный в упражнении 9 подход нерационален, так как каждый из 10 массивов объявляется отдельно, с использованием отдельного имени, и каждый адрес получают отдельно. Вы можете упростить программу, используя операцию new, которая позволит вам выделить память для массивов в цикле и одновременно связать с ними указатели:
for(j = 0; j < NUMARRAYS; j++)  // создаем NUMARRAYS массивов
	*(ар + j) = new int[MAXSIZE];  // no MAXSIZE целых чисел в каждом
Перепишите программу упражнения 9, используя этот подход. Доступ к отдельному элементу массивов вы сможете получить, используя то же выражение, что и в упражнении 9, или аналогичное выражение с указателями: *(*(ap + j)+k)*/
#include "../../accessories.h"
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	int i,j,MaxSize=10,**arr=new int*[MaxSize];
	for(i=0; i<MaxSize; i++)
	{
		*(arr+i)=new int[MaxSize];
		for(j=0; j<MaxSize; j++)
			*(*(arr+i)+j)=GetRandomInt(10,1000);
	}
	for(i=0; i<MaxSize; i++)
	{
		for(j=0; j<MaxSize; j++)
			cout<<setw(5)<<*(*(arr+i)+j);
		cout<<endl;
	}
	for(i=0; i<MaxSize; i++)
		delete[]*(arr+i);
	delete[]arr;
	return 0;
}
