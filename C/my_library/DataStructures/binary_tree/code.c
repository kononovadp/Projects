/*Напишите программу, которая открывает и считывает текстовый файл, фиксируя количество повторений в нем каждого слова. Используйте двоичное дерево поиска, модифицированное для хранения слова и количество его повторений. После того как программа прочитает файл, она должна отобразить меню, состоящее из трех пунктов. Первый пункт приводит к выводу списка всех слов с указанием их повторений. Второй обеспечивает возможность ввода слова, а программа должна сообщить количество вхождений этого слова в файле. Результатом третьего пункта меню должен быть выход из программы.*/
#include "tree.h"
#include "tests.h"
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
	MainTask();
	TestIntType();
	TestCharArraySorting();
	return 0;
}