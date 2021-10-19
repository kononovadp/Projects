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
	mem_chunk *t,*h,*m=NULL;
	t=md->first;
	m=t;
	while (t!=NULL)
	{
		if (t->size < m->size)
			m=t;
		t=t->next;
	}
	t=m->next;
	m->next=new mem_chunk;
	m=m->next;
	m->id=md->last_id_used+1;
	m->size=size;
	m->status="allocated";
	m->next=t;
	md->last_id_used=m->id;		
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
}
int main()
{	mem_dispatcher *md;
	md=new mem_dispatcher;
	init(md);
	allocate(md,5); allocate(md,20); allocate(md,30); allocate(md,3);
	show_memory_map(md);

	cin.get();
}