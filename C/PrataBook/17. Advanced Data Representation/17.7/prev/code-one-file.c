/*Напишите программу, которая открывает и считывает текстовый файл, фиксируя количество повторений в нем каждого слова. Используйте двоичное дерево поиска, модифицированное для хранения слова и количество его повторений. После того как программа прочитает файл, она должна отобразить меню, состоящее из трех пунктов. Первый пункт приводит к выводу списка всех слов с указанием их повторений. Второй обеспечивает возможность ввода слова, а программа должна сообщить количество вхождений этого слова в файле. Результатом третьего пункта меню должен быть выход из программы.*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct IntItem
{
	int number;
}intitem;
typedef struct Word
{
	char *word;
	int repeats_count;
}worditem;
typedef struct Node
{
	void *item;
	struct Node *left;
	struct Node *right;
}node;
typedef struct Tree
{
	struct Node *root;
}tree;
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
void InitializeTree(tree *mytree)
{
	mytree->root=NULL;
}
struct Node *AddNode(struct Node *mynode, void *item, 
char ComparisonFunction(void*,void*), void (*ChangeItemFunction)(void*))
{
	if(mynode==NULL)
	{
		mynode=(struct Node*)malloc(sizeof(node));
		mynode->item=item;
		mynode->left=NULL;
		mynode->right=NULL;
		return mynode;
	}
	else
		if(ComparisonFunction(mynode->item,item)=='=' &&
		   ChangeItemFunction!=NULL)
			ChangeItemFunction(mynode->item);
		else
			if(ComparisonFunction(item,mynode->item)=='>')
				mynode->right=AddNode(mynode->right,item,
							  ComparisonFunction,ChangeItemFunction);
			else
				if(ComparisonFunction(item,mynode->item)=='<')
					mynode->left=AddNode(mynode->left,item,
								 ComparisonFunction,ChangeItemFunction);
	return mynode;
}
void ShowTree(struct Node *mynode, void ShowItem(void*))
{
	if(mynode==NULL)
	{
		printf("No tree elements found!");
		return;
	}
	
	if(mynode->left!=NULL)
		ShowTree(mynode->left,ShowItem);
	ShowItem(mynode->item);
	if(mynode->right!=NULL)
		ShowTree(mynode->right,ShowItem);
}
struct Node *SearchInTree(struct Node *mynode, void *required, int *steps,
						  char (*ComparisonFunction)(void*, void*))
{
	*steps=*steps+1;
	if(mynode==NULL)
		return NULL;
	if(ComparisonFunction(mynode->item,required)=='=')
		return mynode;
	else
		if(ComparisonFunction(required,mynode->item)=='<')
			SearchInTree(mynode->left,required,steps,ComparisonFunction);
		else
			if(ComparisonFunction(required,mynode->item)=='>')
				SearchInTree(mynode->right,required,steps, ComparisonFunction);
}
void TestIntNodeSearch(tree *mytree)
{
	int steps=0;
	int required;
	struct Node *search_result;
	putchar('\n');
	printf("Enter a number or no number to exit: ");
	while(scanf("%d",&required))
	{
		steps=0;
		search_result=SearchInTree(mytree->root,CreateIntItem(required),&steps,CompareIntItems);
		if(search_result!=NULL)
		{
			printf("Number found: ");
			ShowIntItem(search_result->item);
			putchar('\n');
		}
		else
			printf("Number NOT found; ");
		printf("steps count: %d\n",steps);
		printf("Enter a number or no number to exit: ");
	}
}
struct Node *GetPreviousNode(struct Node *mynode, void *next, char ComparisonFunction(void*,void*))
{
	if(mynode==NULL)
		return NULL;
	if(mynode->right!=NULL)
		if(ComparisonFunction(next,mynode->right->item)=='=')
			return mynode;
	if(mynode->left!=NULL)
		if(ComparisonFunction(next,mynode->left->item)=='=')
			return mynode;
	if(ComparisonFunction(next,mynode->item)=='<')
		return GetPreviousNode(mynode->left,next,ComparisonFunction);
	if(ComparisonFunction(next,mynode->item)=='>')
		return GetPreviousNode(mynode->right,next,ComparisonFunction);
}
struct Node *GetLastItem(struct Node *receiver, void *required,
						 char ComparisonFunction(void*,void*))
{
	if(receiver==NULL)
		return NULL;
	if(receiver->left==NULL && ComparisonFunction(required,receiver->item)=='<')
		return receiver;
	if(receiver->right==NULL && ComparisonFunction(required,receiver->item)=='>')
		return receiver;
	if(receiver->right==NULL && receiver->left==NULL)
		return receiver;
	if(ComparisonFunction(required,receiver->item)=='>')
		if(receiver->right!=NULL)
			GetLastItem(receiver->right,required,ComparisonFunction);
	if(ComparisonFunction(required,receiver->item)=='<')
		if(receiver->left!=NULL)
			GetLastItem(receiver->left,required,ComparisonFunction);
}
void AddSubtree(struct Node *MainTree, struct Node *subtree,
				char *ComparisonFunction(void*,void*))
{
	if(subtree==NULL)
		return;
	AddNode(MainTree,subtree->item,ComparisonFunction,NULL);
	if(subtree->right!=NULL)
		AddSubtree(MainTree,subtree->right,ComparisonFunction);	
	if(subtree->left!=NULL)
		AddSubtree(MainTree,subtree->left,ComparisonFunction);
}
bool RemoveTreeNode(tree *mytree, void *required,
					char ComparisonFunction(void*,void*))
{
	struct Node *PreviousNode=NULL;
	struct Node *LastItem=NULL;
	struct Node *DeletedNode=NULL;
	if(mytree->root==NULL)
		return false;	
	if(ComparisonFunction(required,mytree->root->item)=='=')
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
			AddSubtree(mytree->root,PreviousNode->left,ComparisonFunction);
			/*LastItem=GetLastItem(mytree->root,PreviousNode->left->num);
			if(PreviousNode->left->num>LastItem->num)
				LastItem->right=PreviousNode->left;
			else
				LastItem->left=PreviousNode->left;*/
		}
		return true;
	}
	if((PreviousNode=GetPreviousNode(mytree->root,required,ComparisonFunction))==NULL)
		return false;
	if(PreviousNode->right!=NULL)
		if(ComparisonFunction(required,PreviousNode->right->item)=='=')
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
				AddSubtree(mytree->root,DeletedNode->right,ComparisonFunction);
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
			AddSubtree(mytree->root,DeletedNode->left,ComparisonFunction);
		return true;
	}
	return false;
}
void TestIntNodeRemoving(tree *mytree, int *arr, int ElementsCount)
{
	int RandomNumber;
	while(mytree->root!=NULL)//for(int i=0; i<ElementsCount-1; i++)
	{
		RandomNumber=rand()%ElementsCount;
		if((RemoveTreeNode(mytree,CreateIntItem(arr[RandomNumber]),
			CompareIntItems))==true)
		{
			printf("Deleted element %d under array index %d\n",arr[RandomNumber],		RandomNumber);
			ShowTree(mytree->root,ShowIntItem);
		}
		else
			printf("Element %d NOT FOUND",arr[RandomNumber]);
		putchar('\n');
	}
}
void TestIntType(void)
{
	tree mytree;	
	int n=10;
	int arr[n];
	int required,steps=0;
	struct Node*search_result;
	InitializeTree(&mytree);
	srand((unsigned int) time(0));	
	for(int i=0; i<n; i++)
		arr[i]=rand()%99;
	printf("Array:\n");
	ShowArray(arr,n);	
	if(n<=0)
		return;
	mytree.root=AddNode(mytree.root,CreateIntItem(arr[0]),CompareIntItems,NULL);
	for(int i=1; i<n; i++)
		AddNode(mytree.root,CreateIntItem(arr[i]),CompareIntItems,NULL);
	printf("\nTree:\n");
	ShowTree(mytree.root,ShowIntItem);
	putchar('\n');
	TestIntNodeSearch(&mytree);
	TestIntNodeRemoving(&mytree,arr,n);
}
void SortWordsArray(char **arr, int words_count)
{
	char *temp;
	int main_word,current_word;
	bool sorted=false;
	while(sorted==false)
	{
		sorted=true;
		for(main_word=0; main_word<words_count; main_word++)
			for(current_word=main_word; current_word<words_count; current_word++)
				if((CompareCharArrays(arr[main_word],arr[current_word]))=='>')
				{					
					temp=(char*)malloc(sizeof(char)*strlen(arr[main_word]));
					strcpy(temp,arr[main_word]);					
					if(strlen(arr[main_word])<strlen(arr[current_word]))
						arr[main_word]=(char*)realloc(arr[main_word],sizeof(char*)*strlen(arr[current_word]));
					strcpy(arr[main_word],arr[current_word]);
					if(strlen(arr[current_word])<strlen(temp))
						arr[current_word]=(char*)realloc(arr[current_word],sizeof(char*)*strlen(temp));
					strcpy(arr[current_word],temp);
					sorted=false;
					free(temp);
				}
	}
}
void TestCharArraySorting(void)
{
	FILE *f=fopen("test.txt","r");
	int ch;
	int symbols_count,words_count=0;
	char *word=(char*)malloc(sizeof(char));
	char **words=(char**)malloc(sizeof(char*));;
	while((ch=getc(f))!=EOF)
	{
		while(ch==' ')
			ch=getc(f);		
		symbols_count=0;
		while(ch!=EOF && ch!=' ')
		{
			
			symbols_count++;
			word=(char*)realloc(word,1+symbols_count*sizeof(char));
			word[symbols_count-1]=ch;
			word[symbols_count]='\0';
			ch=getc(f);
		}
		words_count++;
		words=(char**)realloc(words,1+sizeof(char*)*words_count);
		words[words_count-1]=word;
		//printf("%s\n",word);
		while(ch==' ')
			ch=getc(f);
		if(ch!=' ')
			ungetc(ch,f);
		word=NULL;
	}
	printf("-------------Unsorted array-------------\n");
	for(int i=0; i<words_count; i++)
		printf("%s\n",words[i]);
	printf("-------------Sorted array-------------\n");
	SortWordsArray(words,words_count);
	for(int i=0; i<words_count; i++)
		printf("%s\n",words[i]);
	fclose(f);
}
void AddWordsFromFileToTree(tree *mytree)
{
	worditem *tree_item;
	FILE *f=fopen("test.txt","r");
	int ch,search_steps_count,symbols_count=0;
	char *word=(char*)malloc(sizeof(char));
	struct Node *search_result;
	
	while((ch=getc(f))==' ' && ch!=EOF);
	if(ch!=' ')
		ungetc(ch,f);
	while((ch=getc(f))!=' ' && ch!=EOF)
	{
		symbols_count++;
		word[symbols_count-1]=ch;
		word=(char*)realloc(word,1+sizeof(word)*symbols_count);
		word[symbols_count]=0;
	}
	tree_item=CreateWordItem(word);
	mytree->root=AddNode(mytree->root,tree_item,CompareWordItems,NULL);	
	while(ch!=EOF)
	{
		symbols_count=0;
		search_steps_count=0;
		while((ch=getc(f))==' ' && ch!=EOF);
		if(ch!=' ')
			ungetc(ch,f);
		while((ch=getc(f))!=' ' && ch!=EOF)
		{
			symbols_count++;
			word[symbols_count-1]=ch;
			word=(char*)realloc(word,sizeof(word)*symbols_count);
			word[symbols_count]=0;
		}		
		AddNode(mytree->root,CreateWordItem(word),CompareWordItems,ChangeWordRepeatsCount);
		while((ch=getc(f))==' ' && ch!=EOF);
		if(ch!=' ')
			ungetc(ch,f);
	}	
	fclose(f);
}
void ShowWordsOccurrenceCount(tree *mytree)
{
	char *word=(char*)malloc(50*sizeof(char));
	struct Node *search_result;
	int steps=0;
	printf("\nEnter word to find (not more then 50 symbols): ");
	scanf("%s",word);
	search_result=SearchInTree(mytree->root,CreateWordItem(word),&steps,	CompareWordItems);
	if(search_result!=NULL)
		ShowWordItem(search_result->item);
	else
		printf("Word not found. Search steps count: %d\n",steps);
}
void MainTask(void)
{
	char ch;
	tree mytree;
	InitializeTree(&mytree);
	AddWordsFromFileToTree(&mytree);
	printf("1. Show words in tree; 2. Show words occurrence count;"
		   " 3. exit;\nYour choise: ");
	ch=_getche();
	while(ch!='3')
	{
		switch(ch)
		{
			case '1':putchar('\n');ShowTree(mytree.root,ShowWordItem);break;
			case '2': ShowWordsOccurrenceCount(&mytree); break;
			default: printf("\nChoose correct command\n");
		}
		if(ch!='\n')
			printf("------------------------------------------------------"
				 "\n1. Show words in tree; 2. Show words occurrence count;"
				 " 3. exit;\nYour choise: ");
		ch=_getche();
	}
}
int main(void)
{
	//MainTask();
	TestIntType();
	//TestCharArraySorting();
	return 0;
}
