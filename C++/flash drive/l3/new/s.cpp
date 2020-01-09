#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
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

void init(mem_dispatcher *md)//returns block id if allocated and -1 otherwise
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
	else cout<<"!!!"<<endl;
}

int deallocate(mem_dispatcher *md, int block_id);
void defragment(mem_dispatcher *md);


void show_memory_map(mem_dispatcher *md)//displays heap status
{	
	mem_chunk *t;
	t=md->first;
	do {
 		cout<<"block id: "<<t->id<<" size: "<<t->size<<" status: "<<t->status<<endl;
		t=t->next;
	}while (t!=NULL);
	cout<<"________________________"<<endl<<endl;
}
int main()
{	mem_dispatcher *md;
	md=new mem_dispatcher;
	init(md);show_memory_map(md);
	allocate(md,5);show_memory_map(md);
	allocate(md,20);show_memory_map(md);
	allocate(md,30);show_memory_map(md);
	allocate(md,3);show_memory_map(md);
	show_memory_map(md);

	cin.get();
}