//*4. Добавьте деструктор в программу LINKLIST. Он должен удалять все элементы списка при удалении объекта класса linklist. Элементы должны удаляться по очереди, в соответствии с их расположением в списке. Протестируйте деструктор путем вывода сообщения об удалении каждого из элементов списка; удалено должно быть также количество элементов, какое было положено в список (деструктор вызывается автоматически для каждого существующего объекта).
#include <iostream>
using namespace std;
struct link //один элемент списка
{
	int data; //некоторые данные
	link* next; //указатель на следующую структуру
};
class linklist //список
{
	link* first;
	public:
	linklist(){first=NULL;} //первого элемента пока нет
	~linklist()
	{
		link* current=first; //начинаем с первого элемента
		while(current) //пока есть данные
		{
			first=current;
			cout<<"Node "<<current->data<<" was deleted\n"; //печатаем данные
			current=current->next; //двигаемся к следующему элементу			
			delete first;			
		}
		first=NULL;
	}
	void additem(int d) //добавление элемента
	{
		link* newlink=new link; //выделяем память
		newlink->data=d; //запоминаем данные
		newlink->next=first; //запоминаем значение first
		first=newlink; //first теперь указывает на новый элемент
	}
	void display()
	{
		link* current=first; //начинаем с первого элемента
		while(current) //пока есть данные
		{
			cout<<current->data<<endl; //печатаем данные
			current=current->next; //двигаемся к следующему элементу
		}
	}
};
int main()
{
	linklist li; //создаем переменную-список
	li.additem(25); //добавляем туда несколько чисел
	li.additem(36);
	li.additem(49);
	li.additem(64);
	li.display(); //показываем список	
	return 0;
}