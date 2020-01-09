/*Напишите программу, которая открывает и считывает текстовый файл, фиксируя количество появлений в нем каждого слова. Используйте двоичное дерево поиска, модифицированное для хранения слова и количество его повторений. После того как программа прочитает файл, она должна отобразить меню, состоящее из трех пунктов. Первый пункт приводит к выводу списка всех слов с указанием их повторений. Второй обеспечивает возможность ввода слова, а программа должна сообщить количество вхождений этого слова в файле. Результатом третьего пункта меню должен быть выход из программы.*/
#include <stdio.h>
#include <stdbool.h>
typedef struct Node
{
	int num;
	struct Node *left;
	struct Node *right;
}node;
typedef struct Tree
{
	struct Node *root;
}tree;
void InitTree(tree *mytree)
{
	mytree->root=NULL;
}
void ShowArray(int *arr, int n)
{
	for(int i=0; i<n; i++)
	{
		if(i!=0 && i%10==0)
			putchar('\n');
		printf("%d ",arr[i]);
	}
}
struct Node *AddNode(struct Node *mynode, int n)
{
	if(mynode==NULL)
	{
		mynode=(struct Node*)malloc(sizeof(node));
		mynode->num=n;
		mynode->left=NULL;
		mynode->right=NULL;
		return mynode;
	}
	else
		if(mynode->num<n)
			mynode->right=AddNode(mynode->right,n);
		else
			if(mynode->num>n)
				mynode->left=AddNode(mynode->left,n);
	return mynode;
}
void ShowTree(struct Node *mynode)
{	
	if(mynode==NULL)
		printf("No tree elements found!");
	else
	{		
		if(mynode->left!=NULL)
			ShowTree(mynode->left);
		printf("%d ",mynode->num);
		if(mynode->right!=NULL)
			ShowTree(mynode->right);
	}
}
bool SearchInTree(struct Node *mynode, int n, int *steps)
{
	*steps=*steps+1;
	if(mynode==NULL)
		return false;
	if(mynode->num==n)
		return true;
	else
		if(n<mynode->num)
			SearchInTree(mynode->left, n, steps);
		else
			if(n>mynode->num)
				SearchInTree(mynode->right, n, steps);
}
void TestSearch(tree *mytree)
{
	int steps=0;
	int required;
	putchar('\n');
	printf("Enter a number or no number to exit: ");
	while(scanf("%d",&required))
	{
		steps=0;
		if(SearchInTree(mytree->root,required,&steps)==true)
			printf("Number found; ");
		else
			printf("Number NOT found; ");
		printf("steps count: %d\n",steps);
		printf("Enter a number or no number to exit: ");
	}
}
struct Node *GetPreviousNode(struct Node *mynode, int n)
{
	if(mynode==NULL)
		return NULL;
	if(mynode->right!=NULL)
		if(mynode->right->num==n)
			return mynode;
	if(mynode->left!=NULL)
		if(mynode->left->num==n)
			return mynode;
	if(n<mynode->num)
		return GetPreviousNode(mynode->left,n);
	if(n>mynode->num)
		return GetPreviousNode(mynode->right,n);
}
struct Node *GetLastItem(struct Node *receiver, int n)
{
	if(receiver==NULL)
		return NULL;
	if(receiver->left==NULL && n<receiver->num)
		return receiver;
	if(receiver->right==NULL && n>receiver->num)
		return receiver;
	if(receiver->right==NULL && receiver->left==NULL)
		return receiver;
	if(n>receiver->num)
		if(receiver->right!=NULL)
			GetLastItem(receiver->right,n);
	if(n<receiver->num)
		if(receiver->left!=NULL)
			GetLastItem(receiver->left,n);
}
void AddSubtree(struct Node *MainTree, struct Node *subtree)
{
	if(subtree==NULL)
		return;
	AddNode(MainTree,subtree->num);
	if(subtree->right!=NULL)
		AddSubtree(MainTree,subtree->right);
	if(subtree->left!=NULL)
		AddSubtree(MainTree,subtree->left);
}
bool RemoveTreeNode(tree *mytree, int n)
{
	struct Node *PreviousNode=NULL;
	struct Node *LastItem=NULL;
	struct Node *DeletedNode=NULL;
	if(mytree->root==NULL)
		return false;	
	if(n==mytree->root->num)
	{
		if(mytree->root->right==NULL && mytree->root->left==NULL)
		{
			mytree->root=NULL;
			return true;
		}
		PreviousNode=mytree->root;
		if(mytree->root->right!=NULL)
			mytree->root=mytree->root->right;
		else
			if(mytree->root->left!=NULL)
			{
				mytree->root=mytree->root->left;
				return true;
			}
		if(PreviousNode->left!=NULL)
		{
			AddSubtree(mytree->root,PreviousNode->left);
			/*LastItem=GetLastItem(mytree->root,PreviousNode->left->num);
			if(PreviousNode->left->num>LastItem->num)
				LastItem->right=PreviousNode->left;
			else
				LastItem->left=PreviousNode->left;*/
		}
		return true;
	}
	if((PreviousNode=GetPreviousNode(mytree->root,n))==NULL)
		return false;
	if(PreviousNode->right!=NULL)
		if(PreviousNode->right->num==n)
		{
			DeletedNode=PreviousNode->right;
			if(DeletedNode->right==NULL && DeletedNode->left==NULL)
			{
				PreviousNode->right=NULL;
				return true;
			}
			if(DeletedNode->left!=NULL)
				PreviousNode->right=DeletedNode->left;
			else
			{
				PreviousNode->right=DeletedNode->right;
				return true;
			}
			if(DeletedNode->right!=NULL)
				AddSubtree(mytree->root,DeletedNode->right);
			return true;
		}
	else
	{
		DeletedNode=PreviousNode->left;
		if(DeletedNode->right==NULL && DeletedNode->left==NULL)
		{
			PreviousNode->left=NULL;
			return true;
		}
		if(DeletedNode->right!=NULL)
			PreviousNode->left=DeletedNode->right;
		else
		{
			PreviousNode->left=DeletedNode->left;
			return true;
		}
		if(DeletedNode->left!=NULL)
			AddSubtree(mytree->root,DeletedNode->left);
		return true;
	}
	return false;
}
void TestNodeRemoving(tree *mytree, int *arr, int ElementsCount)
{
	int RandomNumber;
	while(mytree->root!=NULL)//for(int i=0; i<ElementsCount-1; i++)
	{
		RandomNumber=rand()%ElementsCount; //arr[RandomNumber] //mytree->root->num
		if((RemoveTreeNode(mytree,arr[RandomNumber]))==true)
		{
			printf("Deleted element %d under index %d\n",arr[RandomNumber],		RandomNumber);
			ShowTree(mytree->root);
		}
		else
			printf("Element %d NOT FOUND",arr[RandomNumber]);
		putchar('\n');
	}
}
int main(void)
{
	int n=10;
	int arr[n];
	int steps=0;
	int required;
	tree mytree;
	srand((unsigned int) time(0));
	printf("Array:\n");
	for(int i=0; i<n; i++)
		arr[i]=rand()%99;
	ShowArray(arr,n);
	InitTree(&mytree);
	if(n<=0)
		return 0;
	mytree.root=AddNode(mytree.root,arr[0]);
	for(int i=1; i<n; i++)
		AddNode(mytree.root,arr[i]);
	printf("\nTree:\n");
	ShowTree(mytree.root);
	putchar('\n');
	//TestNodeRemoving(&mytree,arr,n);
	/*printf("Enter a number or no number to exit: ");
	while(scanf("%d",&required) && mytree.root!=NULL)
	{
		steps=0;
		if(RemoveTreeNode(&mytree,required)==true)
		{
			printf("Number deleted\n");
			ShowTree(mytree.root);
			putchar('\n');
		}
		else
			printf("Number NOT FOUND\n");
		printf("Enter a number or no number to exit: ");
	}*/
	TestSearch(&mytree);
	return 0;
}
