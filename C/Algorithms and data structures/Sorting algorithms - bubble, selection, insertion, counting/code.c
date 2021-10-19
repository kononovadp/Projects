#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
FILE *TestFile;
void BubbleSort(int *arr,int size)
{
	int t;
	char sorted=0;
	int i;
	size--;
	while(sorted!=1)
	{
		sorted=1;
		for(i=0; i<size; i++)
			if(arr[i]>arr[i+1])
			{
				sorted=0;
				t=arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=t;
			}
	}
}
void SelectionSort(int *arr,int size)
{
	int t;
	int i,j,min;
	for(i=0; i<size; i++)
	{
		for(j=i+1,min=i; j<size; j++)
			if(arr[j]<arr[min])
				min=j;
		if(min!=i)
		{
			t=arr[i];
			arr[i]=arr[min];
			arr[min]=t;
		}
	}
}
void InsertionSort(int *arr,int size)
{
	int t;
	int i,j;
	for(i=1; i<size; i++)
		for(j=i; j>0 && arr[j-1]>arr[j]; j--)
		{
			t=arr[j];
			arr[j]=arr[j-1];
			arr[j-1]=t;
		}
}
void CountingSort(int *arr,int size,int max)
{
	int i,j,k;
	int *counts=(int*)calloc(sizeof(int),max);
	for(i=0; i<size; i++)
		counts[arr[i]]++;
	for(i=0,k=0; i<max; i++)
		for(j=0; j<counts[i]; j++,k++)
			arr[k]=i;
	free(counts);
}
int LomutoPartition(int *arr,int low,int high)
{
	int pivot=arr[high],t;
	int i=low,j;
	for(j=low; j<high; j++)
		if(arr[j]<=pivot)
		{
			t=arr[i];
			arr[i]=arr[j];
			arr[j]=t;
			i++;
		}
	t=arr[i];
	arr[i]=arr[high];
	arr[high]=t;
	return i;
}
void QuickSort(int *arr,int high,int low)
{
	int p;
	if(low>high)
		return;
	p=LomutoPartition(arr,low,high);
	QuickSort(arr,p-1,low);
	QuickSort(arr,high,p+1);
}
void QuickSortOptimized(int* arr,int size)
{//Основна ідея даної реалізації була взята тут: http://algolist.ru/sort/quick_sort.php
	int StackSize=2048;
	int* LeftStack=(int*)malloc(sizeof(int)*StackSize); //стеки запитів
	int* RightStack=(int*)malloc(sizeof(int)*StackSize); //(кожний задається парою значень)
	int i,j,temp; //показники, які беруть участь у розділенні
	int LeftBoundary, RightBoundary; //границі частини, сортованої в циклі
	int stackpos=1; //поточна позиція у стеці
	int midpoint; //середина масиву
	int pivot; //опорний елемент
	LeftStack[1]=0;
	RightStack[1]=size-1;
	do
	{
		//Узяти границі LeftBoundary та RightBoundary поточного масиву із стеку:
		LeftBoundary=LeftStack[stackpos];
		RightBoundary=RightStack[stackpos];
		stackpos--;
		do
		{
			// Крок 1. Розділення по елементу pivot
			midpoint=(LeftBoundary+RightBoundary)>>1;
			i=LeftBoundary;
			j=RightBoundary;
			pivot=arr[midpoint];
			do
			{
				while(arr[i]<pivot)
					i++;
				while(pivot<arr[j])
					j--;
				if(i<=j)
				{
					temp=arr[i];
					arr[i]=arr[j];
					arr[j]=temp;
					i++;
					j--;
				}
			}
			while(i<=j);
			//Зараз показник і вказує на початок правого підмасиву, j - на кінець лівого;
			//показники i та j можуть вийти за границі масиву.
			//Кроки 2 та 3: відправляємо більшу частину в стек та пересуваємо границі
			if(i<midpoint) //якщо права частина більше
			{				
				if(i<RightBoundary) //якщо в ній більше одного елемента, потрібно сортувати
				{
					stackpos++;
					LeftStack[stackpos]=i;
					RightStack[stackpos]=RightBoundary;
				}
				RightBoundary=j;//наступна ітерація розділення буде працювати з лівим стеком
			}
			else //ліва частина більше
			{
				if(j>LeftBoundary)
				{
					stackpos++;
					LeftStack[stackpos]=LeftBoundary;
					RightStack[stackpos]=j;
				}
				LeftBoundary=i;
			}
		}
		while(LeftBoundary<RightBoundary); //доки у меншій частині більше 1 елемента
	}
	while(stackpos!=0); //доки є запити у стеку
	free(LeftStack);
	free(RightStack);
}
void MergeSortRecursive(int *arr,int high,int low)
{
	int mid,it1=0,it2=0,*res;
	if(low+1>=high)
		return;
	mid=(low+high)/2;
	MergeSortRecursive(arr,mid,low);
	MergeSortRecursive(arr,high,mid);
	res=(int*)malloc(sizeof(int)*(high-low));
	while(low+it1<mid && mid+it2<high)
		if(arr[low+it1]<arr[mid+it2])
		{
			res[it1+it2]=arr[low+it1];
			it1++;
		}
		else
		{
			res[it1+it2]=arr[mid+it2];
			it2++;
		}
	while(low+it1<mid)
	{
		res[it1+it2]=arr[low+it1];
		it1++;
	}
	while(mid+it2<high)
	{
		res[it1+it2]=arr[mid+it2];
		it2++;
	}
	for(mid=0,it1+=it2; mid<it1; mid++)
		arr[low+mid]=res[mid];
	free(res);
}
void MergeSortIterative(int *arr,int size)
{
	int i,j,k,mid,it1,it2,*res,high,low;
	for(i=1; i<size; i*=2)
		for(j=0,k=size-i; j<k; j+=2*i)
		{
			low=j;
			mid=j+i;
			high=j+2*i;
			it1=0;
			it2=0;
			if(size<high)
				high=size;
			res=(int*)malloc(sizeof(int)*(high-low));
			while(low+it1<mid && mid+it2<high)
				if(arr[low+it1]<arr[mid+it2])
				{
					res[it1+it2]=arr[low+it1];
					it1++;
				}
				else
				{
					res[it1+it2]=arr[mid+it2];
					it2++;
				}
			while(low+it1<mid)
			{
				res[it1+it2]=arr[low+it1];
				it1++;
			}
			while(mid+it2<high)
			{
				res[it1+it2]=arr[mid+it2];
				it2++;
			}
			for(mid=0,it1+=it2; mid<it1; mid++)
				arr[low+mid]=res[mid];
			free(res);
		}
}
__inline void up(size_t *a,size_t *b)
{
	size_t temp;
	temp=*a;
	*a+=*b+1;
	*b=temp;
}
__inline void down(size_t *a,size_t *b)
{
	size_t temp;
	temp=*b;
	*b=*a-*b-1;
	*a=temp;
}
struct SmoothSortTree
{
	int *a;
	size_t q,r,p,b,c,r1,b1,c1;
};
void sift(struct SmoothSortTree *tree)
{
	size_t r0,r2;
	int temp;
	r0=tree->r1;
	temp=tree->a[r0];
	while(tree->b1>2)
	{
		r2=tree->r1-tree->b1+tree->c1;
		if (tree->a[tree->r1-1]>=tree->a[r2])
		{
			r2=tree->r1-1;
			down(&tree->b1,&tree->c1);
		}
		if (tree->a[r2]<temp)
			tree->b1=1;
		else
		{
			tree->a[tree->r1]=tree->a[r2];
			tree->r1=r2;
			down(&tree->b1,&tree->c1);
		}
	}
	if (tree->r1-r0>0)
		tree->a[tree->r1]=temp;
}
void trinkle(struct SmoothSortTree *tree)
{
	size_t p1,r0,r2,r3;
	int temp;
	p1=tree->p;
	tree->b1=tree->b;
	tree->c1=tree->c;
	r0=tree->r1; 
	temp=tree->a[r0];
	while(p1>0)
	{
		while((p1&1)==0)
		{
			p1>>=1;
			up(&tree->b1,&tree->c1);
		}
		r3=tree->r1-tree->b1;
		if (p1==1||tree->a[r3]<temp)
			p1=0;
		else
		{
			p1--;
			if(tree->b1==1)
			{
				tree->a[tree->r1]=tree->a[r3];
				tree->r1=r3;
			}
			else
				if(tree->b1>=3)
				{
					r2=tree->r1-tree->b1+tree->c1;
					if(tree->a[tree->r1-1]>=tree->a[r2])
					{
						r2=tree->r1-1;
						down(&tree->b1,&tree->c1);
						p1<<=1;
					}
					if(tree->a[r2]<tree->a[r3])
					{
						tree->a[tree->r1]=tree->a[r3];
						tree->r1=r3;
					}
					else
					{
						tree->a[tree->r1]=tree->a[r2];
						tree->r1=r2;
						down(&tree->b1,&tree->c1);
						p1=0;
					}
				}
		}
	}
	if(tree->r1-r0!=0)
		tree->a[tree->r1]=temp;
	sift(tree);
}
void semitrinkle(struct SmoothSortTree *tree)
{
	int temp;
	tree->r1=tree->r-tree->c;
	if(tree->a[tree->r1]>=tree->a[tree->r])
	{
		temp=tree->a[tree->r];
		tree->a[tree->r]=tree->a[tree->r1];
		tree->a[tree->r1]=temp;
		trinkle(tree);
	}
}
void SmoothSort(int *a,int n)
{
	struct SmoothSortTree tree;
	size_t temp;
	tree.a=a;
	tree.r=0;
	tree.p=tree.b=tree.c=1;
	//побудова дерева
	for(tree.q=1; tree.q<n; tree.q++)
	{
		tree.r1=tree.r;
		if ((tree.p & 7)==3)
		{
			tree.b1=tree.b;
			tree.c1=tree.c;
			sift(&tree);
			tree.p=(tree.p+1)>>2;
			temp=tree.b+tree.c+1;
			tree.b+=temp+1;
			tree.c=temp;
		}
		else
			if((tree.p&3)==1)
			{
				if(tree.q+tree.c<n)
				{
					tree.b1=tree.b;
					tree.c1=tree.c;
					sift(&tree);
				}
				else
					trinkle(&tree);
				do
				{
					down(&tree.b,&tree.c);
					tree.p<<=1;
				}
				while(tree.b>1);
				tree.p++;
			}
		tree.r++;
	}
	tree.r1=tree.r;
	trinkle(&tree);
	//побудова відсортованого масиву
	while(tree.q-->1)
	{
		if(tree.b==1)
		{
			tree.r--;
			tree.p--;
			while((tree.p & 1)==0)
			{
				tree.p>>=1;
				up(&tree.b,&tree.c);
			}
		}
		else
			if(tree.b>2)
			{
				tree.p--;
				tree.r=tree.r-tree.b+tree.c;
				if(tree.p>0)
					semitrinkle(&tree);
				down(&tree.b,&tree.c);
				tree.p=(tree.p << 1)+1;
				tree.r+=tree.c;
				semitrinkle(&tree);
				down(&tree.b,&tree.c);
				tree.p=(tree.p << 1)+1;
			}
	}
}
__inline void ShowArray(int* array,int ArraySize)
{
	int i,j,ten,MaxDigitsCount=76,CurrentDigitsCount=0,DigitsCountOfNumber;
	for(i=0; i<ArraySize && CurrentDigitsCount<MaxDigitsCount-1; i++)
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
	if(i<ArraySize)
		printf(":");
	if(CurrentDigitsCount==MaxDigitsCount-1)
		printf(" ");
	putchar('\n');
}
void ShuffleArray(int* array,int ArraySize,int percentage,char ShowMessage)
{
	int i,j,t,min,max=ArraySize,PartsCount,PartSize=ArraySize*percentage/100;
	if(PartSize==0)
		PartSize=ArraySize;
	PartsCount=ArraySize/PartSize;
	if(ShowMessage==1)
		printf("Partially sorted array: count of sorted parts: %d; size: %d items:",PartsCount/2,PartSize);
	if(PartsCount==1)
		PartsCount++;
	while(max>=PartSize)
	{		
		if(PartsCount%2==0)
			for(i=max-1,min=max-PartSize; i>min; i--)
			{
				j=min+(rand()%(max-min));
				t=array[i];
				array[i]=array[j];
				array[j]=t;
			}
		max-=PartSize;
		PartsCount--;
	}
	if(ShowMessage==1)
		putchar('\n');
}
void GetArrayWithRegularElements(int* array,int ArraySize,int percentage)
{
	int i,ElementsCount=ArraySize*percentage/100,pos;	
	ShuffleArray(array,ArraySize,0,0);
	if(ElementsCount==0)
		printf("Percentage of equal numbers: %d (%d items):",percentage,ElementsCount);
	else
		printf("Percentage of equal numbers: %d (%d numbers of %d):",percentage,ElementsCount,array[0]);
	for(i=0; i<ElementsCount; i++)
		array[i]=array[0];
	ShuffleArray(array,ArraySize,0,0);
	putchar('\n');
}
void CheckSortedArray(int* SortedArray,int* InitialArray,int size)
{
	char sorted;
	int i,j,*FoundItems;
	printf(" Checking...");
	for(i=0; i<size-1; i++)
		if(SortedArray[i+1]<SortedArray[i])
		{
			printf(" Sorted INCORRECTLY.\n");
			return;
		}
	FoundItems=(int*)calloc(sizeof(int),size);
	for(i=0; i<size; i++)
	{
		for(j=0,sorted=0; j<size; j++)
			if(FoundItems[j]==0 && SortedArray[i]==InitialArray[j])
			{
				FoundItems[j]=1;
				sorted=1;
				break;
			}
		if(sorted==0)
		{			
			printf(" Sorted INCORRECTLY.\n");
			free(FoundItems);
			return;
		}
	}
	printf(" Sorted correctly.\n");
	free(FoundItems);
}
void FillArray(int* array,int ArraySize,int min,int max)
{
	int i,j;	
	for(i=0,j=min; i<ArraySize; i++,j++)
	{
		if(j==max)
			j=min;
		array[i]=j;
	}
}
__inline void CopyArray(int* recipient,int* source,int size)
{
	int i;
	for(i=0; i<size; i++)
		recipient[i]=source[i];
}
void ShuffleThePartOfArray(int* array, int ArraySize, int percentage)
{
	unsigned long long int i=ArraySize*percentage/100,j;
	int t;
	printf("Array was sorted for %d percent, shuffled part starts from the index %lld:",percentage,i);
	for(; i<ArraySize; i++)
	{
		j=i+(rand()%(ArraySize-i));
		t=array[i];
		array[i]=array[j];
		array[j]=t;
	}
	putchar('\n');
}
void FillArrayWithRandomNumbers(int* arr,int size,int MinNumber,int MaxNumber)
{
	int i;
	printf("Array of random numbers between %d and %d",MinNumber,MaxNumber);
	if(MinNumber==0)
		MinNumber=1;
	for(i=0; i<size; i++)
		if(i%2==0)
			arr[i]=rand()%MinNumber;
		else
			if(i%2==1)
				arr[i]=rand()%MaxNumber;
			else
				if(i%3==0)
					arr[i]=MinNumber+(rand()%(MaxNumber-MinNumber));
	if(size<=50)
		ShowArray(arr,size);
}
SYSTEMTIME GetTimeDifference(SYSTEMTIME pSr,SYSTEMTIME pSl)
{
    SYSTEMTIME t_res;
    FILETIME v_ftime;
    ULARGE_INTEGER v_ui;
    __int64 v_right,v_left,v_res;
    SystemTimeToFileTime(&pSr,&v_ftime);
    v_ui.LowPart=v_ftime.dwLowDateTime;
    v_ui.HighPart=v_ftime.dwHighDateTime;
    v_right=v_ui.QuadPart;
    SystemTimeToFileTime(&pSl,&v_ftime);
    v_ui.LowPart=v_ftime.dwLowDateTime;
    v_ui.HighPart=v_ftime.dwHighDateTime;
    v_left=v_ui.QuadPart;
    v_res=v_right-v_left;
    v_ui.QuadPart=v_res;
    v_ftime.dwLowDateTime=v_ui.LowPart;
    v_ftime.dwHighDateTime=v_ui.HighPart;
    FileTimeToSystemTime(&v_ftime,&t_res);
    return t_res;
}
void TestAllSortingAlgorithms(int* InitialArray,int size,int MaxNumber)
{
	int MilesecondsCount,*SortedArray=(int*)malloc(sizeof(int)*size);
	SYSTEMTIME StartTime,EndTime;
	CopyArray(SortedArray,InitialArray,size);
	printf("%21s","Bubble sort...");
	GetSystemTime(&StartTime);
	BubbleSort(SortedArray,size);	
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" Time: %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);	
	CopyArray(SortedArray,InitialArray,size);
	printf("%21s","Selection sort...");
	GetSystemTime(&StartTime);
	SelectionSort(SortedArray,size);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" Time: %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);	
	CopyArray(SortedArray,InitialArray,size);
	printf("%21s","Insertion sort...");
	GetSystemTime(&StartTime);
	InsertionSort(SortedArray,size);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" Time: %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);	
	CopyArray(SortedArray,InitialArray,size);
	printf("%21s","Quick sort...");
	GetSystemTime(&StartTime);
	QuickSort(SortedArray,size-1,0);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" Time: %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);	
	CopyArray(SortedArray,InitialArray,size);
	printf("%21s","Quick sort (opt.)...");
	GetSystemTime(&StartTime);
	QuickSortOptimized(SortedArray,size);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" Time: %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);	
	CopyArray(SortedArray,InitialArray,size);
	printf("%21s","Counting sort...");
	GetSystemTime(&StartTime);
	CountingSort(SortedArray,size,MaxNumber);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" Time: %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);	
	CopyArray(SortedArray,InitialArray,size);
	printf("%21s","Merge sort (rec.)...");
	GetSystemTime(&StartTime);
	MergeSortRecursive(SortedArray,size,0);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" Time: %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);	
	CopyArray(SortedArray,InitialArray,size);
	printf("%21s","Merge sort (iter.)...");
	GetSystemTime(&StartTime);
	MergeSortIterative(SortedArray,size);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" Time: %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);	
	CopyArray(SortedArray,InitialArray,size);
	printf("%21s","Smooth sort...");
	GetSystemTime(&StartTime);
	SmoothSort(SortedArray,size);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" Time: %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);	
	free(SortedArray);
	fprintf(TestFile,"\n");
	printf("--------------------------------------------------------------------------------");
}
int main(void)
{
	int i,ArraySize=40000,MinNumber=0,MaxNumber=ArraySize;
	int *array=(int*)malloc(sizeof(int)*ArraySize);
	SYSTEMTIME StartTime,EndTime;	
	TestFile=fopen("tests.txt","w");
	srand(time(0));
	printf("DATA TYPE:                %17s;\n","int");
	printf("SIZE OF ARRAY             %17d;\n",ArraySize);
	printf("MINIMUM NUMBER:           %17d;\n",MinNumber);
	printf("MAXIMUM NUMBER:           %17d;\n",MaxNumber);
	printf("================================================================================");
	fprintf(TestFile,"DATA TYPE:                %17s;\n","int");
	fprintf(TestFile,"SIZE OF ARRAY             %17d;\n",ArraySize);
	fprintf(TestFile,"MINIMUM NUMBER:           %17d;\n",MinNumber);
	fprintf(TestFile,"MAXIMUM NUMBER:           %17d;\n",MaxNumber);
	fprintf(TestFile,"%60s%22s%22s%22s%22s%22s%22s%22s%22s\n","Bubble sort","Selection sort","Insertion sort","Quick sort","Quick sort (opt.)","Counting sort","Merge sort (rec.)","Merge sort (iter.)","Smooth sort");
	printf("Building of array of random numbers...");
	GetSystemTime(&StartTime);
	array=(int*)malloc(sizeof(int)*ArraySize);
	for(i=0; i<ArraySize; i++)
		array[i]=MinNumber+rand()%(MaxNumber-MinNumber);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	printf(" Time: %2d sec = %6d ms.\n",EndTime.wSecond,EndTime.wSecond*1000+EndTime.wMilliseconds);		
	fprintf(TestFile,"%38s","Random array ");
	TestAllSortingAlgorithms(array,ArraySize,MaxNumber);	
	printf("Building of array of numbers in direct order...");
	GetSystemTime(&StartTime);
	for(i=ArraySize-1; i>-1; i--)
		array[i]=i;
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	printf(" Time: %2d sec = %6d ms.\n",EndTime.wSecond,EndTime.wSecond*1000+EndTime.wMilliseconds);
	fprintf(TestFile,"%38s","Numbers in direct order ");
	TestAllSortingAlgorithms(array,ArraySize,MaxNumber);	
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	ShuffleArray(array,ArraySize,25,1);		
	fprintf(TestFile,"%38s","One sorted part makes up 25 percent ");
	TestAllSortingAlgorithms(array,ArraySize,MaxNumber);
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	ShuffleThePartOfArray(array,ArraySize,10);		
	fprintf(TestFile,"%38s","Array was sorted for 10 percent ");
	TestAllSortingAlgorithms(array,ArraySize,MaxNumber);
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	ShuffleThePartOfArray(array,ArraySize,30);		
	fprintf(TestFile,"%38s","Array was sorted for 30 percent ");
	TestAllSortingAlgorithms(array,ArraySize,MaxNumber);
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	ShuffleThePartOfArray(array,ArraySize,70);		
	fprintf(TestFile,"%38s","Array was sorted for 70 percent ");
	TestAllSortingAlgorithms(array,ArraySize,MaxNumber);
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	GetArrayWithRegularElements(array,ArraySize,0);		
	fprintf(TestFile,"%38s","Array without equal numbers ");
	TestAllSortingAlgorithms(array,ArraySize,MaxNumber);	
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	GetArrayWithRegularElements(array,ArraySize,10);		
	fprintf(TestFile,"%38s","Array with 10 percent of equal numbers");
	TestAllSortingAlgorithms(array,ArraySize,MaxNumber);	
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	GetArrayWithRegularElements(array,ArraySize,25);		
	fprintf(TestFile,"%38s","Array with 25 percent of equal numbers");
	TestAllSortingAlgorithms(array,ArraySize,MaxNumber);	
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	GetArrayWithRegularElements(array,ArraySize,80);		
	fprintf(TestFile,"%38s","Array with 80 percent of equal numbers");
	TestAllSortingAlgorithms(array,ArraySize,MaxNumber);
	free(array);
	fclose(TestFile);
	printf("The file tests.txt was created (better seen without word wrap).");
	return 0;
}
