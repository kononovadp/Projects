#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
int main(void)
{
	struct QueuePointersStruct
	{
		int data;
		struct QueuePointersStruct *prev,*next;
	};
	struct DoubleLinkedListStruct
	{
		int data;
		struct DoubleLinkedListStruct *prev,*next;
	};
	struct QueuePointersStruct *QueuePointers,*QueueTailPointers;
	struct DoubleLinkedListStruct *DoubleLinkedList,*DoubleLinkedListTail;
	int i,ArraySize=50000000,*array,MinNumber=1,MaxNumber=ArraySize;
	int j,ten,MaxDigitsCount=76,CurrentDigitsCount,DigitsCountOfNumber;
	int *QueueArray,QueueArrayTail,*DoubleLinkedListArray,DoubleLinkedListPrev,DoubleLinkedListNext;
	time_t StartTime,EndTime;
	DWORD StartTimeMsec,EndTimeMsec;
	FILE *TestFile=fopen("tests.txt","w");
	srand(time(0));
	printf("DATA TYPE:                %17s;\n","int");
	printf("SIZE OF ARRAY:            %17d;\n",ArraySize);
	printf("MINIMUM NUMBER:           %17d;\n",MinNumber);
	printf("MAXIMUM NUMBER:           %17d;\n",MaxNumber);
	printf("================================================================================");
	fprintf(TestFile,"DATA TYPE:                %17s;\n","int");
	fprintf(TestFile,"SIZE OF ARRAY:            %17d;\n",ArraySize);
	fprintf(TestFile,"MINIMUM NUMBER:           %17d;\n",MinNumber);
	fprintf(TestFile,"MAXIMUM NUMBER:           %17d;\n",MaxNumber);
	fprintf(TestFile,"================================================================================\n");
	fprintf(TestFile,"%44s %16s\n","Time of adding","Time of removing");
	printf("Building of an ARRAY...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();	
	array=(int*)malloc(sizeof(int)*ArraySize);
	for(i=0; i<ArraySize; i++)
		array[i]=MinNumber+rand()%(MaxNumber-MinNumber);	
	EndTimeMsec=GetTickCount();
	EndTime=time(&EndTime);
	printf(" Time: %d ms = %d sec. Last elements:\n",EndTimeMsec-StartTimeMsec,EndTime-StartTime);
	for(i=ArraySize-1,CurrentDigitsCount=0; i>-1 && CurrentDigitsCount<MaxDigitsCount-1; i--)
	{
		if(array[i]==0)
			DigitsCountOfNumber=1;
		else
		{
			ten=array[i];
			DigitsCountOfNumber=0;
			while(ten>0)
			{
				ten/=10;
				DigitsCountOfNumber++;
			}
		}
		printf(" ");
		CurrentDigitsCount++;
		for(ten=1,j=0; j<DigitsCountOfNumber-1; j++)
			ten*=10;
		for(j=0; j<DigitsCountOfNumber && CurrentDigitsCount<MaxDigitsCount; j++)
		{
			printf("%d",(array[i]/ten)%10);
			ten/=10;
			CurrentDigitsCount++;
		}		
	}
	if(i>0)
		printf("...");
	printf("\n--------------------------------------------------------------------------------");
	//------------------------------------QUEUE (ARRAY)------------------------------------
	printf("Building of a QUEUE (ARRAY)...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();	
	QueueArray=(int*)malloc(sizeof(int)*ArraySize);
	for(i=0,QueueArrayTail=0; i<ArraySize; i++,QueueArrayTail++)
		QueueArray[QueueArrayTail]=array[i];
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %d ms = %d sec. Items of queue:\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%30s%14d","Queue (array)",EndTimeMsec);	
	for(QueueArrayTail--,CurrentDigitsCount=0; QueueArrayTail>-1 && CurrentDigitsCount<MaxDigitsCount-1; QueueArrayTail--)
	{
		if(QueueArray[QueueArrayTail]==0)
			DigitsCountOfNumber=1;
		else
		{
			ten=QueueArray[QueueArrayTail];
			DigitsCountOfNumber=0;
			while(ten>0)
			{
				ten/=10;
				DigitsCountOfNumber++;
			}
		}
		printf(" ");
		CurrentDigitsCount++;
		for(ten=1,j=0; j<DigitsCountOfNumber-1; j++)
			ten*=10;
		for(j=0; j<DigitsCountOfNumber && CurrentDigitsCount<MaxDigitsCount; j++)
		{
			printf("%d",(QueueArray[QueueArrayTail]/ten)%10);
			ten/=10;
			CurrentDigitsCount++;
		}		
	}
	if(QueueArrayTail>0)
		printf("...");
	printf("\nRemoving of items from the QUEUE (ARRAY)...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	for(QueueArrayTail=ArraySize-1; QueueArrayTail>-1; QueueArrayTail--)
		QueueArray=(int*)realloc(QueueArray,sizeof(int)*QueueArrayTail);
	free(QueueArray);
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %d ms = %d sec\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%17d\n",EndTimeMsec);
	printf("--------------------------------------------------------------------------------");
	//-----------------------------------QUEUE (POINTERS)-----------------------------------
	printf("Building of the QUEUE (POINTERS)...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	QueuePointers=(struct QueuePointersStruct*)calloc(sizeof(struct QueuePointersStruct),1);
	QueuePointers->data=array[0];
	for(i=1; i<ArraySize; i++)
	{
		QueuePointers->next=(struct QueuePointersStruct*)malloc(sizeof(struct QueuePointersStruct));
		QueuePointers->next->prev=QueuePointers;
		QueuePointers->next->data=array[i];
		QueuePointers=QueuePointers->next;
	}
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime);
	printf(" Time: %d ms = %d sec. Items of queue:\n",EndTimeMsec,EndTime-StartTime);
	fprintf(TestFile,"%30s%14d","Queue (pointers)",EndTimeMsec);
	for(QueueTailPointers=QueuePointers,CurrentDigitsCount=0; QueuePointers!=NULL && CurrentDigitsCount<MaxDigitsCount-1; QueuePointers=QueuePointers->prev)
	{
		if(QueuePointers->data==0)
			DigitsCountOfNumber=1;
		else
		{
			ten=QueuePointers->data;
			DigitsCountOfNumber=0;
			while(ten>0)
			{
				ten/=10;
				DigitsCountOfNumber++;
			}
		}
		printf(" ");
		CurrentDigitsCount++;
		for(ten=1,j=0; j<DigitsCountOfNumber-1; j++)
			ten*=10;
		for(j=0; j<DigitsCountOfNumber && CurrentDigitsCount<MaxDigitsCount; j++)
		{
			printf("%d",(QueuePointers->data/ten)%10);
			ten/=10;
			CurrentDigitsCount++;
		}		
	}
	if(QueuePointers!=NULL)
		printf("...");
	printf("\nRemoving of items from the QUEUE (POINTERS)...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	for(QueueTailPointers=QueueTailPointers->prev; QueueTailPointers->prev!=NULL; QueueTailPointers=QueueTailPointers->prev)
		free(QueueTailPointers->next);
	free(QueueTailPointers->next);
	free(QueueTailPointers);
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime);
	printf(" Time: %d ms = %d sec\n",EndTimeMsec,EndTime-StartTime);
	fprintf(TestFile,"%17d\n",EndTimeMsec);
	printf("--------------------------------------------------------------------------------");
	//------------------------------Double linked list (array)------------------------------
	printf("Building of a double linked list (array)...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	DoubleLinkedListArray=(int*)malloc(sizeof(int)*ArraySize);
	for(DoubleLinkedListPrev=-1,DoubleLinkedListNext=0; DoubleLinkedListNext<ArraySize; DoubleLinkedListPrev++,DoubleLinkedListNext++)
		DoubleLinkedListArray[DoubleLinkedListNext]=array[DoubleLinkedListNext];
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime);
	printf(" Time: %d ms = %d sec. Items:\n",EndTimeMsec,EndTime-StartTime);
	fprintf(TestFile,"%30s%14d","Double linked list (array)",EndTimeMsec);
	for(CurrentDigitsCount=0; DoubleLinkedListPrev>-1 && CurrentDigitsCount<MaxDigitsCount-1; DoubleLinkedListPrev--,DoubleLinkedListNext--)
	{
		if(DoubleLinkedListArray[DoubleLinkedListPrev]==0)
			DigitsCountOfNumber=1;
		else
		{
			ten=DoubleLinkedListArray[DoubleLinkedListPrev];
			DigitsCountOfNumber=0;
			while(ten>0)
			{
				ten/=10;
				DigitsCountOfNumber++;
			}
		}
		printf(" ");
		CurrentDigitsCount++;
		for(ten=1,j=0; j<DigitsCountOfNumber-1; j++)
			ten*=10;
		for(j=0; j<DigitsCountOfNumber && CurrentDigitsCount<MaxDigitsCount; j++)
		{
			printf("%d",(DoubleLinkedListArray[DoubleLinkedListPrev]/ten)%10);
			ten/=10;
			CurrentDigitsCount++;
		}		
	}
	if(DoubleLinkedListPrev>-1)
		printf("...");
	printf("\nRemoving of items from the DOUBLE LINKED LIST (ARRAY)...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	for(DoubleLinkedListPrev=ArraySize-2,DoubleLinkedListNext=ArraySize-1; DoubleLinkedListPrev>-1; DoubleLinkedListPrev--,DoubleLinkedListNext--)
		DoubleLinkedListArray=(int*)realloc(DoubleLinkedListArray,sizeof(int)*DoubleLinkedListNext);
	free(DoubleLinkedListArray);
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime);
	printf(" Time: %d ms = %d sec\n",EndTimeMsec,EndTime-StartTime);
	fprintf(TestFile,"%17d\n",EndTimeMsec);
	printf("--------------------------------------------------------------------------------");
	//-----------------------------Double linked list (pointers)----------------------------
	printf("Building of the DOUBLE LINKED LIST (POINTERS)...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	DoubleLinkedList=(struct DoubleLinkedListStruct*)calloc(sizeof(struct DoubleLinkedListStruct),1);
	DoubleLinkedList->data=array[0];
	for(i=0; i<ArraySize; i++)
	{
		DoubleLinkedList->next=(struct DoubleLinkedListStruct*)calloc(sizeof(struct DoubleLinkedListStruct),1);
		DoubleLinkedList->next->prev=DoubleLinkedList;
		DoubleLinkedList->next->data=array[i];
		DoubleLinkedList=DoubleLinkedList->next;
	}
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime);
	printf(" Time: %d ms = %d sec. Items:\n",EndTimeMsec,EndTime-StartTime);
	fprintf(TestFile,"%30s%14d","Double linked list (pointers)",EndTimeMsec);
	for(DoubleLinkedListTail=DoubleLinkedList,CurrentDigitsCount=0; DoubleLinkedList!=NULL && CurrentDigitsCount<MaxDigitsCount-1; DoubleLinkedList=DoubleLinkedList->prev)
	{
		if(DoubleLinkedList->data==0)
			DigitsCountOfNumber=1;
		else
		{
			ten=DoubleLinkedList->data;
			DigitsCountOfNumber=0;
			while(ten>0)
			{
				ten/=10;
				DigitsCountOfNumber++;
			}
		}
		printf(" ");
		CurrentDigitsCount++;
		for(ten=1,j=0; j<DigitsCountOfNumber-1; j++)
			ten*=10;
		for(j=0; j<DigitsCountOfNumber && CurrentDigitsCount<MaxDigitsCount; j++)
		{
			printf("%d",(DoubleLinkedList->data/ten)%10);
			ten/=10;
			CurrentDigitsCount++;
		}		
	}
	if(DoubleLinkedList!=NULL)
		printf("...");
	printf("\nRemoving of items from the DOUBLE LINKED LIST...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	for(DoubleLinkedListTail=DoubleLinkedListTail->prev; DoubleLinkedListTail->prev!=NULL; DoubleLinkedListTail=DoubleLinkedListTail->prev)
		free(DoubleLinkedListTail->next);
	free(DoubleLinkedListTail->next);
	free(DoubleLinkedListTail);
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime);
	printf(" Time: %d ms = %d sec.\n",EndTimeMsec,EndTime-StartTime);
	fprintf(TestFile,"%17d\n",EndTimeMsec);
	printf("--------------------------------------------------------------------------------");
	fclose(TestFile);
	printf("The file tests.txt was created.");
	return 0;
}
