/*Напишите программу, которая открывает и считывает текстовый файл, фиксируя количество появлений в нем каждого слова. Используйте двоичное дерево поиска, модифицированное для хранения слова и количество его повторений. После того как программа прочитает файл, она должна отобразить меню, состоящее из трех пунктов. Первый пункт приводит к выводу списка всех слов с указанием их повторений. Второй обеспечивает возможность ввода слова, а программа должна сообщить количество вхождений этого слова в файле. Результатом третьего пункта меню должен быть выход из программы.*/
#include <stdio.h>
#include <stdbool.h>
typedef struct Item
{
	struct Item *next;
	int num;
}item;
typedef struct List
{
	struct Item *head;
}list;
void ShowArray(int *arr, int n)
{
	for(int i=0; i<n; i++)
	{
		if(i!=0 && i%10==0)
			putchar('\n');
		printf("%d ",arr[i]);
	}
}	
void InitList(struct List *mylist)
{
	mylist->head=NULL;
}
struct Item *AddItem(struct Item *myitem, int n)
{
	if(myitem==NULL)
	{
		myitem=(struct Item*)malloc(sizeof(item));
		myitem->num=n;
		myitem->next=NULL;
		return myitem;
	}
		myitem->next=AddItem(myitem->next,n);
	return myitem;
}
void ShowList(struct Item *myitem)
{
	if(myitem==NULL)
	{
		printf("List is empty!");
		return;
	}
	printf("%d ",myitem->num);
	if(myitem->next!=NULL)
		ShowList(myitem->next);
}
int MinItem(struct Item *myitem, int min)
{
	if(myitem->num<min)
		min=myitem->num;
	if(myitem->next!=NULL)
		MinItem(myitem->next,min);
	else
		return min;
}
int main(void)
{
	int n=10;
	int arr[n];
	int steps=0;
	int required;
	srand((unsigned int) time(0));
	printf("Array:\n");
	list mylist;	
	for(int i=0; i<n; i++)
		arr[i]=rand()%300;
	ShowArray(arr,n);
	InitList(&mylist);
	mylist.head=AddItem(mylist.head,arr[0]);
	for(int i=1; i<n; i++)
		AddItem(mylist.head,arr[i]);	
	printf("\nList:\n");
	ShowList(mylist.head);
	int min=MinItem(mylist.head,mylist.head->num);
	printf("\nmin = %d",min);
	return 0;
}
