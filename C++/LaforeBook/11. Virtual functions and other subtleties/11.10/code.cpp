//10. Упражнение 4 в главе 10 включало в себя добавление к классу linklist перегружаемого деструктора. Допустим, мы заполняем объект этого класса данными, а затем присваиваем один класс целиком другому, используя стандартный оператор присваивания: list2 = list1; Допустим, что впоследствии мы удалим объект класса list1. Можем ли мы все еще использовать list2 для доступа к введенным данным? Увы, нет, так как при удалении list1 все его ссылки были удалены. Единственное, что было известно объекту linklist про удаленный объект, это указатель на него. Но его удалили, указатель в list2 стал недееспособным, и все попытки получить доступ к данным приведут к получению мусора вместо данных, а в худшем случае — к зависанию программы. Один из способов избежать этих проблем — перегрузить оператор присваивания, чтобы он вместе с объектом копировал бы все его ссылки. Но тогда придется пройти по всей цепочке, поочередно копируя все ссылки. Как отмечалось ранее, следует также перегружать конструктор копирования. Чтобы была возможность удалять объекты linklist в main(), можно создавать их с помощью указателя и new. В таком случае проще будет проверять работу новых операций. Не переживайте, если обнаружите, что в процессе копирования порядок следования данных изменился. Понятно, что копирование всех данных не является самым эффективным решением проблемы с точки зрения экономии памяти. Сравните этот подход с представленным в примере STRIMEM (глава 10), где использовался только один набор данных для всех объектов, и хранилась информация о том, сколько объектов указывали на эти данные.
//Класс String с экономией памяти
//Перегружаемая операция присваивания и конструктор копирования
#include "../../accessories.h"
struct link //один элемент списка
{
	int data;
	link* next;
};
class linklist
{
	link* first;
	public:
	linklist(){first=NULL;}
	~linklist()
	{
		link* current=first;
		while(current)
		{
			first=current;
			cout<<setw(4)<<current->data; 
			current=current->next;
			delete first;			
		}
		first=NULL;
	}
	void AddItem(int d)
	{
		link* newlink=new link;
		newlink->data=d;
		newlink->next=first;
		first=newlink;
	}
	void display()
	{
		link* current=first;
		while(current)
		{
			cout<<setw(4)<<current->data;
			current=current->next;
		}
	}
	linklist& operator=(linklist& list2)
	{
		link* current=list2.first;
		while(current)
		{
			AddItem(current->data);
			current=current->next;
		}
		return *this;		
	}
};
class ObjectsCounter
{
	int CountOfLinks,CountOfItems;
	linklist* data;
	friend class LinkedList;
	ObjectsCounter(int* array,int ArraySize):CountOfItems(ArraySize),CountOfLinks(1)
	{		
		data=new linklist();
		for(int i=0; i<CountOfItems; i++)
			data->AddItem(array[i]);		
	}
	~ObjectsCounter()
	{
		delete data;
		CountOfLinks=0;
		CountOfItems=0;
	}
};
class LinkedList
{
	ObjectsCounter* counter;
	public:
	LinkedList(int* array,int ArraySize)
	{
		counter=new ObjectsCounter(array,ArraySize);
	}
	LinkedList(LinkedList& NewLinkedList)
	{
		counter=NewLinkedList.counter;
		(counter->CountOfLinks)++;
	}
	void DeleteFromMemory()
	{		
		if(counter->CountOfLinks==1)
		{
			delete counter;
			counter=NULL;
		}
		else
			(counter->CountOfLinks)--;			
	}	
	void display()
	{
		counter->data->display();
		cout<<"\nAddress: "<<counter<<"; count of links: "<<counter->CountOfLinks;
	}
	void operator=(LinkedList& NewLinkedList)
	{
		if(counter->CountOfLinks==1)
			delete counter;
		else
			(counter->CountOfLinks)--;
		counter=NewLinkedList.counter;
		(counter->CountOfLinks)++;
	}
};
int main()
{
	char ch=0;
	int i,ArraySize,*array;
	InitFloatingPointAndRandomNumbers();
	while(ch!='0')
	{
		ArraySize=GetRandomInt(10,16);
		array=new int[ArraySize];
		linklist LinkedList1,LinkedList2;
		cout<<"ARRAY:                 ";		
		for(i=0; i<ArraySize; i++)
		{
			array[i]=GetRandomInt(0,1000);
			cout<<setw(4)<<array[i];
			LinkedList1.AddItem(array[i]);
		}
		cout<<"\nLinked list 1:         ";
		LinkedList1.display();
		LinkedList2=LinkedList1;
		cout<<"\nLinked list 2:         ";
		LinkedList2.display();		
		cout<<"\nDelete linked list 1:  ";
		LinkedList1.~linklist();
		cout<<"\nLinked list 2:         ";
		LinkedList2.display();
		cout<<"\nDelete linked list 2:  ";
		LinkedList2.~linklist();
		cout<<"\n------------------------------------------------------------------------------------------";
		LinkedList LinkedList3(array,ArraySize);
		delete[]array;
		cout<<"\nLinked list 3:         ";
		LinkedList3.display();
		LinkedList LinkedList4=LinkedList3;
		cout<<"\nLinked list 4:         ";
		LinkedList4.display();
		LinkedList LinkedList5(LinkedList3);
		cout<<"\nLinked list 5:         ";
		LinkedList5.display();
		cout<<"\nDeleting of Linked list 3...";
		LinkedList3.DeleteFromMemory();
		cout<<" Deleting of Linked list 4...";
		LinkedList4.DeleteFromMemory();
		cout<<"\nDelete linked list 5:  ";
		LinkedList5.DeleteFromMemory();
		cout<<"\n==========================================================================================\n";
		cout<<"Press 1 to start again or 0 to exit: ";
		ch=getch();
		while(ch!='0' && ch!='1')		
			ch=getch();
		cout<<ch<<endl;		
	}
	return 0;
}