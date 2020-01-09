//#pragma once
#include <string.h>
typedef struct IntItem
{
	int number;
}intitem;
typedef struct Word
{
	char *word;
	int repeats_count;
}worditem;
void ShowArray(int *arr, int n)
{
	for(int i=0; i<n; i++)
	{
		if(i!=0 && i%10==0)
			putchar('\n');
		printf("%d ",arr[i]);
	}
}
void ShowIntItem(intitem *my_item)
{
	printf("%d ",my_item->number);
}
void ShowWordItem(worditem *my_item)
{
	printf("Word: %s; repeaats count: %d; appearance count: %d\n",
	my_item->word,my_item->repeats_count,my_item->repeats_count+1);
}
char CompareIntItems(intitem *item1, intitem *item2)
{
	if(item1->number<item2->number)
		return '<';
	if(item1->number==item2->number)
		return '=';
	if(item1->number>item2->number)
		return '>';
}
char CompareCharArrays(char *arr1, char *arr2)
{
	int symbols_count;
	if(strlen(arr1)<strlen(arr2))
		symbols_count=strlen(arr1);
	else
		symbols_count=strlen(arr2);
	for(int i=0; i<symbols_count; i++)
		if(arr1[i]<arr2[i])
			return '<';
		else
			if(arr1[i]>arr2[i])
				return '>';
	if(strlen(arr1)==strlen(arr2))
		return '=';
	else
		if(strlen(arr1)<strlen(arr2))
			return '<';
		else
			return '>';
}
char CompareWordItems(worditem *item1, worditem *item2)
{
	char comparison_result=CompareCharArrays(item1->word,item2->word);
	if(comparison_result=='>')
		return '>';
	else
		if(comparison_result=='<')
			return '<';
		else
			return '=';
}
intitem *CreateIntItem(int n)
{
	intitem *newitem=(intitem*)malloc(sizeof(intitem));
	newitem->number=n;
	return newitem;
}
worditem *CreateWordItem(char *word)
{
	worditem *newitem=(worditem*)malloc(sizeof(worditem*));	
	newitem->word=(char*)malloc(strlen(word)*sizeof(char));
	strcpy(newitem->word,word);
	newitem->repeats_count=0;
	return newitem;
}
void ChangeWordRepeatsCount(worditem *item)
{
	item->repeats_count=item->repeats_count+1;
}
