/**3. Добавьте механизм обработки исключений в программу из упражнения 2. Рассмотрите два исключения: при превышении размера очереди и при попытке удаления данных из пустой очереди. Это можно сделать, добавив новый элемент данных в класс очереди — счетчик текущего числа элементов в очереди. Инкрементируйте счетчик при добавлении нового элемента, декрементируйте, соответственно, при удалении элемента из головы очереди. Генерируйте исключение, если счетчик превысил размер массива или если он стал меньше 0.
Можно попробовать сделать main() интерактивной, чтобы пользователь мог вводить и извлекать данные. Так будет проще проверить работу написанных функций. С помощью механизма исключений программа должна обеспечивать повторную попытку ввода данных пользователем без нарушения целостности содержимого очереди.*/
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
class ErrorQueueIsEmpty
{		
	public:		
	ErrorQueueIsEmpty(){}
	void display()
	{
		cout<<"The queue is EMPTY\n";
	}
};
template <class AnyType>
class ErrorQueueIsFull
{		
	AnyType QueueItem;
	public:		
	ErrorQueueIsFull(AnyType NewQueueElement)
	{
		QueueItem=NewQueueElement;
	}
	void display()
	{
		cout<<"The item "<<QueueItem<<" can't be added: The queue is FULL\n";
	}
};
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
			throw ErrorQueueIsFull<AnyType>(item);		
		if(front==-1)
			front=0;
		rear=(rear+1)%QueueLength;
		queue[rear]=item;		
		cout<<"The item "<<item<<" was PUSHED under the index "<<rear<<endl;
		if(rear==QueueLength)
			rear=0;
	}
	AnyType pop()
	{
		if(front==-1)
		{
			throw ErrorQueueIsEmpty();
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
template <class AnyType>
void AddFromArrayToTheQueue(AnyType* array,int ArraySize,int CountOfDigits)
{
	int i,LineWidth=90/(CountOfDigits+1);
	for(i=0; i<ArraySize; i++)
	{
		if(i%LineWidth==0)
			cout<<endl;
		cout<<setw(CountOfDigits+1)<<array[i];
	}
	cout<<endl;
	QueueTemplate<AnyType> IntQueue(ArraySize);
	cout<<"1. Add an array item to the queue;\n2. Retrieve an item from the queue;\n0. Exit;\n";
	for(char ch=0,i=0; ch!='0'; )
	{
		cout<<"Choice: ";
		ch=getch();
		while(ch<'0' || ch>'2')
			ch=getch();
		cout<<ch<<". ";
		switch(ch)
		{
			case '1':			
			try{IntQueue.QueueTemplate<AnyType>::push(array[i++]);}
			catch(ErrorQueueIsFull<AnyType> NewError)
			{
				NewError.display();
				i--;
			}
			if(i==ArraySize)
				i=0;
			break;
			case '2':
			try{IntQueue.pop();}
			catch(ErrorQueueIsEmpty NewError)
			{
				NewError.display();
			}
			break;
			case '0': cout<<"Exit";
		}
	}
}
int main(void)
{
	InitFloatingPointAndRandomNumbers();	
	random_device RandomDevice;
	default_random_engine RandomGenerator(RandomDevice());
	int i,CountOfDivides;
	int ArraySize=GetRandomInt(5,20);
	
	int IntMax=INT_MAX/ArraySize,IntMin=IntMax/ArraySize;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		IntMin/=10;
	int* IntArray=GetRandomIntegerData(IntMin,IntMax,ArraySize,RandomGenerator);	
	cout<<"RANDOM SIZE: "<<ArraySize<<"; MIN: "<<IntMin<<"; MAX: "<<IntMax<<"; RANDOM "<<"INT ARRAY: ";
	AddFromArrayToTheQueue(IntArray,ArraySize,GetCountOfDigits(IntMax));
	
	/*double DoubleMax=LLONG_MAX/ArraySize,DoubleMin=DoubleMax/ArraySize;
	for(i=0,CountOfDivides=GetRandomInt(2,6); i<CountOfDivides; i++)
		DoubleMin/=10.0;
	double* DoubleArray=GetRandomCharAndDouble(DoubleMin,DoubleMax,ArraySize,GetRandomDouble);
	cout<<"RANDOM SIZE: "<<ArraySize<<"; MIN: "<<DoubleMin<<"; MAX: "<<DoubleMax<<"; RANDOM "<<"DOUBLE ARRAY: ";
	AddFromArrayToTheQueue(DoubleArray,ArraySize,GetCountOfDigits(LLONG_MAX)+3);*/
	return 0;
}
