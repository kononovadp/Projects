/*Напишите программу, которая позволяет ввести строку. Программа затем должна заталкивать в стек символы строки по одному (см. вопрос для самоконтроля под номером 5), выталкивать символы из стека и, наконец, отображать их. В результате символы отображаются в обратном порядке.
Стек является еще одной формой данных из семейства списков. В стеке добавления и удаления могут выполняться только с одной стороны списка. Говорят, что элементы "заталкиваются" в стек и "выталкиваются" из него. Следовательно, стек представляет собой структуру LIFO (rear in, first out - "последним прибыл, первым обслужен").
а. Определите тип ADT для стека.
б. Определите программный интерфейс стека, т. е. заголовочный файл stack.h.*/
#include <stdio.h>
typedef struct Node
{
	struct Node *prev;
	char ch;
}node;
typedef struct Stack
{
	struct Node *rear;
}stack;
void InitStack(stack *st)
{
	st->rear=NULL;
}
void AddToStack(stack *st,char ch)
{
	char current,previous;
	node *p;
	if(st->rear==NULL)
	{
		st->rear=(node*)malloc(sizeof(node));
		st->rear->ch=ch;
		st->rear->prev=NULL;
		return;
	}
	p=st->rear;
	current=p->ch;
	while(p->prev!=NULL)
	{
		previous=p->prev->ch;
		p->prev->ch=current;
		current=previous;
		p=p->prev;
	}
	p->prev=(node*)malloc(sizeof(node));
	p->prev->ch=current;
	p->prev->prev=NULL;
	st->rear->ch=ch;
}
void DeleteFromStack(stack *st)
{
	//st->rear=st->rear->prev;
	if(st->rear==NULL)
		return;
	if(st->rear->prev==NULL)
	{
		st->rear=NULL;
		return;
	}
	node *p=st->rear;
	node *p2=st->rear->prev;
	while(p->prev!=NULL)
	{
		p->ch=p->prev->ch;
		p=p->prev;
	}
	p=st->rear;
	if(p->prev!=NULL)
	{
		while(p->prev->prev!=NULL)
			p=p->prev;
		free(p->prev);
		p->prev=NULL;
	}
}
void AddItem(stack *st,char ch)
{
	if(st->rear==NULL)
	{
		st->rear=(struct Node*)malloc(sizeof(node));
		st->rear->ch=ch;
		st->rear->prev=NULL;
	}
	else
	{
		node *item=st->rear;
		char t1,t2;
		t1=item->ch;
		while(item->prev!=NULL)
		{
			t2=item->prev->ch;
			item->prev->ch=t1;
			t1=t2;
			item=item->prev;
		}
		item->prev=(struct Node*)malloc(sizeof(node));
		item->prev->ch=t1;
		item->prev->prev=NULL;
		st->rear->ch=ch;
	}
}
void ShowStack(stack *st)
{
	node *item=st->rear;
	while(item!=NULL)
	{
		putchar(item->ch);
		item=item->prev;		
	}
	putchar('\n');
}	
int main(void)
{
	char s[50];
	printf("Current string: ");
	scanf("%s",&s);
	stack mystack;
	InitStack(&mystack);
	for(int i=0; i<strlen(s); i++)
		AddToStack(&mystack,s[i]); //AddItem(&mystack,s[i]);
	printf("Stack: ");
	ShowStack(&mystack);
	for(int i=0; i<strlen(s); i++)
	{
		DeleteFromStack(&mystack);
		ShowStack(&mystack);
	}
    return 0;
}
