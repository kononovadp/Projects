/*8. Основываясь на программе LINKLIST из главы 10 «Указатели», напишите программу, позволяющую пользователю выбрать одно из четырех действий нажатием соответствующей кнопки. Действия таковы:
♦ добавить ссылку в список (от пользователя требуется ввести целое число);
♦ показать данные по всем ссылкам из списка;
♦ записать в файл данные для всех ссылок (создание или переписывание файла);
♦ считать все данные из файла и создать новый список ссылок, куда и поместить их.
Первые два действия могут использовать методы, уже имеющиеся в LINKLIST. От вас требуется написать функции для чтения и записи файла. И для того, и для другого можно использовать один и тот же файл. В нем должны храниться только данные; нет никакого смысла хранить содержимое указателей, которые, возможно, уже не будут нужны во время чтения списка*/
#include "../../accessories.h"
struct ListItem
{
	int data;
	struct ListItem* next;
};
class LinkedList
{
	struct ListItem* head;
	public:
	LinkedList():head(NULL){}
	~LinkedList()
	{
		struct ListItem* item=head;
		while(item)
		{
			struct ListItem* ItemForDeletion=item;
			//cout<<"Item for deletion: "<<ItemForDeletion->data<<endl;
			item=item->next;
			delete ItemForDeletion;
		}
		head=NULL;
	}
	void AddItem(int n)
	{
		if(head==NULL)
		{
			head=new struct ListItem();
			head->data=n;
			head->next=NULL;
		}
		else
		{
			struct ListItem* NewItem=head;
			while(NewItem->next!=NULL)
				NewItem=NewItem->next;
			NewItem->next=new struct ListItem();
			NewItem->next->data=n;
			NewItem->next->next=NULL;
		}
	}
	void AddItem(struct ListItem* NewItem)
	{
		if(head==NULL)
			head=NewItem;
		else
		{
			struct ListItem* item=head;
			while(item->next!=NULL)
				item=item->next;
			item->next=NewItem;
			NewItem->next->next=NULL;
		}
	}
	void AddItem()
	{
		char ch=0;
		int n;
		while(ch!='0')
		{
			cout<<"New item (int): ";
			n=GetIntFromKeyboard(0,9999);
			AddItem(n);
			cout<<"\nPress 1 to add a new item or 0 to stop input: ";
			ch=getch();
			while(ch!='0' && ch!='1')
				ch=getch();
			cout<<ch<<endl;
		}
	}
	void display()
	{
		struct ListItem* NewItem=head;
		cout<<"List: ";
		while(NewItem)
		{
			cout<<setw(5)<<NewItem->data;
			NewItem=NewItem->next;
		}
		cout<<endl;
	}
	void WriteListToFile()
	{
		ofstream file("LinkedList.txt");
		struct ListItem* NewItem=head;
		while(NewItem)
		{
			file<<NewItem->data<<" ";
			NewItem=NewItem->next;
		}
		file.close();
	}
	void AddItemsFromMemoryToFile()
	{		
		int n;
		LinkedList ListFromFile;
		ifstream file("LinkedList.txt");
		file>>n;
		while(!file.eof())
		{
			ListFromFile.AddItem(n);
			file>>n;
		}
		file.close();		
		struct ListItem* item=head;
		while(item)
		{
			ListFromFile.AddItem(item->data);
			item=item->next;
		}		
		ofstream NewFile("LinkedList.txt");
		item=ListFromFile.head;
		while(item)
		{
			NewFile<<item->data<<" ";
			item=item->next;
		}
		NewFile.close();
	}
};
int main(void)
{	
	char ch=0;
	LinkedList NewLinkedList;
	while(ch!='0')
	{
		cout<<"1. Add items to the linked list;\n2. Display list;\n3. Write list to the file;\n";
		cout<<"4. Add items from memory to the file;\n0. Exit.\nYour choice: ";
		ch=getch();
		while(ch<'0' || ch>'4')
			ch=getch();
		cout<<ch<<endl;
		switch(ch)
		{
			case '1': NewLinkedList.AddItem(); break;
			case '2': NewLinkedList.display(); break;
			case '3': NewLinkedList.WriteListToFile(); break;
			case '4': NewLinkedList.AddItemsFromMemoryToFile(); break;
			default: break;
		}
	}
	return 0;
}
