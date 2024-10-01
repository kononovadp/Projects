/*8. Исправьте функцию additem() из программы LINKLIST так, чтобы она добавляла новый элемент в конец списка, а не в начало. Это будет означать, что первый вставленный элемент будет выведен первым и результат работы программы будет следующим:
25
36
49
64
Для того чтобы добавить элемент, вам необходимо будет пройти по цепи до конца списка, а затем изменить указатель последнего элемента так, чтобы он указывал на новый элемент*/
#include <iostream>
using namespace std;
struct link
{
	int data;
	link* next;
};
class linklist
{
	link* first;
	public: linklist(){first=NULL;}
	void additem(int d)
	{
		if(first==NULL)
		{
			first=new link;
			first->data=d;
			first->next=NULL;
			return;
		}
		link* NewNode=first;
		while(NewNode->next!=NULL)
			NewNode=NewNode->next;
		NewNode->next=new link;
		NewNode->next->data=d;
		NewNode->next->next=NULL;
	}
	void display()
	{
		link* current=first;
		while(current)
		{
			cout<<current->data<<endl;
			current=current->next;
		}
	}
};
int main()
{
	linklist li;
	li.additem(25);
	li.additem(36);  
	li.additem(49);
	li.additem(64);
	li.display();
	return 0;
}
