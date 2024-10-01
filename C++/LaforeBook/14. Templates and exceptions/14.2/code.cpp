/**2. Очередь — это тип хранилища данных. Она напоминает по своей сути стек, только вместо правила LIFO (последний вошел — первый вышел) использует правило FIFO (первый вошел — первый вышел). В общем, как очередь у окошка в банке. Если вы заносите в массив числа 1, 2, 3, обратно вы их получите в той же последовательности.
Стеку требуется для работы только один индекс массива (front, вершина массива. См. программу STAKARAY из главы 7). Очереди же требуется два индекса: индекс хвоста, куда добавляются новые элементы, и индекс головы очереди, откуда исчезают старые. Хвост постепенно сдвигается, как и голова. Если хвост или голова достигает конца массива, он переставляется на начало.
Напишите шаблон класса для работы с очередью. Предположим, что программист не будет совершать ошибок при написании ее модели. Например, вместимость очереди не будет превышена, а из пустой очереди не будет производиться попыток удаления данных. Определите несколько очередей разных типов и поработайте с их данными*/
#include "../../accessories.h"
#include <random>
using namespace std;
template <class AnyType>
AnyType* GetRandomIntegerData(AnyType MinNumber,AnyType MaxNumber,int CountOfItems,default_random_engine RandomGenerator)
{
	AnyType* RandomArray=new AnyType[CountOfItems];
	uniform_int_distribution<AnyType> distribution(MinNumber,MaxNumber);
	for(int i=0; i<CountOfItems; i++)	
		RandomArray[i]=distribution(RandomGenerator);
	return RandomArray;
}
template <class AnyType>
AnyType* GetRandomCharAndDouble(AnyType MinNumber,AnyType MaxNumber,int CountOfItems,AnyType RandomGenerator(AnyType min,AnyType max))
{
	AnyType* RandomArray=new AnyType[CountOfItems];
	for(int i=0; i<CountOfItems; i++)
		RandomArray[i]=RandomGenerator(MinNumber,MaxNumber);
	return RandomArray;
}
template <class AnyType>
class QueueTemplate
{	//https://codechick.io/tutorials/dsa/dsa-circular-queue
	AnyType* queue;
	int front,rear,QueueLength;
	public:
	QueueTemplate(int NewMaxLength)
	{
		QueueLength=NewMaxLength;
		queue=new AnyType[QueueLength];
		front=-1;
		rear=-1;
	}
	~QueueTemplate(){delete[] queue;}
	void push(AnyType item)
	{
		if((front==0 && rear==QueueLength-1) || (front==rear+1))
		{
			cout<<"The item "<<item<<" can't be PUSHED. The queue is FULL.\n";
			return;
		}
		if(front==-1)
			front=0;
		rear = (rear+1)%QueueLength;
		queue[rear]=item;		
		cout<<"The item "<<item<<" was PUSHED under the index "<<rear<<endl;
		if(rear==QueueLength)
			rear=0;
	}
	AnyType pop()
	{
		if(front==-1)
		{
			cout<<"The queue is EMPTY\n";
			return -1;
		}
		int item=queue[front];
		cout<<"The item "<<item<<" was POPPED under the index "<<front<<endl;
		if(front==rear)
		{
			front=-1;
			rear=-1;
		}
		else
			front=(front+1)%QueueLength;		
		return item;
	}
};
int main(void)
{
	InitFloatingPointAndRandomNumbers();	
	random_device RandomDevice;
	default_random_engine RandomGenerator(RandomDevice());
	int i,j,LineWidth,CountOfDigits,CountOfDivides,CountOfOperations;
	int CountOfItems=GetRandomInt(5,20);
	
	int IntMax=INT_MAX/CountOfItems,IntMin=IntMax/CountOfItems;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		IntMin/=10;
	int* IntArray=GetRandomIntegerData(IntMin,IntMax,CountOfItems,RandomGenerator);
	CountOfDigits=GetCountOfDigits(IntMax);
	LineWidth=90/(CountOfDigits+1);
	cout<<"RANDOM SIZE: "<<CountOfItems<<"; MIN: "<<IntMin<<"; MAX: "<<IntMax<<"; RANDOM "<<"INT ARRAY: ";
	for(i=0; i<CountOfItems; i++)
	{
		if(i%LineWidth==0)
			cout<<endl;
		cout<<setw(CountOfDigits+1)<<IntArray[i];
	}
	cout<<endl;
	QueueTemplate<int> IntQueue(CountOfItems);
	/*for(i=0; i<CountOfItems; i++)
		IntQueue.push(IntArray[i]);	
	IntQueue.pop();
	IntQueue.pop();
	IntQueue.push(123);
	IntQueue.push(321);
	IntQueue.push(4567);*/
	CountOfOperations=GetRandomInt(CountOfItems,CountOfItems*3);	
	for(i=0,j=0; i<CountOfOperations; i++)
		if(GetRandomInt(0,2))
		{
			IntQueue.push(IntArray[j++]);
			if(j==CountOfItems)
				j=0;
		}
		else
			IntQueue.pop();
	for(i=0; i<91; i++)
		cout<<'-';
	
	long long LongLongMax=LLONG_MAX/CountOfItems,LongLongMin=LongLongMax/CountOfItems;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		LongLongMin/=10;
	long long* LongLongArray=GetRandomIntegerData(LongLongMin,LongLongMax,CountOfItems,RandomGenerator);
	CountOfDigits=GetCountOfDigits(LongLongMax);
	LineWidth=90/(CountOfDigits+1);
	cout<<"RANDOM SIZE: "<<CountOfItems<<"; MIN: "<<LongLongMin<<"; MAX: "<<LongLongMax<<"; RANDOM "<<"LONG LONG ARRAY: ";
	for(i=0; i<CountOfItems; i++)
	{
		if(i%LineWidth==0)
			cout<<endl;
		cout<<setw(CountOfDigits+1)<<LongLongArray[i];
	}
	cout<<endl;
	QueueTemplate<long long> LongLongQueue(CountOfItems);
	CountOfOperations=GetRandomInt(CountOfItems,CountOfItems*3);	
	for(i=0,j=0; i<CountOfOperations; i++)
		if(GetRandomInt(0,2))
		{
			LongLongQueue.push(LongLongArray[j++]);
			if(j==CountOfItems)
				j=0;
		}
		else
			LongLongQueue.pop();
	for(i=0; i<91; i++)
		cout<<'-';
	
	double DoubleMax=INT_MAX/CountOfItems,DoubleMin=DoubleMax/CountOfItems;
	for(i=0,CountOfDivides=GetRandomDouble(2,6); i<CountOfDivides; i++)
		DoubleMin/=10.0;
	double* DoubleArray=GetRandomCharAndDouble(DoubleMin,DoubleMax,CountOfItems,GetRandomDouble);
	CountOfDigits=GetCountOfDigits(INT_MAX)+3;
	LineWidth=90/(CountOfDigits+1);
	cout<<"RANDOM SIZE: "<<CountOfItems<<"; MIN: "<<DoubleMin<<"; MAX: "<<DoubleMax<<"; RANDOM "<<"DOUBLE ARRAY: ";
	for(i=0; i<CountOfItems; i++)
	{
		if(i%LineWidth==0)
			cout<<endl;
		cout<<setw(CountOfDigits+1)<<DoubleArray[i];
	}
	cout<<endl;
	QueueTemplate<double> DoubleQueue(CountOfItems);
	CountOfOperations=GetRandomInt(CountOfItems,CountOfItems*3);	
	for(i=0,j=0; i<CountOfOperations; i++)
		if(GetRandomInt(0,2))
		{
			DoubleQueue.push(DoubleArray[j++]);
			if(j==CountOfItems)
				j=0;
		}
		else
			DoubleQueue.pop();
	for(i=0; i<91; i++)
		cout<<'-';
	
	char* CharArray=GetRandomCharAndDouble('A','Z',CountOfItems,GetRandomChar);
	cout<<"RANDOM SIZE: "<<CountOfItems<<"; MIN: A; MAX: Z; RANDOM CHAR ARRAY: ";
	for(i=0; i<CountOfItems; i++)
	{
		if(i%45==0)
			cout<<endl;
		cout<<CharArray[i]<<' ';
	}
	cout<<endl;
	QueueTemplate<char> CharQueue(CountOfItems);
	CountOfOperations=GetRandomInt(CountOfItems,CountOfItems*3);	
	for(i=0,j=0; i<CountOfOperations; i++)
		if(GetRandomInt(0,2))
		{
			CharQueue.push(CharArray[j++]);
			if(j==CountOfItems)
				j=0;
		}
		else
			CharQueue.pop();
	for(i=0; i<91; i++)
		cout<<'-';
	return 0;
}
