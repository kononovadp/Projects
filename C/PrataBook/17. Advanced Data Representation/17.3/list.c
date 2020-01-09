// list.c -- функции для поддержки операций со списком 
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// прототип локальной функции 
static void CopyToNode(Item item, Node * pnode);

// функции интерфейса 
// устанавливает список в пустое состояние 
void InitializeList(List * plist)
{
	plist->items=0;
}

// возвращает true, если список пуст 
bool ListIsEmpty(const List * plist)
{
    if (plist->items==0)
        return true;
    else
        return false;
}

// возвращает true, если список полон 
bool ListIsFull(const List * plist)
{
    Node * pt;
    bool full;

    pt = (Node *) malloc(sizeof(Node));
    if (pt == NULL)
        full = true;
    else
        full = false;
    free(pt);

    return full;
}

// возвращает количество узлов 
unsigned int ListItemCount(const List * plist)
{
    return plist->items;
}

// создает узел для хранения элемента и добавляет его в конец 
// списка, указанного переменной plist (медленная реализация) 
bool AddItem(Item item, List * plist)
{
	plist->entries[plist->items]=item;
	plist->items+=1;
	return true;
}

// посещает каждый узел и выполняет функцию, указанную pfun 
void Traverse  (const List * plist, void (* pfun)(Item item) )
{
    for(int i=0; i<plist->items; i++)
		(*pfun)(plist->entries[i]);
}

// освобождает память, выделенную функцией malloc() 
// устанавливает указатель списка в NULL            
void EmptyTheList(List * plist)
{
    for(int j=0; j<plist->items; j++)
		for(int i=0; i<plist->items-j; i++)
			plist->entries[i]=plist->entries[i+1];
	plist->items=0;
}

// определение локальной функции 
// копирует элемент в узел       
static void CopyToNode(Item item, Node * pnode)
{
    pnode->item = item;  // копирование структуры 
}

