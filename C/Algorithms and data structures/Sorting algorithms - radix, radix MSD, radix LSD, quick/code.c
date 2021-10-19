#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
FILE *TestFile;
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
// A function to do counting sort of arr[] according to
// the digit represented by exp.
void CountingSort(int* arr, int n, int exp)
{
    int i,*output=(int*)malloc(sizeof(int)*n); // output array
    int* count=(int*)calloc(sizeof(int),10);
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++; 
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1]; 
    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    } 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
	free(output);
	free(count);
}
void RadixSort(int* arr, int n)
{//https://www.geeksforgeeks.org/radix-sort/
    // Find the maximum number to know number of digits
	int exp,max=arr[0];
	for(exp=0; exp<n; exp++)
		if(arr[exp]>max)
			max=arr[exp];
		for(exp = 1; max/exp>0; exp*=10)
			CountingSort(arr, n, exp);
}
void MSDRadixSort(int start,int end,int numberOfBits,int currentBit,int* input,int* tmp)
{//https://stackoverflow.com/questions/28726933/cant-get-the-radix-sort-algorithm-to-work-in-c
	int p,m,n,numberOfBuckets=1<<numberOfBits,bitMask=numberOfBuckets-1;
	int *buckets,shift=32-currentBit-numberOfBits;
	if((end-start)<1)
		return;	
	if((currentBit+numberOfBits)>32)//adjust numberOfBits if currentBit close to end element
		numberOfBits=32-currentBit;	
	buckets=(int*)malloc(sizeof(int)*(numberOfBuckets+1));
	for(p=0; p<numberOfBuckets+1; p++)
		buckets[p]=0;
	for(p=start; p<end; p++)
		buckets[(input[p]>>shift)&bitMask]++;
	for(p=0,m=start; p<numberOfBuckets+1; p++)
	{
		n=buckets[p];
		buckets[p]=m;
		m+=n;
	}	
	for(p=start; p<end; p++)//sort the input array input and store it in array tmp   
		tmp[buckets[(input[p]>>shift)&bitMask]++]=input[p];
	for(p=numberOfBuckets; p>0; p--)//restore bucket info
		buckets[p]=buckets[p-1];
	buckets[0]=start;	
	currentBit+=numberOfBits;//advance current bit
	if(currentBit<32)		
		for(p=0; p<numberOfBuckets; p++)//recurse on all the groups that have been created
			MSDRadixSort(buckets[p],buckets[p+1],numberOfBits,currentBit,tmp,input);	
	free(buckets);
	return;
}
void LSDRadixSort(int* a,int size)
{
	int i,*digitCount,pass=1,maxVal=0,digitPosition=1;
	int* bucket=(int*)malloc(sizeof(int)*size);
	for(i=0; i<size; i++)
		if(a[i]>maxVal)
			maxVal = a[i];	
	while(maxVal/digitPosition>0)
	{//maxVal decide the while-loop count; if maxVal is 3 digits, then we loop through 3 times
		digitCount=(int*)calloc(sizeof(int),10);//reset counter		
		for(i=0; i<size; i++)//count pos-th digits (keys)
			digitCount[a[i]/digitPosition%10]++;		
		for(i=1; i<10; i++)//accumulated count
			digitCount[i]+=digitCount[i-1];		
		for(i=size-1; i>=0; i--)//To keep the order, start from back side
			bucket[--digitCount[a[i]/digitPosition%10]]=a[i];		
		for(i=0; i<size; i++)//rearrange the original array using elements in the bucket
			a[i]=bucket[i];
		digitPosition*=10;
		free(digitCount);
	}
}
void LSDRadixSortOptimized(int* array,int n)//https://habr.com/ru/post/533206/
{		
	char* b;
	int* TempArray=(int*)malloc(sizeof(int)*n);//Память под временный массив
	int* baskets=(int*)calloc(sizeof(int),1024);
	int i,value,digit,off,key,*temp;
	for(i=0; i<n; ++i)//Заполняем массив корзин для всех разрядов
	{
		key=array[i];
		for(digit=0; digit<4; digit++)		
			baskets[((key>>(digit*8))&0xFF)+256*digit]++;		
	}	
	for (digit=0; digit<4; digit++)//Пересчитываем смещения для корзин
	{
		off=0;
		for(i=0; i<256; i++)
		{
			value=baskets[i+256*digit];
			baskets[i+256*digit]=off;
			off+=value;
		}
	}	
	for(i=0,b=(char*)&array[n],temp=&baskets[0]; i<n; ++i)
	{
		key=array[i];
		off=(key>>(0))&0xFF;
		TempArray[temp[off]++]=key;
	}	
	for(i=0,b=(char*)&TempArray[n]+1,temp=&baskets[256]; i<n; ++i)
	{
		key=TempArray[i];
		off=(key>>(8))&0xFF;
		array[temp[off]++]=key;
	}
	free(baskets);
	free(TempArray);
}
void TestAllSortingAlgorithms(int* InitialArray,int size,int MaxNumber)
{
	int MilesecondsCount,*SortedArray=(int*)malloc(sizeof(int)*size);
	int* temp=(int*)malloc(sizeof(int)*size);
	SYSTEMTIME StartTime,EndTime;
	CopyArray(SortedArray,InitialArray,size);
	printf("%24s","Quick sort (opt.)...");
	GetSystemTime(&StartTime);
	QuickSortOptimized(SortedArray,size);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);
	CopyArray(SortedArray,InitialArray,size);
	printf("%24s","Radix sort...");
	GetSystemTime(&StartTime);
	RadixSort(SortedArray,size);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);
	CopyArray(SortedArray,InitialArray,size);
	printf("%24s","MSD Radix sort...");
	GetSystemTime(&StartTime);
	MSDRadixSort(0,size,4,0,SortedArray,temp);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);	
	CopyArray(SortedArray,InitialArray,size);
	printf("%24s","LSD Radix sort...");
	GetSystemTime(&StartTime);
	LSDRadixSort(SortedArray,size);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);	
	CopyArray(SortedArray,InitialArray,size);
	printf("%24s","LSD Radix sort (opt.)...");
	GetSystemTime(&StartTime);
	LSDRadixSortOptimized(SortedArray,size);
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	MilesecondsCount=EndTime.wSecond*1000+EndTime.wMilliseconds;
	printf(" %2d sec = %6d ms.",EndTime.wSecond,MilesecondsCount);
	CheckSortedArray(SortedArray,InitialArray,size);
	fprintf(TestFile,"%22d",MilesecondsCount);	
	free(SortedArray);
	fprintf(TestFile,"\n");
	printf("--------------------------------------------------------------------------------");
}
int main(void)
{
	int i,ArraySize=5000000,MinNumber=0,MaxNumber=ArraySize;
	int *array=(int*)malloc(sizeof(int)*ArraySize);
	SYSTEMTIME StartTime,EndTime;	
	TestFile=fopen("tests.txt","w");
	srand(time(0));
	printf("SIZE OF ARRAY			%17d;\n",ArraySize);
	printf("MINIMUM NUMBER:			%17d;\n",MinNumber);
	printf("MAXIMUM NUMBER:			%17d;\n",MaxNumber);
	printf("================================================================================");	
	fprintf(TestFile,"SIZE OF ARRAY			%17d;\n",ArraySize);
	fprintf(TestFile,"MINIMUM NUMBER:			%17d;\n",MinNumber);
	fprintf(TestFile,"MAXIMUM NUMBER:			%17d;\n",MaxNumber);	
	fprintf(TestFile,"%60s%22s%22s%22s%22s\n","Quick sort (opt.)","Radix sort","MSD Radix sort","LSD Radix sort","Radix sort LSD (opt.)");
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
