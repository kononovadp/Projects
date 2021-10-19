#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <conio.h>
#define _CRT_SECURE_NO_WARNINGS
#define HEAP_SIZE 100
using namespace std;
struct mem_chunk{
	int id;
	int size;
	string status;
	mem_chunk* next;
};
struct mem_dispatcher{
	int last_id_used;
	mem_chunk* first;	
};

void init(mem_dispatcher *md)
{
	mem_chunk *mc;
	mc=new mem_chunk;
	md->first=mc;	
	mc->id=0;
	mc->size=HEAP_SIZE;
	mc->status="free";
	mc->next=NULL;
	md->last_id_used=mc->id;
}
int allocate(mem_dispatcher *md, int size)
{	
	mem_chunk *t,*m=NULL;
	t=md->first;
	int min=HEAP_SIZE+1;
	while (t!=NULL)
	{ 
		if ((t->size < min) && (t->status=="free") && (t->size>=size))
			{m=t; min=t->size; }
		t=t->next;
	}
	if (m!=NULL)
	{if (m->size==size)
		m->status="allocated";
	else
	{t=m->next;
	m->size=m->size-size;
	m->next=new mem_chunk;
	m=m->next;
	m->id=md->last_id_used+1;
	m->size=size;
	m->status="allocated";
	m->next=t;
	md->last_id_used=m->id;	
	}	}
	else cout<<"allocation failed: incorrect size"<<endl;
}
int deallocate(mem_dispatcher *md, int block_id)
{
	mem_chunk *t,*p; bool b=0;
	t=md->first; p=t;
	while (t != NULL)
	{	
		if (t->id ==block_id)
		{
			t->status="free";
			b=1;
		}
		t=t->next;
	}
	for(int i=0; i<2; i++)
	{
	p=md->first; t=p; 
	while (t->next != NULL)
	{	t=t->next;
		if ((p->status=="free")&&(t->status=="free"))
		{	
			p->size+=t->size;
			p->next=t->next;
		}
		p=t;
	}	}
	if (b==0)
		cout<<"deallocation failed"<<endl;
}
void defragment(mem_dispatcher *md)
{
	mem_chunk *t,*p,*ffb;
	t=md->first;
	bool b=0;
	while(t!=NULL)
	{
		if(t->status=="free")
		{
			ffb=t;
			b=1;
			break;
		}
	t=t->next;
	}
	if (b==0) 
	{
		cout<<"free block was not found"<<endl;
		exit;
	}
	t=ffb; 
	while (t->next!=NULL)
	{
		p=t;
		t=t->next;
		if (t->status=="free")
		{
			ffb->size+=t->size;
			p->next=t->next;
		} 
	}
}
void show_memory_map(mem_dispatcher *md)//displays heap status
{	
	mem_chunk *t;
	t=md->first;
	do {
 		cout<<"block id: "<<t->id<<" size: "<<t->size<<" status: "<<t->status<<endl;
		t=t->next;
	}while (t!=NULL);
}
void menu(mem_dispatcher *md)
{
	cout<<"1. Allocate"<<endl;
	cout<<"2. Deallocate"<<endl;
	cout<<"3. Show memory map"<<endl;
	cout<<"4. Defragment"<<endl;
	cout<<"5. Exit"<<endl;
	int menu; int id_or_size;
	while(menu!=53)
	{
	cout<<"Enter command: ";
	menu=getch();
	cout<<menu-48<<endl;
 		if (menu==49)
		{
			cout<<"Enter the size of allocated block ";
			cin>>id_or_size;
			allocate(md,id_or_size);
		}
		else
			if (menu==50)
			{
				cout<<"Enter id of deallocated block ";
				cin>>id_or_size;
				deallocate(md,id_or_size);
			}
		else
			if (menu==51)
				show_memory_map(md);
		else
			if (menu==52)
				defragment(md);
		else 
			cout<<"incorrect command"<<endl;		
	}
}
int main()
{	mem_dispatcher *md;
	md=new mem_dispatcher;
	init(md);
	menu(md);
	//allocate(md,5); //show_memory_map(md);
	//allocate(md,20); //show_memory_map(md);
	//allocate(md,30); //show_memory_map(md);
	//allocate(md,3); //show_memory_map(md);
	//deallocate(md,4); show_memory_map(md);
	//deallocate(md,2); show_memory_map(md);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//deallocate(md,3); deallocate(md,3); show_memory_map(md);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	//cin.get();
}