typedef struct IntItem
{
	int number;
}intitem;
typedef struct Word
{
	char *word;
	int repeats_count;
}worditem;
typedef struct PetItem
{
	char *petname;
	char **petkinds;
	int petkinds_count;
}petitem;
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
void ShowPetItem(petitem *my_item)
{
	if(my_item==NULL)
	{
		printf("No pets found.\n");
		return;
	}
	if(my_item->petkinds_count==1)
		printf("Pets name: %s; type: %s\n",my_item->petname,my_item->petkinds[0]);
	else
	{
		printf("All types of the pet %s:\n",my_item->petname);
		for(int i=0; i<my_item->petkinds_count; i++)
			printf("%10s\n",my_item->petkinds[i]);
	}
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
char ComparePetItems(petitem *new_item, petitem *prev_item)
{
	char comparison_result=CompareCharArrays(new_item->petname,prev_item->petname);
	if(comparison_result=='>')
		return '>';
	else
		if(comparison_result=='<')
			return '<';
		else
		{
			int i;
			for(i=0; i<prev_item->petkinds_count; i++)
				if(strcmp(new_item->petkinds[0],prev_item->petkinds[i])==0)
					return '=';
			prev_item->petkinds[i]=(char*)malloc(strlen(new_item->petkinds[0])*sizeof(char));
			strcpy(prev_item->petkinds[prev_item->petkinds_count],new_item->petkinds[0]);			
			prev_item->petkinds_count=prev_item->petkinds_count+1;
			return '=';
		}
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
