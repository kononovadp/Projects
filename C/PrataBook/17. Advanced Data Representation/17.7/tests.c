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
