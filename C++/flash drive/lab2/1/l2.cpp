#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define HEAP_SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
using namespace std;
typedef  enum{ FREE, ALLOCATED } STATUS;
typedef struct mem{
	int id;
	int size;
	STATUS status;
	struct mem* next;//pointer to the next memory block
//add here whatever you need
//
}mem_chunk;

typedef struct {
	int last_id_used;
	 mem* first;//pointer to the first memory block
}mem_dispatcher;


//creates a heap as a single free block  with id 0 and HEAP_SIZE size
void init(mem_dispatcher *md);
//returns block id if allocated and -1 otherwise
int allocate(mem_dispatcher *md, int size);
//returns nonnegative value if block is deallocated and -1 otherwise
int deallocate(mem_dispatcher *md, int block_id);
//reunites free blocks that were previously stored in various parts of a heap //into one successive block 
void defragment(mem_dispatcher *md);
//displays heap status
void show_memory_map(mem_dispatcher *md);

int main()
{
mem.id=9;


cin.get();
}