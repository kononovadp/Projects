#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <Windows.h>
#define RedBlackTreeNULL &sentinel
FILE *TestFile;
char DigitsCount;
struct BinaryTree
{
	int data;
	struct BinaryTree *right,*left;
};
struct RedBlackTree
{
	struct RedBlackTree *left,*right,*parent;	
	char RedColor;
	int data;
};
struct RedBlackTree sentinel={RedBlackTreeNULL,RedBlackTreeNULL,RedBlackTreeNULL,0,0};
struct RedBlackTree *RedBlackTreeRoot=RedBlackTreeNULL;
void QuickSort(int* arr,int size)
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
char GetDigitsCount(int n)
{
	char i=0;
	if(n==0)
		return 1;
	while(n>0)
	{
		n/=10;
		i++;
	}
	return i;
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
		printf("...");
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
		printf("Partially sorted array: count of sorted parts: %d; size: %d items...",PartsCount/2,PartSize);
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
		printf("Percentage of equal numbers: %d (%d items)...",percentage,ElementsCount);
	else
		printf("Percentage of equal numbers: %d (%d numbers of %d)...",percentage,ElementsCount,array[0]);
	for(i=0; i<ElementsCount; i++)
		array[i]=array[0];
	ShuffleArray(array,ArraySize,0,0);
	putchar('\n');
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
void ShuffleThePartOfArray(int* array, int ArraySize, int percentage)
{
	unsigned long long int i=ArraySize*percentage/100,j;
	int t;
	printf("Array was sorted for %d percent, shuffled part starts from the index %lld...",percentage,i);
	for(; i<ArraySize; i++)
	{
		j=i+(rand()%(ArraySize-i));
		t=array[i];
		array[i]=array[j];
		array[j]=t;
	}
	putchar('\n');
}
int GetCountOfEqualItems(int *array,int ArraySize)
{
	int i,j,count=0,*SortedArray;
	DWORD StartTimeMsec,EndTimeMsec;
	time_t StartTime,EndTime;
	printf("Counting of equal items...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	SortedArray=(int*)malloc(sizeof(int)*ArraySize);
	for(i=0; i<ArraySize; i++)
		SortedArray[i]=array[i];
	QuickSort(SortedArray,ArraySize);
	for(i=0,ArraySize--; i<ArraySize; i++)
		if(SortedArray[i]==SortedArray[i+1])
			count++;
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %5d ms = %4d sec\n",EndTimeMsec,EndTime);
	printf("Sorted array:\n");
	ShowArray(SortedArray,ArraySize+1);
	free(SortedArray);
	return count;
}
void AddToTheBinaryTree(struct BinaryTree *node,int n)
{
	if(n>node->data && node->right==NULL)
	{
		node->right=(struct BinaryTree*)calloc(sizeof(struct BinaryTree),1);
		node->right->data=n;
	}
	else
		if(n<node->data && node->left==NULL)
		{
			node->left=(struct BinaryTree*)calloc(sizeof(struct BinaryTree),1);
			node->left->data=n;
		}
		else
			if(n>node->data && node->right!=NULL)
				AddToTheBinaryTree(node->right,n);
			else
				if(n<node->data && node->left!=NULL)
					AddToTheBinaryTree(node->left,n);
}
void AddToTheBinaryTreeIterative(struct BinaryTree *node,int n)
{
	for(;;)
	{
		if(node->data==n)
			return;
		if(n>node->data && node->right==NULL)
		{
			node->right=(struct BinaryTree*)malloc(sizeof(struct BinaryTree));
			node->right->data=n;
			node->right->right=NULL;
			node->right->left=NULL;
			return;
		}
		else
			if(n<node->data && node->left==NULL)
			{
				node->left=(struct BinaryTree*)malloc(sizeof(struct BinaryTree));
				node->left->data=n;
				node->left->right=NULL;
				node->left->left=NULL;
				return;
			}
		if(n>node->data && node->right!=NULL)
			node=node->right;
		else
			if(n<node->data && node->left!=NULL)
				node=node->left;
	}
}
void ShowAndTraverseBinaryTree(struct BinaryTree *node,int *AddedItemsCount,int *CurrentDigitsCount)
{
	int DigitsCountOfNumber,ten,j;	
	if(node->left!=NULL)
		ShowAndTraverseBinaryTree(node->left,AddedItemsCount,CurrentDigitsCount);
	if(*CurrentDigitsCount<76)
	{
		DigitsCountOfNumber=GetDigitsCount(node->data);
		if(*CurrentDigitsCount<75)
			printf(" ");
		*CurrentDigitsCount+=1;
		for(ten=1,j=0; j<DigitsCountOfNumber-1; j++)
			ten*=10;
		for(j=0; j<DigitsCountOfNumber && *CurrentDigitsCount<76; j++)
		{
			printf("%d",(node->data/ten)%10);
			ten/=10;
			*CurrentDigitsCount+=1;
		}
		if(*CurrentDigitsCount==76)
		{			
			printf("...");
			*CurrentDigitsCount+=5;
		}
	}
	*AddedItemsCount+=1;
	if(node->right!=NULL)
		ShowAndTraverseBinaryTree(node->right,AddedItemsCount,CurrentDigitsCount);
}
int ShowAndTraverseBinaryTreeIterative(struct BinaryTree *node,int QueueSize)
{
	char ch=0;
	int DigitsCountOfNumber,ten,i=0,j,CurrentDigitsCount=0,CountOfTraversedItems =0;
	struct BinaryTree **queue=(struct BinaryTree**)malloc(sizeof(struct BinaryTree*)*QueueSize);
	while(node!=NULL|| i>0)//https://russianblogs.com/article/95791337759/
	{
		while(node)
		{
			queue[i]=node;			
			node=node->left;
			i++;
		}
		DigitsCountOfNumber=GetDigitsCount(queue[i-1]->data);
		if(CurrentDigitsCount<75)
			printf(" ");
		CurrentDigitsCount+=1;
		for(ten=1,j=0; j<DigitsCountOfNumber-1; j++)
			ten*=10;
		for(j=0; j<DigitsCountOfNumber && CurrentDigitsCount<76; j++)
		{
			printf("%d",(queue[i-1]->data/ten)%10);
			ten/=10;
			CurrentDigitsCount+=1;
		}
		if(CurrentDigitsCount==76)
		{			
			printf("...");
			CurrentDigitsCount+=5;
		}
		node=queue[i-1]->right;
		i--;
		CountOfTraversedItems++;
	}	
	free(queue);
	return CountOfTraversedItems;
}
int GetHeightOfBinaryTree(struct BinaryTree *node)
{	
	int left,right,max;
	if(node==NULL)
		return 0;
	if(node->left!=NULL)	
		left=GetHeightOfBinaryTree(node->left);
	else
		left=0;
	if(node->right!=NULL)
		right=GetHeightOfBinaryTree(node->right);
	else
		right=0;
    if(right>left)
		max=right;
	else
		max=left;
    return max+1;
}
int GetHeightOfBinaryTreeIterative(struct BinaryTree *node,int ItemsCount)
{	//http://espressocode.top/iterative-method-to-find-height-of-binary-tree/
	struct BinaryTree **queue=(struct BinaryTree**)malloc(sizeof(struct BinaryTree*)*ItemsCount);
	int i,QueueTail,QueueFront,CountOfItemsInQueue,height=0;
	queue[0]=node;
	for(QueueTail=0,QueueFront=1,CountOfItemsInQueue=1; CountOfItemsInQueue!=0; height++)
	{
		for(i=0; i<CountOfItemsInQueue; i++,QueueTail++)
		{
			node=queue[QueueTail];
			if(node->left!=NULL)
			{
				queue[QueueFront]=node->left;
				QueueFront++;
			}
			if(node->right!=NULL)
			{
				queue[QueueFront]=node->right;
				QueueFront++;
			}
		}
		CountOfItemsInQueue=QueueFront-QueueTail;
	}
	free(queue);
	return height;
}
char SearchInBinaryTree(struct BinaryTree *node,int data,int *StepsCount)
{
	*StepsCount=*StepsCount+1;
	if(node->data==data)
		return 1;
	if(data<node->data)
	{
		if(node->left!=NULL)
			return SearchInBinaryTree(node->left,data,StepsCount);
		else
			return 0;
	}
	else
		if(data>node->data)
		{
			if(node->right!=NULL)
				return SearchInBinaryTree(node->right,data,StepsCount);
			else
				return 0;
		}
	return 0;
}
int SearchInBinaryTreeIterative(struct BinaryTree *node,int data,int QueueSize)
{
	int i,QueueTail,QueueFront,CountOfItemsInQueue,StepsCont=0;
	struct BinaryTree **queue=(struct BinaryTree**)malloc(sizeof(struct BinaryTree*)*QueueSize);
	queue[0]=node;
	for(i=1; i>0; StepsCont++)
	{		
		i--;		
		node=queue[i];
		if(node->data==data)
		{
			free(queue);
			return StepsCont+1;
		}
		if(node->right!=NULL)
		{
			queue[i]=node->right;
			i++;
		}
		if(node->left!=NULL)
		{
			queue[i]=node->left;
			i++;
		}
	}
	free(queue);
	return 0;
}
void FreeMemoryOfBinaryTree(struct BinaryTree *node)
{
	if(node->left!=NULL)
		FreeMemoryOfBinaryTree(node->left);
	if(node->right!=NULL)
		FreeMemoryOfBinaryTree(node->right);
	if(node->left!=NULL && node->left->left==NULL && node->left->right==NULL)
	{
	//	printf("\nitem %d was removed\n",node->left->data);
		free(node->left);
		node->left=NULL;		
	}
	if(node->right!=NULL && node->right->right==NULL && node->right->left==NULL)
	{
	//	printf("\nitem %d was removed\n",node->right->data);
		free(node->right);
		node->right=NULL;
	}	
}
void FreeMemoryOfBinaryTreeIterative(struct BinaryTree *node,int ItemsCount)
{
	struct BinaryTree **queue=(struct BinaryTree**)malloc(sizeof(struct BinaryTree*)*ItemsCount);
	int i,QueueTail,QueueFront,CountOfItemsInQueue;
	queue[0]=node;
	for(QueueTail=0,QueueFront=1,CountOfItemsInQueue=1; CountOfItemsInQueue!=0;)
	{
		for(i=0; i<CountOfItemsInQueue; i++,QueueTail++)
		{
			node=queue[QueueTail];
			if(node->left!=NULL)
			{
				queue[QueueFront]=node->left;
				QueueFront++;
			}
			if(node->right!=NULL)
			{
				queue[QueueFront]=node->right;
				QueueFront++;
			}
		}
		CountOfItemsInQueue=QueueFront-QueueTail;
	}
	for(i=QueueFront-2; i>-1; i--)
	{		
		node=queue[i];
		if(node!=NULL && node->left!=NULL)
		{
		//	printf("\n%d removed",node[i]->left->data);
			free(node->left);
			node->left=NULL;
		}
		if(node!=NULL && node->right!=NULL)
		{
		//	printf("\n%d removed",node[i]->right->data);
			free(node->right);
			node->right=NULL;
		}
	}
	free(queue);
}
/*void BalanceRedBlackTree(struct RedBlackTree *node)
{printf("\n|%d\n",node->data);
	struct RedBlackTree *uncle,*grandparent,*SavedNode;
	if (node->parent==NULL)
	{		
		node->RedColor=0;
		return;
	}
	if(node->parent->RedColor==0)
		return;
	grandparent=node->parent->parent;
	if(grandparent==NULL)
		uncle=NULL;
	else
		if(grandparent->parent==grandparent->left)
			uncle=grandparent->right;
		else
			uncle=grandparent->left;
	if((uncle!=NULL)&&(uncle->RedColor==1))
	{
		node->parent->RedColor=0;
		uncle->RedColor=0;
		grandparent->RedColor=1;
		BalanceRedBlackTree(grandparent);
	}
	else
	{
		if((node==node->parent->right)&&(node->parent==grandparent->left))
		{//поворот вліво			
			uncle=grandparent->left;
			SavedNode=node->left;
			grandparent->left=node;
			node->left=uncle;
			uncle->right=SavedNode;
			node=node->left;
		}
		else
			if ((node==node->parent->left)&&(node->parent==grandparent->right))
			{	//поворот вправо
				uncle=grandparent->right;
				SavedNode=node->right;
				grandparent->right=node;
				node->right=uncle;
				uncle->left=SavedNode;
				node=node->right;
			}
		grandparent=node->parent->parent;
		node->parent->RedColor=0;
		grandparent->RedColor=1;
		if ((node==node->parent->left)&&(node->parent==grandparent->left))
		{	//поворот вправо
			uncle=grandparent->left;
			uncle->parent=grandparent->parent;
			if(grandparent->parent!=NULL)
			{
				if (grandparent->parent->left==grandparent)
					grandparent->parent->left=uncle;
				else
					grandparent->parent->right=uncle;
			}
			grandparent->left=uncle->right;
			if(uncle->right!=NULL)
				uncle->right->parent=grandparent;
			grandparent->parent=uncle;
			uncle->right=grandparent;
		}
		else
			if((node==node->parent->right)&&(node->parent == grandparent->right))
			{	//поворот вліво
				uncle=grandparent->right;
				uncle->parent=grandparent->parent;
				if(grandparent->parent != NULL)
				{
					if (grandparent->parent->left==grandparent)
						grandparent->parent->left=uncle;
					else
						grandparent->parent->right=uncle;
				}
				grandparent->right=uncle->left;
				if(uncle->left!=NULL)
					uncle->left->parent=grandparent;
				grandparent->parent=uncle;
				uncle->left=grandparent;
			}
	}
}
void AddToTheRedBlackTree(struct RedBlackTree *node,int n)
{	
	if(node->left==NULL && n<node->data)
	{
		node->left=(struct RedBlackTree*)calloc(sizeof(struct RedBlackTree),1);
		node->left->RedColor=0;
		node->left->data=n;
		node->left->parent=node;
		node=node->left;
		BalanceRedBlackTree(node);
		return;
	}
	else
		if(node->right==NULL && n>node->data)
		{
			node->right=(struct RedBlackTree*)calloc(sizeof(struct RedBlackTree),1);
			node->right->RedColor=0;
			node->right->data=n;
			node->right->parent=node;
			node=node->right;
			BalanceRedBlackTree(node);
			return;
		}
	if(n>node->data)
		AddToTheRedBlackTree(node->right,n);
	else
		if(n<node->data)
			AddToTheRedBlackTree(node->left,n);
}*/
void RotateLeft(struct RedBlackTree *x)
{//http://algolist.ru/ds/rbtree.php
	struct RedBlackTree *y=x->right;
	x->right=y->left;
	if(y->left!=RedBlackTreeNULL)
		y->left->parent=x;
	if(y!=RedBlackTreeNULL)
		y->parent=x->parent;
	if(x->parent)
	{
		if(x==x->parent->left)
			x->parent->left=y;
		else
			x->parent->right=y;
	}
	else
		RedBlackTreeRoot=y;
	y->left=x;
	if(x!=RedBlackTreeNULL)
		x->parent=y;
}
void RotateRight(struct RedBlackTree *x)
{//http://algolist.ru/ds/rbtree.php
	struct RedBlackTree *y=x->left;
	x->left=y->right;
	if(y->right!=RedBlackTreeNULL)
		y->right->parent=x;
	if(y!=RedBlackTreeNULL)
		y->parent=x->parent;
	if(x->parent)
	{
		if(x==x->parent->right)
			x->parent->right=y;
		else
			x->parent->left=y;
	}
	else
		RedBlackTreeRoot=y;
	y->right=x;
	if(x!=RedBlackTreeNULL)
		x->parent=y;
}
void BalanceRedBlackTree(struct RedBlackTree *x)
{//http://algolist.ru/ds/rbtree.php
	struct RedBlackTree *y;
	while(x!=RedBlackTreeRoot && x->parent->RedColor==1)
	{
		if(x->parent==x->parent->parent->left)
		{
			y=x->parent->parent->right;
			if(y->RedColor==1)
			{
				x->parent->RedColor=0;//uncle is 1
				y->RedColor=0;
				x->parent->parent->RedColor=1;
				x=x->parent->parent;
			}
			else
			{//uncle is 0				
				if(x==x->parent->right)//make x a left child
				{
					x=x->parent;
					RotateLeft(x);
				}
				x->parent->RedColor=0;//recolor and rotate
				x->parent->parent->RedColor=1;
				RotateRight(x->parent->parent);
			}
		}
		else
		{//mirror image of above code
			y=x->parent->parent->left;
			if(y->RedColor==1)
			{//uncle is 1
				x->parent->RedColor=0;
				y->RedColor=0;
				x->parent->parent->RedColor=1;
				x=x->parent->parent;
			}
			else
			{//uncle is 0
				if (x==x->parent->left)
				{
					x=x->parent;
					RotateRight(x);
				}
				x->parent->RedColor=0;
				x->parent->parent->RedColor=1;
				RotateLeft(x->parent->parent);
			}
		}
	}
	RedBlackTreeRoot->RedColor=0;
}
struct RedBlackTree *AddToTheRedBlackTree(int data)
{//http://algolist.ru/ds/rbtree.php
	struct RedBlackTree *current,*parent,*x;
    current=RedBlackTreeRoot;
    parent=0;
    while(current!=RedBlackTreeNULL)
	{
		if(data==current->data)
			return (current);
		parent=current;
		//current=compLT(data, current->data) ?
        //    current->left : current->right;
		if(data<current->data)
			current=current->left;
		else
			current=current->right;
	}
	x=(struct RedBlackTree*)malloc(sizeof(struct RedBlackTree));
	x->data=data;
	x->parent=parent;
	x->left=RedBlackTreeNULL;
	x->right=RedBlackTreeNULL;
	x->RedColor=1;
	if(parent)//insert node in tree
	{
		if(data<parent->data)
			parent->left=x;
		else
			parent->right=x;
	}
	else
		RedBlackTreeRoot=x;
	BalanceRedBlackTree(x);
	return(x);
}
void ShowAndTraverseRedBlackTree(struct RedBlackTree *node,int *AddedItemsCount,int *CurrentDigitsCount)
{
	int DigitsCountOfNumber,ten,j;
	if(node->left!=RedBlackTreeNULL)
		ShowAndTraverseRedBlackTree(node->left,AddedItemsCount,CurrentDigitsCount);	
	if(*CurrentDigitsCount<76)
	{
		DigitsCountOfNumber=GetDigitsCount(node->data);
		if(*CurrentDigitsCount<75)
			printf(" ");
		*CurrentDigitsCount+=1;
		for(ten=1,j=0; j<DigitsCountOfNumber-1; j++)
			ten*=10;
		for(j=0; j<DigitsCountOfNumber && *CurrentDigitsCount<76; j++)
		{
			printf("%d",(node->data/ten)%10);
			ten/=10;
			*CurrentDigitsCount+=1;
		}
		if(*CurrentDigitsCount==76)
		{			
			printf("...");
			*CurrentDigitsCount+=5;
		}
	}
	*AddedItemsCount+=1;
	if(node->right!=RedBlackTreeNULL)
		ShowAndTraverseRedBlackTree(node->right,AddedItemsCount,CurrentDigitsCount);
}
int GetHeightOfRedBlackTree(struct RedBlackTree *node)
{	
	int left,right,max;
	if(node==RedBlackTreeNULL)
		return 0;
	if(node->left!=RedBlackTreeNULL)	
		left=GetHeightOfRedBlackTree(node->left);
	else
		left=-1;
	if(node->right!=RedBlackTreeNULL)
		right=GetHeightOfRedBlackTree(node->right);
	else
		right=-1;
    max=left>right?left:right;
    return max+1;
}
int GetHeightOfRedBlackTreeIterative(struct RedBlackTree *node,int ItemsCount)
{	//http://espressocode.top/iterative-method-to-find-height-of-binary-tree/
	struct RedBlackTree **queue=(struct RedBlackTree**)malloc(sizeof(struct RedBlackTree*)*ItemsCount);
	int i,QueueTail,QueueFront,CountOfItemsInQueue,height=0;
	queue[0]=node;
	for(QueueTail=0,QueueFront=1,CountOfItemsInQueue=1; CountOfItemsInQueue!=0; height++)
	{
		for(i=0; i<CountOfItemsInQueue; i++,QueueTail++)
		{
			node=queue[QueueTail];
			if(node->left!=RedBlackTreeNULL)
			{
				queue[QueueFront]=node->left;
				QueueFront++;
			}
			if(node->right!=RedBlackTreeNULL)
			{
				queue[QueueFront]=node->right;
				QueueFront++;
			}
		}
		CountOfItemsInQueue=QueueFront-QueueTail;
	}
	free(queue);
	return height-1;
}
int GetDepthOfRedBlackTree(struct RedBlackTree *node)
{
    int depth=1;
	if(node==RedBlackTreeNULL)
        return 0;	
	depth+=GetDepthOfRedBlackTree(node->left);
	depth+=GetDepthOfRedBlackTree(node->right);
    return depth;       
}
char SearchInRedBlackTree(struct RedBlackTree *node,int data,int *StepsCount)
{
	*StepsCount=*StepsCount+1;
	if(node->data==data)
		return 1;
	if(data<node->data)
	{
		if(node->left!=RedBlackTreeNULL)
			return SearchInRedBlackTree(node->left,data,StepsCount);
		else
			return 0;
	}
	else
		if(data>node->data)
		{
			if(node->right!=RedBlackTreeNULL)
				return SearchInRedBlackTree(node->right,data,StepsCount);
			else
				return 0;
		}
	return 0;
}
void FreeMemoryOfRedBlackTree(struct RedBlackTree *node)
{
	if(node==NULL || node==RedBlackTreeNULL)
		return;
	if(node->left!=RedBlackTreeNULL)
		FreeMemoryOfRedBlackTree(node->left);
	if(node->right!=RedBlackTreeNULL)
		FreeMemoryOfRedBlackTree(node->right);
	if(node->left!=RedBlackTreeNULL && node->left->left==RedBlackTreeNULL && node->left->right==RedBlackTreeNULL)
	{
		free(node->left);
		node->left=RedBlackTreeNULL;		
	}
	if(node->right!=RedBlackTreeNULL && node->right->right==RedBlackTreeNULL && node->right->left==RedBlackTreeNULL)
	{
		free(node->right);
		node->right=RedBlackTreeNULL;
	}
}
void TestTrees(int *array,int ArraySize,int CountOfEqualItemsInArray)
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
	unsigned long long int AverageStepsCount;
	int i,AddedItemsCount=0,HeightOfTree=0,StepsCount;
	int j,ten,MaxDigitsCount=76,CurrentDigitsCount,DigitsCountOfNumber;
	int *QueueArray,QueueArrayTail,*DoubleLinkedListArray,DoubleLinkedListPrev,DoubleLinkedListNext;
	struct BinaryTree *BinaryTreeRoot;
	DWORD StartTimeMsec,EndTimeMsec;
	time_t StartTime,EndTime;	
	printf("Building of a binary tree...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	BinaryTreeRoot=(struct BinaryTree*)malloc(sizeof(struct BinaryTree));
	BinaryTreeRoot->data=array[0];
	BinaryTreeRoot->left=NULL;
	BinaryTreeRoot->right=NULL;
	for(i=1; i<ArraySize; i++)
		AddToTheBinaryTreeIterative(BinaryTreeRoot,array[i]);
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;	
	printf(" Time: %5d ms = %7d sec. Tree:\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%12d",EndTimeMsec);
	AddedItemsCount=ShowAndTraverseBinaryTreeIterative(BinaryTreeRoot,ArraySize);	
	HeightOfTree=GetHeightOfBinaryTreeIterative(BinaryTreeRoot,ArraySize);
	printf("\n%56s %8d\n","Height of tree:",HeightOfTree);
	fprintf(TestFile,"%12d",HeightOfTree);
	printf("%56s %8d\n","Count of TRAVERSED items:",AddedItemsCount);
	printf("%56s %8d\n","Count of NOT TRAVERSED items:",ArraySize-AddedItemsCount);
	printf("%56s %8d\n","Count of EQUAL items in the array:",CountOfEqualItemsInArray);
	printf("Searching in binary tree...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	for(i=0,AddedItemsCount=0,AverageStepsCount=0; i<ArraySize; i++)
	{
		StepsCount=SearchInBinaryTreeIterative(BinaryTreeRoot,array[i],ArraySize);
		if(StepsCount>0)
		{
			AddedItemsCount++;
			AverageStepsCount+=StepsCount;
		}
	}
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %5d ms = %7d sec\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%12d",EndTimeMsec);
	printf("%56s %8d\n","Count of FOUND items in the binary tree:",AddedItemsCount);
	printf("%56s %8lld\n","Average count of steps to all items:",AverageStepsCount/ArraySize);
	printf("Clearing of memory of binary tree...");	
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	FreeMemoryOfBinaryTreeIterative(BinaryTreeRoot,ArraySize);	
	free(BinaryTreeRoot);
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;	
	printf(" Time: %5d ms = %7d sec\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%12d",EndTimeMsec);
	printf("--------------------------------------------------------------------------------");
	RedBlackTreeRoot=RedBlackTreeNULL;
	printf("Building of a red-black tree...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	for(i=0; i<ArraySize; i++)	
		AddToTheRedBlackTree(array[i]);
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %5d ms = %4d sec. Tree:\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%12d",EndTimeMsec);
	HeightOfTree=0;
	AddedItemsCount=0;
	ShowAndTraverseRedBlackTree(RedBlackTreeRoot,&AddedItemsCount,&HeightOfTree);
	HeightOfTree=GetHeightOfRedBlackTree(RedBlackTreeRoot);	
	printf("\n%56s %8d\n","Height of tree:",HeightOfTree);	
	fprintf(TestFile,"%12d",HeightOfTree);
	printf("%56s %8d\n","Count of TRAVERSED items:",AddedItemsCount);
	printf("%56s %8d\n","Count of NOT TRAVERSED items:",ArraySize-AddedItemsCount);
	printf("%56s %8d\n","Count of EQUAL items in the array:",CountOfEqualItemsInArray);
	printf("Searching in red-black tree...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	for(i=0,AddedItemsCount=0,AverageStepsCount=0; i<ArraySize; i++)
	{
		StepsCount=0;
		j=SearchInRedBlackTree(RedBlackTreeRoot,array[i],&StepsCount);
		if(j>0)
		{
			AddedItemsCount++;
			AverageStepsCount+=StepsCount;
		}
	}
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %5d ms = %4d sec\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%12d",EndTimeMsec);
	printf("%56s %8d\n","Count of FOUND items in the red-black tree:",AddedItemsCount);
	printf("%56s %8lld\n","Average count of steps to all items:",AverageStepsCount/ArraySize);
	printf("Clearing of memory of red-black tree...");	
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	FreeMemoryOfRedBlackTree(RedBlackTreeRoot);
	free(RedBlackTreeRoot);
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %5d ms = %4d sec\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%12d",EndTimeMsec);
	printf("--------------------------------------------------------------------------------");	
	printf("Building of a QUEUE (ARRAY)...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();	
	QueueArray=(int*)malloc(sizeof(int)*ArraySize);
	for(i=0,QueueArrayTail=0; i<ArraySize; i++,QueueArrayTail++)
		QueueArray[QueueArrayTail]=array[i];
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %d ms = %d sec. Items of queue:\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%12d",EndTimeMsec);
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
	fprintf(TestFile,"%12d",EndTimeMsec);
	printf("--------------------------------------------------------------------------------");	
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
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %d ms = %d sec. Items of queue:\n",EndTimeMsec,EndTime);	
	fprintf(TestFile,"%12d",EndTimeMsec);
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
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %d ms = %d sec\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%12d",EndTimeMsec);
	printf("--------------------------------------------------------------------------------");
	printf("Building of a double linked list (array)...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	DoubleLinkedListArray=(int*)malloc(sizeof(int)*ArraySize);
	for(DoubleLinkedListPrev=-1,DoubleLinkedListNext=0; DoubleLinkedListNext<ArraySize; DoubleLinkedListPrev++,DoubleLinkedListNext++)
		DoubleLinkedListArray[DoubleLinkedListNext]=array[DoubleLinkedListNext];
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %d ms = %d sec. Items:\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%12d",EndTimeMsec);
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
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %d ms = %d sec\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%12d",EndTimeMsec);
	printf("--------------------------------------------------------------------------------");
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
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %d ms = %d sec. Items:\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%12d",EndTimeMsec);
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
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %d ms = %d sec.\n",EndTimeMsec,EndTime);
	fprintf(TestFile,"%12d\n",EndTimeMsec);
	printf("--------------------------------------------------------------------------------");
	printf("================================================================================");
	printf("--------------------------------------------------------------------------------");
}
int main(void)
{
	unsigned int i,j,CountOfEqualItems,ArraySize=10000;
	int *array,MinNumber=1,MaxNumber=ArraySize+1;
	DWORD StartTimeMsec,EndTimeMsec;
	time_t StartTime,EndTime;
	TestFile=fopen("tests.txt","w");
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
	fprintf(TestFile,"NAMES OF COLUMNS:\nTIME OF ADDING TO THE BINARY TREE\nHEIGHT OF THE BINARY TREE\nTIME OF SEARCH IN THE BINARY TREE\nTIME TO CLEAR THE MEMORY OF THE BINARY TREE\nTIME OF ADDING TO THE RED-BLACK TREE\nHEIGHT OF THE RED-BLACK TREE\nTIME OF SEARCH IN THE RED-BLACK TREE\nTIME TO CLEAR THE MEMORY OF THE RED-BLACK TREE\nTIME OF ADDING TO THE QUEUE (ARRAY)\nTIME TO REMOVE ALL ITEMS FROM THE QUEUE (ARRAY)\nTIME OF ADDING TO THE QUEUE (POINTERS)\nTIME TO REMOVE ALL ITEMS FROM THE QUEUE (POINTERS)\nTIME OF ADDING TO THE DOUBLE LINKED LIST (ARRAY)\nTIME TO REMOVE ALL ITEMS FROM THE DOUBLE LINKED LIST (ARRAY)\nTIME OF ADDING TO THE DOUBLE LINKED LIST (POINTERS)\nTIME TO REMOVE ALL ITEMS FROM THE DOUBLE LINKED LIST (POINTERS)\n");	
	fprintf(TestFile,"==================================================================================================================================================================================================================================================\n");
	fprintf(TestFile,"%50s%12s%12s%12s%12s%12s%12s%12s%12s%12s%12s%12s%12s%12s%12s%12s\n","TOATTBT","HOTBT","TOSITBT","TTCTMOTBT","TOATTRBT","HOTRBT","TOSITRBT","TTCTMOTRBT","TOATTQA","TTRAIFTQA","TOATTQP","TTRAIFTQP","TOATTDLLA","TTRAIFTDLLA","TOATTDLLP","TTRAIFTDLLP");
	printf("Building of array of random numbers...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	array=(int*)malloc(sizeof(int)*ArraySize);
	for(i=0; i<ArraySize; i++)
		array[i]=MinNumber+rand()%(MaxNumber-MinNumber);
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %d ms = %d sec. Array:\n",EndTimeMsec,EndTime);
	ShowArray(array,ArraySize);
	CountOfEqualItems=GetCountOfEqualItems(array,ArraySize);	
	fprintf(TestFile,"%38s","Random array ");
	TestTrees(array,ArraySize,CountOfEqualItems);	
	printf("Building of array of numbers in direct order...");
	StartTime=time(&StartTime);
	StartTimeMsec=GetTickCount();
	for(i=0; i<ArraySize; i++)
		array[i]=i;
	EndTimeMsec=GetTickCount()-StartTimeMsec;
	EndTime=time(&EndTime)-StartTime;
	printf(" Time: %d ms = %d sec. Array:\n",EndTimeMsec,EndTime);
	ShowArray(array,ArraySize);
	CountOfEqualItems=GetCountOfEqualItems(array,ArraySize);	
	fprintf(TestFile,"%38s","Numbers in direct order ");
	TestTrees(array,ArraySize,CountOfEqualItems);	
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	ShuffleArray(array,ArraySize,25,1);
	ShowArray(array,ArraySize);
	CountOfEqualItems=GetCountOfEqualItems(array,ArraySize);
	fprintf(TestFile,"%38s","One sorted part makes up 25 percent ");
	TestTrees(array,ArraySize,CountOfEqualItems);
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	ShuffleThePartOfArray(array,ArraySize,10);
	ShowArray(array,ArraySize);
	CountOfEqualItems=GetCountOfEqualItems(array,ArraySize);
	fprintf(TestFile,"%38s","Array was sorted for 10 percent ");
	TestTrees(array,ArraySize,CountOfEqualItems);
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	ShuffleThePartOfArray(array,ArraySize,30);
	ShowArray(array,ArraySize);
	CountOfEqualItems=GetCountOfEqualItems(array,ArraySize);
	fprintf(TestFile,"%38s","Array was sorted for 30 percent ");
	TestTrees(array,ArraySize,CountOfEqualItems);
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	ShuffleThePartOfArray(array,ArraySize,70);
	ShowArray(array,ArraySize);
	CountOfEqualItems=GetCountOfEqualItems(array,ArraySize);
	fprintf(TestFile,"%38s","Array was sorted for 70 percent ");
	TestTrees(array,ArraySize,CountOfEqualItems);
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	GetArrayWithRegularElements(array,ArraySize,0);
	ShowArray(array,ArraySize);
	CountOfEqualItems=GetCountOfEqualItems(array,ArraySize);
	fprintf(TestFile,"%38s","Array without equal numbers ");
	TestTrees(array,ArraySize,CountOfEqualItems);	
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	GetArrayWithRegularElements(array,ArraySize,10);
	ShowArray(array,ArraySize);
	CountOfEqualItems=GetCountOfEqualItems(array,ArraySize);
	fprintf(TestFile,"%38s","Array with 10 percent of equal numbers");
	TestTrees(array,ArraySize,CountOfEqualItems);	
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	GetArrayWithRegularElements(array,ArraySize,25);
	ShowArray(array,ArraySize);
	CountOfEqualItems=GetCountOfEqualItems(array,ArraySize);
	fprintf(TestFile,"%38s","Array with 25 percent of equal numbers");
	TestTrees(array,ArraySize,CountOfEqualItems);	
	FillArray(array,ArraySize,MinNumber,MaxNumber);
	GetArrayWithRegularElements(array,ArraySize,80);
	ShowArray(array,ArraySize);
	CountOfEqualItems=GetCountOfEqualItems(array,ArraySize);
	fprintf(TestFile,"%38s","Array with 80 percent of equal numbers");
	TestTrees(array,ArraySize,CountOfEqualItems);	
	free(array);
	fclose(TestFile);
	printf("The file tests.txt was created (better seen without word wrap).");
	return 0;
}
