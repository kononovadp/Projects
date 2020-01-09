#include <stdio.h>
#include <stdbool.h>
typedef struct StackChar
{
	char mychar;
	struct StackChar *prev;
}stackchar;
typedef struct Stack
{
	struct StackChar *last;
}stack;
void InitializeStack(stack *mystack)
{
	mystack->last=NULL;
}
void ShowStack(stack *st)
{
	stackchar *el=st->last;
	if(el==NULL)
	{
		printf("No elements found.\n");
		return;
	}
	while(el!=NULL)
	{
		printf("%c ",el->mychar);
		el=el->prev;
	}
	putchar('\n');
}
void AddToStack(stack *st,char ch)
{
	char current,previous;
	stackchar *p;
	if(st->last==NULL)
	{
		st->last=(stackchar*)malloc(sizeof(stackchar));
		st->last->mychar=ch;
		st->last->prev=NULL;
		return;
	}
	p=st->last;
	current=p->mychar;
	while(p->prev!=NULL)
	{
		previous=p->prev->mychar;
		p->prev->mychar=current;
		current=previous;
		p=p->prev;
	}
	p->prev=(stackchar*)malloc(sizeof(stackchar));
	p->prev->mychar=current;
	p->prev->prev=NULL;
	st->last->mychar=ch;
}
void DeleteFromStack(stack *st)
{
	//st->last=st->last->prev;
	if(st->last==NULL)
		return;
	if(st->last->prev==NULL)
	{
		st->last=NULL;
		return;
	}
	stackchar *p=st->last;
	stackchar *p2=st->last->prev;
	while(p->prev!=NULL)
	{
		p->mychar=p->prev->mychar;
		p=p->prev;
	}
	p=st->last;
	if(p->prev!=NULL)
	{
		while(p->prev->prev!=NULL)
			p=p->prev;
		free(p->prev);
		p->prev=NULL;
	}
}
