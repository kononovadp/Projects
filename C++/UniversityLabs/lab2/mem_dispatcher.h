#pragma once
using namespace std;
struct mem_chunk
{
	int id;
	int size;
	string status;
	mem_chunk* next;
};
struct mem_dispatcher
{
	int last_id_used;
	mem_chunk* first;	
};
void init(mem_dispatcher *md);
int allocate(mem_dispatcher *md, int size);
int deallocate(mem_dispatcher *md, int block_id);
void defragment(mem_dispatcher *md);
void show_memory_map(mem_dispatcher *md);
void menu(mem_dispatcher *md);