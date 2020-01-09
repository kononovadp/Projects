/*Напишите программу, которая позволяет ввести строку. Программа затем должна заталкивать в стек символы строки по одному (см. вопрос для самоконтроля под номером 5), выталкивать символы из стека и, наконец, отображать их. В результате символы отображаются в обратном порядке.
Стек является еще одной формой данных из семейства списков. В стеке добавления и удаления могут выполняться только с одной стороны списка. Говорят, что элементы "заталкиваются" в стек и "выталкиваются" из него. Следовательно, стек представляет собой структуру LIFO (last in, first out - "последним прибыл, первым обслужен").
а. Определите тип ADT для стека.
б. Определите программный интерфейс стека, т. е. заголовочный файл stack.h.*/
#include <stdio.h>
typedef struct Node
{
	struct Node *next;
	char ch;
}node;
typedef struct List
{
	struct Node *head;
}list;
void InitList(list *my_list)
{
	my_list->head=NULL;
}
void AddItem(list *my_list, char ch)
{
	if(my_list->head==NULL)
	{
		my_list->head=(struct Node*)malloc(sizeof(node));
		my_list->head->ch=ch;
		my_list->head->next=NULL;
	}
	else
	{
		node *p=my_list->head;
		while(p->next!=NULL)
			p=p->next;
		p->next=(struct Node*)malloc(sizeof(node));
		p->next->ch=ch;
		p->next->next=NULL;
	}
}
void ShowList(list *my_list)
{
	node *p=my_list->head;
	while(p!=NULL)
	{
		putchar(p->ch);
		p=p->next;
	}
}
int main(void)
{
    char *s="1235h";
	list mylist;
	InitList(&mylist);
	for(int i=0; i<strlen(s); i++)
		AddItem(&mylist,s[i]);
	ShowList(&mylist);
    return 0;
}
