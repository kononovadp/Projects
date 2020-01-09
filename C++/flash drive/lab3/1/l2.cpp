#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#define _CRT_SECURE_NO_WARNINGS
#define HEAP_SIZE 10
using namespace std;
typedef enum{ FREE, ALLOCATED };
struct memorycard
{
	int id;
	int size;
	string status;
	memorycard* next;	
} mem;

void init(int size)
{
memorycard mem;
mem.id=5;
mem.size=100;
mem.status=FREE;
}
void memshow(struct memorycard *start)
{
  while(start) {
    cout<<start->memorycard.id<<"  ";
    start = start->next;
  }
}

int main()
{
init(100);
int i;
memorycard *temp, *head;
head=NULL;
for (i=0; i<5; i++){
	temp=new memorycard;
	mem.id++;
	mem.status="free";//temp->status="free";
	//cout<<mem.id<<mem.status<<endl;
	temp->next=head;
	head=temp; }
//memshow(*head);
cin.get();	}