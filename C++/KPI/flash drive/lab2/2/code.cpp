#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define HEAP_SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
using namespace std;
typedef  enum{FREE,ALLOCATED} STATUS;
struct mem 
	{int id;
	int size;
	STATUS status;
	struct mem* first;
	struct mem* next; };
int main()
{
	int i=9;
	int *j=&i;
	(*j)++;
	cout<<*j;
	cin.get();
}