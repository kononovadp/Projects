#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <limits.h>
#include <Windows.h>
#include <malloc.h>
FILE* tests;
unsigned int HashTableSize;
struct ItemOfTable
{
	void* array;
	unsigned int key;
	unsigned int ItemSize;
	struct ItemOfTable* next;
};
struct HashTable
{
	unsigned int ItemsCount;
	struct ItemOfTable** items;
};
unsigned int SumOfEvennessAndTheLastDigit_Char(void* array,unsigned int size)
{
	unsigned int i,sum=0;
	unsigned char* CharsArray=(unsigned char*)array;
	for(i=0; i<size; i++)
		sum=sum+((CharsArray[i]%2)+(CharsArray[i]%10));
	while(sum>HashTableSize)
		sum/=10;
	return sum;
}
unsigned int SumOfEvennessAndTheLastDigit_Int(void* array,unsigned int size)
{
	unsigned int i,sum=0;
	int* IntArray=(int*)array;
	for(i=0; i<size; i++)
		sum=sum+((IntArray[i]%2)+(IntArray[i]%10));
	while(sum>HashTableSize)
		sum/=10;
	return sum;
}
unsigned int AverageSumOfNumberAndIndex_Char(void* array,unsigned int size)
{
	unsigned int i,sum=0;
	unsigned char *CharsArray=(unsigned char*)array;
	for(i=0; i<size; i++)
		sum+=CharsArray[i]+i;
	sum/=size;
	while(sum>HashTableSize)
		sum/=10;
	return sum;//(sum/size)-(sum%10);
}
unsigned int AverageSumOfNumberAndIndex_Int(void* array,unsigned int size)
{
	unsigned int i,sum=0;
	int* IntArray=(int*)array;
	for(i=0; i<size; i++)
		sum+=IntArray[i]+i;
	sum/=size;
	while(sum>HashTableSize)
		sum/=10;
	return sum;//(sum/size)-(sum%10);
}
unsigned int MurmurHash2_Char(void *array,unsigned int size)
{//https://ru.wikipedia.org/wiki/MurmurHash2
	const unsigned int m = 0x5bd1e995;
	const unsigned int seed = 0;
	const int r = 24;
	unsigned int hash = seed ^ size;	
	const unsigned char * CharsArray = (unsigned char *)array;
	unsigned int k;
	while(size>=4)
	{
		k=CharsArray[0];
		k|=CharsArray[1]<<8;
		k|=CharsArray[2]<<16;
		k|=CharsArray[3]<<24;
		k*=m;
		k^=k>>r;
		k*=m;
		hash*=m;
		hash^=k;
		CharsArray+=4;
		size-=4;
	}
	switch(size)
	{
		case 3:
		hash^=CharsArray[2]<<16;
		case 2:
		hash^=CharsArray[1]<<8;
		case 1:
		hash^=CharsArray[0];
		hash*=m;
	};
	hash^=hash>>13;
	hash*=m;
	hash^=hash>>15;
	while(hash>HashTableSize)
		hash/=10;
	return hash;
}
unsigned int MurmurHash2_Int(void *array,unsigned int size)
{	//https://ru.wikipedia.org/wiki/MurmurHash2
	const unsigned int m=0x5bd1e995;
	const unsigned int seed=0;
	const int r=24;
	unsigned int hash=seed^size;
	int* IntArray=(int*)array;
	unsigned int k;
	while(size>=4)
	{
		k=IntArray[0];
		k|=IntArray[1]<<8;
		k|=IntArray[2]<<16;
		k|=IntArray[3]<<24;
		k*=m;
		k^=k>>r;
		k*=m;
		hash*=m;
		hash^=k;
		IntArray+=4;
		size-=4;
	}
	switch(size)
	{
		case 3:
		hash^=IntArray[2]<<16;
		case 2:
		hash^=IntArray[1]<<8;
		case 1:
		hash^=IntArray[0];
		hash*=m;
	};
	hash^=hash>>13;
	hash*=m;
	hash^=hash>>15;
	while(hash>HashTableSize)
		hash/=10;
	return hash;
}
unsigned char CompareCharItems(void* TableItem,void* source,unsigned int ItemSize)
{
	unsigned int i;
	unsigned char* SourceStr=(unsigned char*)source,*TableArray=(unsigned char*)TableItem;	
	for(i=0; i<ItemSize; i++)
		if(SourceStr[i]!=TableArray[i])
			return 0;
	return 1;
}
unsigned char CompareIntItems(void* TableItem,void* source,unsigned int ItemSize)
{
	unsigned int i;
	int *Sourcearray=(int*)source,*TableArray=(int*)TableItem;
	for(i=0; i<ItemSize; i++)
		if(Sourcearray[i]!=TableArray[i])
			return 0;
	return 1;
}
int GetDigitsCount(int n)
{
	int i=0;
	while(n>0)
	{
		n/=10;
		i++;
	}
	return i;
}
void ShowIntArray(void* array,unsigned int size)
{
	unsigned int i,ten;
	int* IntArray=(int*)array;
	int j,MaxDigitsCount=5,CurrentDigitsCount=0,DigitsCountOfNumber;
	for(i=0; i<size && CurrentDigitsCount<MaxDigitsCount-1; i++)
	{
		DigitsCountOfNumber=GetDigitsCount(IntArray[i]);
		printf(" ");
		CurrentDigitsCount++;
		for(ten=1,j=0; j<DigitsCountOfNumber-1; j++)
			ten*=10;
		for(j=0; j<DigitsCountOfNumber && CurrentDigitsCount<MaxDigitsCount; j++)
		{
			printf("%d",(IntArray[i]/ten)%10);
			ten/=10;
			CurrentDigitsCount++;
		}		
	}
	if(i<size)
		printf("...");
	if(CurrentDigitsCount==MaxDigitsCount-1)
		printf(" ");
}
void ShowCharArray(void* array,unsigned int size)
{
	unsigned int i;
	unsigned char* CharArray=(unsigned char*)array;
	int MaxCharsCount=5;
	printf(" ");
	for(i=0; i<MaxCharsCount && i<size; i++)
		printf("%c",CharArray[i]);
	if(i<size)
		printf("...");
}
void* CloneCharArrays(void* source,unsigned int size)
{
	unsigned int i;
	unsigned char* SourceArray=(unsigned char*)source,*array=(unsigned char*)malloc(sizeof(unsigned char)*(size+1));
	for(i=0; i<size; i++)
		array[i]=SourceArray[i];
	array[i]=0;
	return (void*)array;
}
void* CloneIntArrays(void* source,unsigned int size)
{
	unsigned int i;
	int* SourceArray=(int*)source,*array=(int*)malloc(sizeof(int)*size);
	for(i=0; i<size; i++)
		array[i]=SourceArray[i];
	return (void*)array;
}
void SetCursorPosition(int x,int y)
{
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
unsigned char AddItem_SeparateChaining(struct HashTable* ht,unsigned int key,unsigned int HashFunction(void*,unsigned int),void *SourceArray,unsigned int ItemSize,unsigned int ItemsCount,void ShowItem(void*,unsigned int),unsigned int HashTableSize,void* CloneArray(void*,unsigned int))
{
	unsigned char result;
	struct ItemOfTable* iot;
	if(key>=HashTableSize)				
		result=0;
	else
		if(ht->items[key]==NULL)
		{
			ht->items[key]=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
			ht->items[key]->array=CloneArray(SourceArray,ItemSize);
			ht->items[key]->key=key;
			ht->items[key]->ItemSize=ItemSize;
			ht->items[key]->next=NULL;
			result=1;			
		}
		else
			if(ht->items[key]!=NULL)
			{
				iot=ht->items[key];
				while(iot->next!=NULL)
					iot=iot->next;
				iot->next=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
				iot->next->array=CloneArray(SourceArray,ItemSize);
				iot->next->key=key;
				iot->next->ItemSize=ItemSize;
				iot->next->next=NULL;
				result=2;
			}
	if(ItemsCount<100)
	{
		printf("\nThe item ");
		ShowItem(SourceArray,ItemSize);
		if(result==0)
			printf(" NOT ADDED under the key                           %10u",key);
		else
			if(result==1)
				printf(" added ORIGINALLY under the key                    %10u",key);
			else
				printf(" added to the LINKED LIST under the key            %10u",key);
	}
	return result;
}
unsigned char FindItem_SeparateChaining(struct ItemOfTable** HashTableItems,unsigned int key,void ShowItem(void*,unsigned int),unsigned int HashFunction(void*,unsigned int),void *SourceArray,unsigned int ItemSize,unsigned int ItemsCount,unsigned int HashTableSize,unsigned char CompareItems(void*,void*,unsigned int))
{
	unsigned char result=1;
	struct ItemOfTable* iot;
	if(key>=HashTableSize)
		result=0;
	else
	{
		for(iot=HashTableItems[key]; iot!=NULL && CompareItems(iot->array,SourceArray,ItemSize)==0; result=2)
			iot=iot->next;
		if(iot==NULL)
			result=0;
	}
	if(ItemsCount<100)
	{
		printf("\nThe item ");
		ShowItem(SourceArray,ItemSize);
		if(result==0)
			printf(" NOT FOUND under the key                           %10u",key);
		else
			if(result==1)
				printf(" found ORIGINALLY under the key                    %10u",key);
			else
				printf(" found in the LINKED LIST under the key            %10u",key);
	}
	return result;
}
unsigned char RemoveItem_SeparateChaining(struct ItemOfTable** HashTableItems,unsigned int key,void ShowItem(void*,unsigned int),unsigned int HashFunction(void*,unsigned int),void *SourceArray,unsigned int ItemSize,unsigned int ItemsCount,unsigned int HashTableSize,unsigned char CompareItems(void*,void*,unsigned int))
{
	unsigned char result=1;
	struct ItemOfTable* iot,*NextItem;
	if(key>=HashTableSize || HashTableItems[key]==NULL)
		result=0;
	else
		if(CompareItems(SourceArray,HashTableItems[key]->array,ItemSize)==1)
		{
			iot=HashTableItems[key]->next;
			free(HashTableItems[key]->array);
			free(HashTableItems[key]);
			HashTableItems[key]=iot;			
		}
		else
		{
			iot=HashTableItems[key];
			while(iot->next!=NULL && CompareItems(SourceArray,iot->next->array,ItemSize)!=1)
				iot=iot->next;
			if(iot->next!=NULL)
			{				
				NextItem=iot->next->next;
				free(iot->next->array);
				free(iot->next);
				iot->next=NextItem;
				result=2;
			}
			else			
				result=0;
		}
	if(ItemsCount<100)
	{
		printf("\nThe item ");
		ShowItem(SourceArray,ItemSize);
		if(result==0)
			printf(" NOT FOUND under the key                           %10u",key);
		else
			if(result==1)
				printf(" removed ORIGINALLY under the key                  %10u",key);
			else
				if(result==2)
					printf(" removed from the LINKED LIST under the key        %10u",key);
	}
	return result;
}
unsigned char AddItem_OpenAddressing_LinearProbing(struct HashTable* ht,unsigned int key,unsigned int HashFunction(void*,unsigned int),void *SourceArray,unsigned int ItemSize,unsigned int ItemsCount,void ShowItem(void*,unsigned int),unsigned int HashTableSize,void* CloneArray(void*,unsigned int))
{
	unsigned char result=1;
	int i,j;
	if(key>=HashTableSize)
	{
		for(i=HashTableSize-1; i>-1 && ht->items[i]!=NULL; i--);
		if(i==-1)
			result=0;
		else
		{
			ht->items[i]=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
			ht->items[i]->array=CloneArray(SourceArray,ItemSize);
			ht->items[i]->key=key;
			ht->items[i]->ItemSize=ItemSize;
			ht->items[i]->next=NULL;
			result=2;
		}
	}
	else
	{
		for(i=key,j=key+1; i>-1 || j<HashTableSize; i--,j++)
			if(i>-1 && ht->items[i]==NULL)
			{
				ht->items[i]=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
				ht->items[i]->array=CloneArray(SourceArray,ItemSize);
				ht->items[i]->ItemSize=ItemSize;
				ht->items[i]->key=key;
				ht->items[i]->next=NULL;
				break;
			}
			else
				if(j<HashTableSize && ht->items[j]==NULL)
				{
					ht->items[j]=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
					ht->items[j]->array=CloneArray(SourceArray,ItemSize);
					ht->items[j]->key=key;
					ht->items[j]->ItemSize=ItemSize;
					ht->items[j]->next=NULL;
					i=j;
					break;
				}
		if(i<0 && j>=HashTableSize)
			result=0;
		else
			if(i==key)
				result=1;
			else
				result=2;
	}
	if(ItemsCount<100)
	{
		printf("\nThe item");
		ShowItem(SourceArray,ItemSize);
		if(result==0)
			printf(" NOT ADDED under the key                            %10u",key);			
		else
			if(result==1)
				printf(" added ORIGINALLY under the key                     %10u",key);
			else
				printf(" added under the key %10u, hash function key: %10u",i,key);
	}
	return result;
}
unsigned char FindItem_OpenAddressing_LinearProbing(struct ItemOfTable** HashTableItems,unsigned int key,void ShowItem(void*,unsigned int),unsigned int HashFunction(void*,unsigned int),void *SourceArray,unsigned int ItemSize,unsigned int ItemsCount,unsigned int HashTableSize,unsigned char CompareItems(void*,void*,unsigned int))
{
	unsigned char result;
	int i,j;
	if(key>=HashTableSize)
	{
		for(i=HashTableSize-1; i>-1; i--)
			if(HashTableItems[i]!=NULL && CompareItems(HashTableItems[i]->array,SourceArray,ItemSize)==1)
				break;
		if(i==-1)
			result=0;
		else
			result=2;
	}
	else
	{
		for(i=key,j=key+1; i>-1 || j<HashTableSize; i--,j++)
			if(i>-1 && HashTableItems[i]!=NULL && CompareItems(HashTableItems[i]->array,SourceArray,ItemSize)==1)
				break;
		else
			if(j<HashTableSize && HashTableItems[j]!=NULL && CompareItems(HashTableItems[j]->array,SourceArray,ItemSize)==1)
			{
				i=j;
				break;
			}
		if(i<0 && j>=HashTableSize)
			result=0;
		else
			if(i==key)
				result=1;
			else
				result=2;
	}
	if(ItemsCount<100)
	{
		printf("\nThe item");
		ShowItem(SourceArray,ItemSize);
		if(result==0)
			printf(" NOT FOUND under the key                            %10u",key);
		else
			if(result==1)
				printf(" found ORIGINALLY under the key                     %10u",key);
			else
				printf(" found under the key %10u, hash function key: %10u",i,key);
	}
	return result;
}
unsigned char RemoveItem_OpenAddressing_LinearProbing(struct ItemOfTable** HashTableItems,unsigned int key,void ShowItem(void*,unsigned int),unsigned int HashFunction(void*,unsigned int),void *SourceArray,unsigned int ItemSize,unsigned int ItemsCount,unsigned int HashTableSize,unsigned char CompareItems(void*,void*,unsigned int))
{
	unsigned char result=1;
	int i,j,k;
	if(key>=HashTableSize)
	{
		for(i=HashTableSize-1; i>-1; i--)
			if(HashTableItems[i]!=NULL && CompareItems(HashTableItems[i]->array,SourceArray,ItemSize)==1)
			{				
				free(HashTableItems[i]->array);
				free(HashTableItems[i]);
				HashTableItems[i]=NULL;				
				break;
			}
		if(i==-1)
			result=0;
		else
			result=2;
	}
	else
	{
		for(i=key,j=key+1; i>-1 || j<HashTableSize; i--,j++)
			if(i>-1 && HashTableItems[i]!=NULL && CompareItems(HashTableItems[i]->array,SourceArray,ItemSize)==1)
			{
				free(HashTableItems[i]->array);
				free(HashTableItems[i]);
				HashTableItems[i]=NULL;
				break;
			}
			else
				if(j<HashTableSize && HashTableItems[j]!=NULL && CompareItems(HashTableItems[j]->array,SourceArray,ItemSize)==1)
				{
					free(HashTableItems[j]->array);
					free(HashTableItems[j]);
					HashTableItems[j]=NULL;
					i=j;
					break;
				}
		if(i<0 && j>=HashTableSize)
			result=0;
		else
			if(i==key)
				result=1;
			else
				result=2;
	}
	if(ItemsCount<100)
	{
		printf("\nThe item");
		ShowItem(SourceArray,ItemSize);
		if(result==0)
		{
			printf(" NOT FOUND under the key                            %10u",key);
			return 0;
		}
		else
			if(result==1)
				printf(" removed ORIGINALLY under the key                   %10u",key);
			else
				printf(" removed under the key %10u, hash func. key:  %10u",i,key);
		while(result>0)
			for(j=i-1,k=i+1,result=0; j>-1 || k<ItemsCount; j--,k++)
				if(j>-1 && HashTableItems[j]!=NULL && HashTableItems[j]->key==key)
				{
					HashTableItems[i]=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
					HashTableItems[i]->array=HashTableItems[j]->array;
					HashTableItems[i]->key=key;
					HashTableItems[i]->ItemSize=HashTableItems[j]->ItemSize;
					printf("\nThe item");
					ShowItem(HashTableItems[j]->array,ItemSize);
					printf(" relocated from the cell %10u to the cell     %10u",j,i);
					free(HashTableItems[j]);
					HashTableItems[j]=NULL;
					key=j;
					i=j;
					result=1;
					break;
				}
				else
					if(k<ItemsCount && HashTableItems[k]!=NULL && HashTableItems[k]->key==key)
					{
						HashTableItems[i]=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
						HashTableItems[i]->array=HashTableItems[k]->array;
						HashTableItems[i]->key=key;
						HashTableItems[i]->ItemSize=HashTableItems[k]->ItemSize;
						printf("\nThe item");
						ShowItem(HashTableItems[k]->array,ItemSize);
						printf(" relocated from the cell %10u to the cell     %10u",k,i);
						free(HashTableItems[k]);
						HashTableItems[k]=NULL;
						key=k;
						i=k;
						result=1;
						break;
					}
	}
	else
	{
		if(result==0)
			return 0;
		while(result>0)
			for(j=i-1,k=i+1,result=0; j>-1 || k<ItemsCount; j--,k++)
				if(j>-1 && HashTableItems[j]!=NULL && HashTableItems[j]->key==key)
				{
					HashTableItems[i]=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
					HashTableItems[i]->array=HashTableItems[j]->array;
					HashTableItems[i]->key=key;
					HashTableItems[i]->ItemSize=HashTableItems[j]->ItemSize;
					free(HashTableItems[j]);
					HashTableItems[j]=NULL;
					key=j;
					i=j;
					result=2;
					break;
				}
				else
					if(k<ItemsCount && k<HashTableSize && HashTableItems[k]!=NULL && HashTableItems[k]->key==key)
					{
						HashTableItems[i]=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
						HashTableItems[i]->array=HashTableItems[k]->array;
						HashTableItems[i]->key=key;
						HashTableItems[i]->ItemSize=HashTableItems[k]->ItemSize;
						free(HashTableItems[k]);
						HashTableItems[k]=NULL;
						key=k;
						i=k;
						result=2;
						break;
					}
	}
	return 1;
}
unsigned char AddItem_OpenAddressing_DoubleHashing(struct HashTable* ht,unsigned int key,unsigned int HashFunction(void*,unsigned int),void *SourceArray,unsigned int ItemSize,unsigned int ItemsCount,void ShowItem(void*,unsigned int),unsigned int HashTableSize,void* CloneArray(void*,unsigned int))
{
	unsigned char result=1;
	unsigned int i,j,key2,NewKey;
	if(key<HashTableSize && ht->items[key]==NULL)
	{
		ht->items[key]=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
		ht->items[key]->array=CloneArray(SourceArray,ItemSize);
		ht->items[key]->ItemSize=ItemSize;
		ht->items[key]->key=key;
		ht->items[key]->next=NULL;
	}
	else
	{
		key2=HashFunction(SourceArray,ItemSize);
		for(i=0; i<HashTableSize; i++)
		{
			NewKey=(key+i*key2)%HashTableSize;
			if(NewKey<HashTableSize && ht->items[NewKey]==NULL)
			{
				ht->items[NewKey]=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
				ht->items[NewKey]->array=CloneArray(SourceArray,ItemSize);
				ht->items[NewKey]->ItemSize=ItemSize;
				ht->items[NewKey]->key=key;
				ht->items[NewKey]->next=NULL;
				result=2;
				break;
			}
		}
		if(result==1)
			result=0;
	}
	if(ItemsCount<100)
	{
		printf("\nThe item");
		ShowItem(SourceArray,ItemSize);
		if(result==0)
			printf(" NOT ADDED under the key                            %10u",key);			
		else
			if(result==1)
				printf(" added ORIGINALLY under the key                     %10u",key);
			else
				printf(" added under the key %10u, hash function key: %10u",NewKey,key);
	}
	return result;
}
unsigned char FindItem_OpenAddressing_DoubleHashing(struct ItemOfTable** HashTableItems,unsigned int key,void ShowItem(void*,unsigned int),unsigned int HashFunction(void*,unsigned int),void *SourceArray,unsigned int ItemSize,unsigned int ItemsCount,unsigned int HashTableSize,unsigned char CompareItems(void*,void*,unsigned int))
{
	unsigned char result=1;
	unsigned int i,j,key2,NewKey;	
	if(key<HashTableSize && HashTableItems[key]==NULL)
		result=0;
	else
		if(key<HashTableSize && HashTableItems[key]!=NULL && CompareItems(HashTableItems[key]->array,SourceArray,ItemSize)==1)
			result=1;
		else
		{
			key2=HashFunction(SourceArray,ItemSize);
			for(i=0; i<HashTableSize; i++)
			{
				NewKey=(key+i*key2)%HashTableSize;
				if(NewKey<HashTableSize && HashTableItems[NewKey]!=NULL && CompareItems(HashTableItems[NewKey]->array,SourceArray,ItemSize)==1)
				{
					result=2;
					break;
				}
			}
			if(result==1)
				result=0;
		}
	if(ItemsCount<100)
	{
		printf("\nThe item");
		ShowItem(SourceArray,ItemSize);
		if(result==0)
			printf(" NOT FOUND under the key                            %10u",key);
		else
			if(result==1)
				printf(" found ORIGINALLY under the key                     %10u",key);
			else
				printf(" found under the key %10u, hash function key: %10u",NewKey,key);
	}
	return result;
}
unsigned char RemoveItem_OpenAddressing_DoubleHashing(struct ItemOfTable** HashTableItems,unsigned int key,void ShowItem(void*,unsigned int),unsigned int HashFunction(void*,unsigned int),void *SourceArray,unsigned int ItemSize,unsigned int ItemsCount,unsigned int HashTableSize,unsigned char CompareItems(void*,void*,unsigned int))
{
	unsigned char result=1;
	unsigned int i,j,key2,NewKey;	
	if(key<HashTableSize && HashTableItems[key]==NULL)
		result=0;
	else
		if(key<HashTableSize && HashTableItems[key]!=NULL && CompareItems(HashTableItems[key]->array,SourceArray,ItemSize)==1)
			result=1;
		else
		{
			key2=HashFunction(SourceArray,ItemSize);
			for(i=0; i<HashTableSize; i++)
			{
				NewKey=(key+i*key2)%HashTableSize;
				if(NewKey<HashTableSize && HashTableItems[NewKey]!=NULL && CompareItems(HashTableItems[NewKey]->array,SourceArray,ItemSize)==1)
				{
					free(HashTableItems[NewKey]->array);
					free(HashTableItems[NewKey]);
					HashTableItems[NewKey]=NULL;
					result=2;					
					break;
				}
			}
			if(result==1)
				result=0;
		}
	if(ItemsCount<100)
	{
		printf("\nThe item");
		ShowItem(SourceArray,ItemSize);
		if(result==0)
		{
			printf(" NOT FOUND under the key                            %10u",key);
			return 0;
		}
		else
			if(result==1)
				printf(" removed ORIGINALLY under the key                   %10u",key);
			else
				printf(" removed under the key %10u, hash func. key:  %10u",NewKey,key);
		while(result>0)
			for(i=0,result=0; i<HashTableSize; i++)
				if(HashTableItems[i]!=NULL && HashTableItems[i]->key==NewKey)
				{
					HashTableItems[NewKey]=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
					HashTableItems[NewKey]->array=HashTableItems[i]->array;
					HashTableItems[NewKey]->key=NewKey;
					HashTableItems[NewKey]->ItemSize=HashTableItems[i]->ItemSize;
					printf("\nThe item");
					ShowItem(HashTableItems[i]->array,ItemSize);
					printf(" relocated from the cell %10u to the cell     %10u",i,NewKey);
					free(HashTableItems[i]);
					HashTableItems[i]=NULL;
					result=1;
					NewKey=i;
					break;
				}
	}
	else
	{
		if(result==0)
			return 0;
		while(result>0)
			for(i=0,result=0; i<HashTableSize; i++)
				if(HashTableItems[i]!=NULL && HashTableItems[i]->key==NewKey)
				{
					HashTableItems[NewKey]=(struct ItemOfTable*)malloc(sizeof(struct ItemOfTable));
					HashTableItems[NewKey]->array=HashTableItems[i]->array;
					HashTableItems[NewKey]->key=NewKey;
					HashTableItems[NewKey]->ItemSize=HashTableItems[i]->ItemSize;
					free(HashTableItems[i]);
					HashTableItems[i]=NULL;
					result=1;
					NewKey=i;
					break;
				}
	}
	return 1;
}
void TestHashTable(void **SourceArrays,unsigned int ItemsCount,unsigned int ItemSize,unsigned int HashTableSize,unsigned int HashFunction(void*,unsigned int),unsigned int HashFunction2(void*,unsigned int),unsigned char CompareItems(void*,void*,unsigned int),void* CloneArray(void*,unsigned int),void ShowItem(void*,unsigned int),unsigned char AddItem(struct HashTable*,unsigned int,unsigned int(void*,unsigned int),void*,unsigned int,unsigned int,void(void*,unsigned int),unsigned int,void*(void*,unsigned int)),unsigned char FindItem(struct ItemOfTable**,unsigned int,void(void*,unsigned int),unsigned int(void*,unsigned int),void*,unsigned int,unsigned int,unsigned int,unsigned char(void*,void*,unsigned int)),unsigned char RemoveItem(struct ItemOfTable**,unsigned int,void(void*,unsigned int),unsigned int(void*,unsigned int),void*,unsigned int,unsigned int,unsigned int,unsigned char(void*,void*,unsigned int)))
{
	unsigned char OperationResult;
	int i,j;
	unsigned int key,NotAddedItemsCount=0,CollisionsCount=0;
	struct ItemOfTable* iot,*temp;
	struct HashTable* ht;
	//CONSOLE_SCREEN_BUFFER_INFO CursorPos1,CursorPos2;
	DWORD StartTimeMsec,EndTimeMsec,OneItemStartTimeMsec,OneItemEndTimeMsec,AverageTimeMSec=0;
	time_t StartTime,EndTime;
	printf("Adding items to the hash table...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	ht=(struct HashTable*)malloc(sizeof(struct HashTable));
	ht->items=(struct ItemOfTable**)calloc(sizeof(struct ItemOfTable*),HashTableSize);
	ht->ItemsCount=0;
	for(i=0; i<ItemsCount; i++)
	{
		OneItemStartTimeMsec=GetTickCount();
		key=HashFunction(SourceArrays[i],ItemSize);
		OperationResult=AddItem(ht,key,HashFunction2,SourceArrays[i],ItemSize,ItemsCount,ShowItem,HashTableSize,CloneArray);
		OneItemEndTimeMsec=GetTickCount()-OneItemStartTimeMsec;
		AverageTimeMSec+=OneItemEndTimeMsec;
		if(OperationResult==0)
			NotAddedItemsCount++;
		else
			if(OperationResult==2)
				CollisionsCount++;
	}
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	AverageTimeMSec/=ItemsCount;
	ht->ItemsCount=ItemsCount-NotAddedItemsCount;
	printf("\n--------------------------------------------------------------------------------");
	printf("%36s: %20u;\n","Count of collisions",CollisionsCount);
	printf("%36s: %20u;\n","Count of added items",ht->ItemsCount);
	printf("%36s: %20u;\n","Count of not added items",NotAddedItemsCount);
	printf("%36s: %5d sec = %5d ms;\n","Time of adding of ALL items",EndTime,EndTimeMsec);	
	printf("%36s: %17d ms;\n","Average time of adding of ONE item",AverageTimeMSec);
	printf("--------------------------------------------------------------------------------");	
	fprintf(tests,"%11u%11u%11u%11u%11u",CollisionsCount,ht->ItemsCount,NotAddedItemsCount,EndTimeMsec,AverageTimeMSec);	
	AverageTimeMSec=0;
	CollisionsCount=0;
	NotAddedItemsCount=0;
	printf("Searching items in the hash table...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	for(i=0; i<ItemsCount; i++)
	{
		OneItemStartTimeMsec=GetTickCount();
		key=HashFunction(SourceArrays[i],ItemSize);
		OperationResult=FindItem(ht->items,key,ShowItem,HashFunction2,SourceArrays[i],ItemSize,ItemsCount,HashTableSize,CompareItems);
		OneItemEndTimeMsec=GetTickCount()-OneItemStartTimeMsec;
		AverageTimeMSec+=OneItemEndTimeMsec;
		if(OperationResult==0)
			NotAddedItemsCount++;
		else
			if(OperationResult==2)
				CollisionsCount++;
	}
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	AverageTimeMSec/=ItemsCount;
	printf("\n--------------------------------------------------------------------------------");
	printf("%36s: %20u;\n","Count of collisions",CollisionsCount);
	printf("%36s: %20u;\n","Count of found items",ItemsCount-NotAddedItemsCount);
	printf("%36s: %20u;\n","Count of not found items",NotAddedItemsCount);
	printf("%36s: %5d sec = %5d ms;\n","Time of search of ALL items",EndTime,EndTimeMsec);	
	printf("%36s: %17d ms;\n","Average time of search of ONE item",AverageTimeMSec);
	printf("--------------------------------------------------------------------------------");	
	fprintf(tests,"%11u%11u",EndTimeMsec,AverageTimeMSec);	
	CollisionsCount=0;
	AverageTimeMSec=0;
	NotAddedItemsCount=0;
	printf("Removing of all items from the hash table...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	for(i=ItemsCount-1; i>-1; i--)
	{
		OneItemStartTimeMsec=GetTickCount();
		key=HashFunction(SourceArrays[i],ItemSize);
		OperationResult=RemoveItem(ht->items,key,ShowItem,HashFunction2,SourceArrays[i],ItemSize,ItemsCount,HashTableSize,CompareItems);
		OneItemEndTimeMsec=GetTickCount()-OneItemStartTimeMsec;
		AverageTimeMSec+=OneItemEndTimeMsec;
		if(OperationResult==0)
			NotAddedItemsCount++;				
		else
			CollisionsCount++;
	}
	free(ht->items);
	free(ht);
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	AverageTimeMSec/=ItemsCount;	
	printf("\n--------------------------------------------------------------------------------");
	printf("%36s: %20u;\n","Count of removed items",CollisionsCount);
	printf("%36s: %20u;\n","Count of not found items",NotAddedItemsCount);
	printf("%36s: %5d sec = %5d ms;\n","Time of removing of ALL items",EndTime,EndTimeMsec);
	printf("%36s: %17d ms;\n","Average time of removing of ONE item",AverageTimeMSec);
	fprintf(tests,"%11u%11u\n",EndTimeMsec,AverageTimeMSec);
	//GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorPos2);
	//SetCursorPosition(CursorPos1.dwCursorPosition.X,CursorPos1.dwCursorPosition.Y);
	//printf("    Time:                           %5d;\n",EndTime);
	//SetCursorPosition(CursorPos2.dwCursorPosition.X+1,CursorPos2.dwCursorPosition.Y);
}
int main(void)
{	
	unsigned int i,j,ItemsCount=10000,ItemSize=100;
	int **IntArray,MinNumber=1,MaxNumber=SHRT_MAX;
	unsigned char **CharArray;
	HashTableSize=10000;
	tests=fopen("tests.txt","w");
	srand(time(0));
	printf("Preparing arrays of random chars...");
	CharArray=(unsigned char**)malloc(sizeof(unsigned char*)*ItemsCount);
	for(i=0; i<ItemsCount; i++)
	{
		CharArray[i]=(unsigned char*)malloc(sizeof(unsigned char)*ItemSize+1);
		for(j=0; j<ItemSize; j++)
			CharArray[i][j]='0'+rand()%('z'-'0');
		CharArray[i][j]=0;
	}
	printf(" Done.\n");
	printf("DATA TYPE:                                  %17s;\n","array of chars");
	printf("SIZE OF ONE ITEM:                           %17u;\n",ItemSize);
	printf("SIZE OF THE HASH TABLE:                     %17u;\n",HashTableSize);
	printf("COUNT OF ITEMS IN THE HASH TABLE:           %17u;\n",ItemsCount);	
	fprintf(tests,"HASH FUNCTIONS AND METHODS OF COLLISION RESOLUTION:\nSEPARATE CHAINING: SUM OF EVENNESS AND THE LAST DIGIT\nSEPARATE CHAINING: AVERAGE SUM OF NUMBER AND INDEX\nSEPARATE CHAINING: MURMURHASH 2\nOPEN ADDRESSING: LINEAR PROBING: SUM OF EVENNESS AND THE LAST DIGIT\nOPEN ADDRESSING: LINEAR PROBING: AVERAGE SUM OF NUMBER AND INDEX\nOPEN ADDRESSING: LINEAR PROBING: MURMURHASH 2\nOPEN ADDRESSING: DOUBLE HASHING: SUM OF EVENNESS AND THE LAST DIGIT, AVERAGE SUM OF NUMBER AND INDEX\nOPEN ADDRESSING: DOUBLE HASHING: AVERAGE SUM OF NUMBER AND INDEX, SUM OF EVENNESS AND THE LAST DIGIT\nOPEN ADDRESSING: DOUBLE HASHING: MURMURHASH 2, AVERAGE SUM OF NUMBER AND INDEX\nOPEN ADDRESSING: DOUBLE HASHING: AVERAGE SUM OF NUMBER AND INDEX, MURMURHASH 2\nOPEN ADDRESSING: DOUBLE HASHING: MURMURHASH 2, SUM OF EVENNESS AND THE LAST DIGIT\nOPEN ADDRESSING: DOUBLE HASHING: SUM OF EVENNESS AND THE LAST DIGIT, MURMURHASH 2\nTITLES OF COLUMNS\nCOUNT OF COLLISIONS\nCOUNT OF FOUND ITEMS\nCOUNT OF NOT FOUND ITEMS\nTIME OF ADDING OF ALL ITEMS\nAVERAGE TIME OF ADDING OF ONE ITEM\nTIME OF SEARCH OF ALL ITEMS\nAVERAGE TIME OF SEARCH OF ONE ITEM\nTIME OF REMOVING OF ALL ITEMS\nAVERAGE TIME OF REMOVING OF ONE ITEM\n");
	fprintf(tests,"___________________________________________________________________________________________________\n");
	fprintf(tests,"DATA TYPE:                                  %17s;\n","array of chars");
	fprintf(tests,"SIZE OF ONE ITEM:                           %17u;\n",ItemSize);
	fprintf(tests,"SIZE OF THE HASH TABLE:                     %17u;\n",HashTableSize);
	fprintf(tests,"COUNT OF ITEMS IN THE HASH TABLE:           %17u;\n",ItemsCount);
	fprintf(tests,"___________________________________________________________________________________________________\n");
	fprintf(tests,"%11s%11s%11s%11s%11s%11s%11s%11s%11s\n","COC","COFI","CONFI","TOAOAI","ATOAOOI","TOSOAI","ATOSOOI","TOROAI","ATOROOI");
	printf("================================================================================");
	printf("METHOD OF COLLISION RESOLUTION:                                SEPARATE CHAINING");
	printf("================================================================================");
	printf("HASH FUNCTION:                                SUM OF EVENNESS AND THE LAST DIGIT");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)CharArray,ItemsCount,ItemSize,HashTableSize,SumOfEvennessAndTheLastDigit_Char,NULL,CompareCharItems,CloneCharArrays,ShowCharArray,AddItem_SeparateChaining,FindItem_SeparateChaining,RemoveItem_SeparateChaining);
	printf("--------------------------------------------------------------------------------");
	printf("HASH FUNCTION:                                   AVERAGE SUM OF NUMBER AND INDEX");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)CharArray,ItemsCount,ItemSize,HashTableSize,AverageSumOfNumberAndIndex_Char,NULL,CompareCharItems,CloneCharArrays,ShowCharArray,AddItem_SeparateChaining,FindItem_SeparateChaining,RemoveItem_SeparateChaining);
	printf("--------------------------------------------------------------------------------");
	printf("HASH FUNCTION:                                                      MURMURHASH 2");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)CharArray,ItemsCount,ItemSize,HashTableSize,MurmurHash2_Char,NULL,CompareCharItems,CloneCharArrays,ShowCharArray,AddItem_SeparateChaining,FindItem_SeparateChaining,RemoveItem_SeparateChaining);
	printf("================================================================================");
	printf("METHOD OF COLLISION RESOLUTION:                  OPEN ADDRESSING: LINEAR PROBING");
	printf("================================================================================");
	printf("HASH FUNCTION:                                SUM OF EVENNESS AND THE LAST DIGIT");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)CharArray,ItemsCount,ItemSize,HashTableSize,SumOfEvennessAndTheLastDigit_Char,NULL,CompareCharItems,CloneCharArrays,ShowCharArray,AddItem_OpenAddressing_LinearProbing,FindItem_OpenAddressing_LinearProbing,RemoveItem_OpenAddressing_LinearProbing);
	printf("--------------------------------------------------------------------------------");
	printf("HASH FUNCTION:                                   AVERAGE SUM OF NUMBER AND INDEX");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)CharArray,ItemsCount,ItemSize,HashTableSize,AverageSumOfNumberAndIndex_Char,NULL,CompareCharItems,CloneCharArrays,ShowCharArray,AddItem_OpenAddressing_LinearProbing,FindItem_OpenAddressing_LinearProbing,RemoveItem_OpenAddressing_LinearProbing);
	printf("--------------------------------------------------------------------------------");
	printf("HASH FUNCTION:                                                      MURMURHASH 2");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)CharArray,ItemsCount,ItemSize,HashTableSize,MurmurHash2_Char,NULL,CompareCharItems,CloneCharArrays,ShowCharArray,AddItem_OpenAddressing_LinearProbing,FindItem_OpenAddressing_LinearProbing,RemoveItem_OpenAddressing_LinearProbing);
	printf("================================================================================");
	printf("METHOD OF COLLISION RESOLUTION:                  OPEN ADDRESSING: DOUBLE HASHING");
	printf("================================================================================");
	printf("MAIN HASH FUNCTION:                           SUM OF EVENNESS AND THE LAST DIGIT");
	printf("ADDITIONAL HASH FUNCTION:                        AVERAGE SUM OF NUMBER AND INDEX");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)CharArray,ItemsCount,ItemSize,HashTableSize,SumOfEvennessAndTheLastDigit_Char,AverageSumOfNumberAndIndex_Char,CompareCharItems,CloneCharArrays,ShowCharArray,AddItem_OpenAddressing_DoubleHashing,FindItem_OpenAddressing_DoubleHashing,RemoveItem_OpenAddressing_DoubleHashing);
	printf("--------------------------------------------------------------------------------");
	printf("MAIN HASH FUNCTION:                              AVERAGE SUM OF NUMBER AND INDEX");
	printf("ADDITIONAL HASH FUNCTION:                     SUM OF EVENNESS AND THE LAST DIGIT");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)CharArray,ItemsCount,ItemSize,HashTableSize,AverageSumOfNumberAndIndex_Char,SumOfEvennessAndTheLastDigit_Char,CompareCharItems,CloneCharArrays,ShowCharArray,AddItem_OpenAddressing_DoubleHashing,FindItem_OpenAddressing_DoubleHashing,RemoveItem_OpenAddressing_DoubleHashing);	
	printf("--------------------------------------------------------------------------------");
	printf("MAIN HASH FUNCTION:                                                 MURMURHASH 2");
	printf("ADDITIONAL HASH FUNCTION:                        AVERAGE SUM OF NUMBER AND INDEX");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)CharArray,ItemsCount,ItemSize,HashTableSize,MurmurHash2_Char,AverageSumOfNumberAndIndex_Char,CompareCharItems,CloneCharArrays,ShowCharArray,AddItem_OpenAddressing_DoubleHashing,FindItem_OpenAddressing_DoubleHashing,RemoveItem_OpenAddressing_DoubleHashing);
	printf("--------------------------------------------------------------------------------");
	printf("MAIN HASH FUNCTION:                              AVERAGE SUM OF NUMBER AND INDEX");
	printf("ADDITIONAL HASH FUNCTION:                                           MURMURHASH 2");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)CharArray,ItemsCount,ItemSize,HashTableSize,AverageSumOfNumberAndIndex_Char,MurmurHash2_Char,CompareCharItems,CloneCharArrays,ShowCharArray,AddItem_OpenAddressing_DoubleHashing,FindItem_OpenAddressing_DoubleHashing,RemoveItem_OpenAddressing_DoubleHashing);	
	printf("--------------------------------------------------------------------------------");
	printf("MAIN HASH FUNCTION:                                                 MURMURHASH 2");
	printf("ADDITIONAL HASH FUNCTION:                     SUM OF EVENNESS AND THE LAST DIGIT");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)CharArray,ItemsCount,ItemSize,HashTableSize,MurmurHash2_Char,SumOfEvennessAndTheLastDigit_Char,CompareCharItems,CloneCharArrays,ShowCharArray,AddItem_OpenAddressing_DoubleHashing,FindItem_OpenAddressing_DoubleHashing,RemoveItem_OpenAddressing_DoubleHashing);
	printf("--------------------------------------------------------------------------------");
	printf("MAIN HASH FUNCTION:                           SUM OF EVENNESS AND THE LAST DIGIT");
	printf("ADDITIONAL HASH FUNCTION:                                           MURMURHASH 2");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)CharArray,ItemsCount,ItemSize,HashTableSize,SumOfEvennessAndTheLastDigit_Char,MurmurHash2_Char,CompareCharItems,CloneCharArrays,ShowCharArray,AddItem_OpenAddressing_DoubleHashing,FindItem_OpenAddressing_DoubleHashing,RemoveItem_OpenAddressing_DoubleHashing);
	printf("Cleaning of array memory...");
	for(i=0; i<ItemsCount; i++)
		free(CharArray[i]);
	free(CharArray);
	printf(" Done.\n");
	printf("================================================================================");
	printf("Preparing arrays of random integers...");
	IntArray=(int**)malloc(sizeof(int*)*ItemsCount);	
	for(i=0; i<ItemsCount; i++)
	{
		IntArray[i]=(int*)malloc(sizeof(int)*ItemSize+1);
		for(j=0; j<ItemSize; j++)
			IntArray[i][j]=MinNumber+rand()%(MaxNumber-MinNumber);		
	}
	printf(" Done.\n");
	printf("DATA TYPE:                                  %17s;\n","array of integers");
	printf("SIZE OF ONE ITEM:                           %17u;\n",ItemSize);
	printf("SIZE OF THE HASH TABLE:                     %17u;\n",HashTableSize);
	printf("COUNT OF ITEMS IN THE HASH TABLE:           %17u;\n",ItemsCount);
	fprintf(tests,"___________________________________________________________________________________________________\n");
	fprintf(tests,"DATA TYPE:                                  %17s;\n","array of integers");
	fprintf(tests,"SIZE OF ONE ITEM:                           %17u;\n",ItemSize);
	fprintf(tests,"SIZE OF THE HASH TABLE:                     %17u;\n",HashTableSize);
	fprintf(tests,"COUNT OF ITEMS IN THE HASH TABLE:           %17u;\n",ItemsCount);
	fprintf(tests,"___________________________________________________________________________________________________\n");
	fprintf(tests,"%11s%11s%11s%11s%11s%11s%11s%11s%11s\n","COC","COFI","CONFI","TOAOAI","ATOAOOI","TOSOAI","ATOSOOI","TOROAI","ATOROOI");
	printf("================================================================================");
	printf("METHOD OF COLLISION RESOLUTION:                                SEPARATE CHAINING");
	printf("================================================================================");
	printf("HASH FUNCTION:                                SUM OF EVENNESS AND THE LAST DIGIT");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)IntArray,ItemsCount,ItemSize,HashTableSize,SumOfEvennessAndTheLastDigit_Int,NULL,CompareCharItems,CloneIntArrays,ShowIntArray,AddItem_SeparateChaining,FindItem_SeparateChaining,RemoveItem_SeparateChaining);
	printf("--------------------------------------------------------------------------------");
	printf("HASH FUNCTION:                                   AVERAGE SUM OF NUMBER AND INDEX");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)IntArray,ItemsCount,ItemSize,HashTableSize,AverageSumOfNumberAndIndex_Int,NULL,CompareCharItems,CloneIntArrays,ShowIntArray,AddItem_SeparateChaining,FindItem_SeparateChaining,RemoveItem_SeparateChaining);
	printf("--------------------------------------------------------------------------------");
	printf("HASH FUNCTION:                                                      MURMURHASH 2");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)IntArray,ItemsCount,ItemSize,HashTableSize,MurmurHash2_Int,NULL,CompareCharItems,CloneIntArrays,ShowIntArray,AddItem_SeparateChaining,FindItem_SeparateChaining,RemoveItem_SeparateChaining);
	printf("================================================================================");
	printf("METHOD OF COLLISION RESOLUTION:                  OPEN ADDRESSING: LINEAR PROBING");
	printf("================================================================================");
	printf("HASH FUNCTION:                                SUM OF EVENNESS AND THE LAST DIGIT");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)IntArray,ItemsCount,ItemSize,HashTableSize,SumOfEvennessAndTheLastDigit_Int,NULL,CompareCharItems,CloneIntArrays,ShowIntArray,AddItem_OpenAddressing_LinearProbing,FindItem_OpenAddressing_LinearProbing,RemoveItem_OpenAddressing_LinearProbing);
	printf("--------------------------------------------------------------------------------");
	printf("HASH FUNCTION:                                   AVERAGE SUM OF NUMBER AND INDEX");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)IntArray,ItemsCount,ItemSize,HashTableSize,AverageSumOfNumberAndIndex_Int,NULL,CompareCharItems,CloneIntArrays,ShowIntArray,AddItem_OpenAddressing_LinearProbing,FindItem_OpenAddressing_LinearProbing,RemoveItem_OpenAddressing_LinearProbing);
	printf("--------------------------------------------------------------------------------");
	printf("HASH FUNCTION:                                                      MURMURHASH 2");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)IntArray,ItemsCount,ItemSize,HashTableSize,MurmurHash2_Int,NULL,CompareCharItems,CloneIntArrays,ShowIntArray,AddItem_OpenAddressing_LinearProbing,FindItem_OpenAddressing_LinearProbing,RemoveItem_OpenAddressing_LinearProbing);
	printf("================================================================================");
	printf("METHOD OF COLLISION RESOLUTION:                  OPEN ADDRESSING: DOUBLE HASHING");
	printf("================================================================================");
	printf("MAIN HASH FUNCTION:                           SUM OF EVENNESS AND THE LAST DIGIT");
	printf("ADDITIONAL HASH FUNCTION:                        AVERAGE SUM OF NUMBER AND INDEX");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)IntArray,ItemsCount,ItemSize,HashTableSize,SumOfEvennessAndTheLastDigit_Int,AverageSumOfNumberAndIndex_Int,CompareCharItems,CloneIntArrays,ShowIntArray,AddItem_OpenAddressing_DoubleHashing,FindItem_OpenAddressing_DoubleHashing,RemoveItem_OpenAddressing_DoubleHashing);
	printf("--------------------------------------------------------------------------------");
	printf("MAIN HASH FUNCTION:                              AVERAGE SUM OF NUMBER AND INDEX");
	printf("ADDITIONAL HASH FUNCTION:                     SUM OF EVENNESS AND THE LAST DIGIT");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)IntArray,ItemsCount,ItemSize,HashTableSize,AverageSumOfNumberAndIndex_Int,SumOfEvennessAndTheLastDigit_Int,CompareCharItems,CloneIntArrays,ShowIntArray,AddItem_OpenAddressing_DoubleHashing,FindItem_OpenAddressing_DoubleHashing,RemoveItem_OpenAddressing_DoubleHashing);
	printf("--------------------------------------------------------------------------------");
	printf("MAIN HASH FUNCTION:                                                 MURMURHASH 2");
	printf("ADDITIONAL HASH FUNCTION:                        AVERAGE SUM OF NUMBER AND INDEX");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)IntArray,ItemsCount,ItemSize,HashTableSize,MurmurHash2_Int,AverageSumOfNumberAndIndex_Int,CompareCharItems,CloneIntArrays,ShowIntArray,AddItem_OpenAddressing_DoubleHashing,FindItem_OpenAddressing_DoubleHashing,RemoveItem_OpenAddressing_DoubleHashing);
	printf("--------------------------------------------------------------------------------");
	printf("MAIN HASH FUNCTION:                              AVERAGE SUM OF NUMBER AND INDEX");
	printf("ADDITIONAL HASH FUNCTION:                                           MURMURHASH 2");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)IntArray,ItemsCount,ItemSize,HashTableSize,AverageSumOfNumberAndIndex_Int,MurmurHash2_Int,CompareCharItems,CloneIntArrays,ShowIntArray,AddItem_OpenAddressing_DoubleHashing,FindItem_OpenAddressing_DoubleHashing,RemoveItem_OpenAddressing_DoubleHashing);	
	printf("--------------------------------------------------------------------------------");
	printf("MAIN HASH FUNCTION:                                                 MURMURHASH 2");
	printf("ADDITIONAL HASH FUNCTION:                     SUM OF EVENNESS AND THE LAST DIGIT");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)IntArray,ItemsCount,ItemSize,HashTableSize,MurmurHash2_Int,SumOfEvennessAndTheLastDigit_Int,CompareCharItems,CloneIntArrays,ShowIntArray,AddItem_OpenAddressing_DoubleHashing,FindItem_OpenAddressing_DoubleHashing,RemoveItem_OpenAddressing_DoubleHashing);
	printf("--------------------------------------------------------------------------------");
	printf("MAIN HASH FUNCTION:                           SUM OF EVENNESS AND THE LAST DIGIT");
	printf("ADDITIONAL HASH FUNCTION:                                           MURMURHASH 2");
	printf("--------------------------------------------------------------------------------");
	TestHashTable((void**)IntArray,ItemsCount,ItemSize,HashTableSize,SumOfEvennessAndTheLastDigit_Int,MurmurHash2_Int,CompareCharItems,CloneIntArrays,ShowIntArray,AddItem_OpenAddressing_DoubleHashing,FindItem_OpenAddressing_DoubleHashing,RemoveItem_OpenAddressing_DoubleHashing);
	printf("Cleaning of array memory...");
	for(i=0; i<ItemsCount; i++)
		free(IntArray[i]);
	free(IntArray);
	fclose(tests);
	printf(" Done.\n");
	printf("================================================================================");
	return 0;
}
