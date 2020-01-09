//Модифицируйте программу для клуба любителей животных, так, чтобы все животные с одинаковые кличками хранились в одном и том же узле списка. Когда пользователь выбирает поиск животного, программа должна запросить кличку животного, после чего вывести список всех животных (вместе с их видами), имеющих данную кличку.
// petclub.c -- использование двоичного дерева поиска 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
char menu(void);
void addpet(Tree * pt);
void droppet(Tree * pt);
void showpets(const Tree * pt);
void findpet(const Tree * pt);
void printitem(Item item);
void uppercase(char * str);
char * s_gets(char * st, int n);
char menu(void)
{
    int ch;

    puts("Программа членства в клубе Nerfville Pet Club");
    puts("Введите букву, соответствующую вашему выбору:");
    puts("a) добавление животного   l) вывод списка животных");
    puts("n) количество животных    f) поиск животных");
    puts("d) удаление животного     q) выход");
    while ((ch = getchar()) != EOF)
    {
        while (getchar() != '\n')  /* отбросить оставшуюся часть строки */
            continue;
        ch = tolower(ch);
        if (strchr("alrfndq",ch) == NULL)
            puts("Введите букву a, l, f, n, d или q:");
        else
            break;
    }
    if (ch == EOF)       /* ввод символа EOF приводит к выходу из программы */
        ch = 'q';

    return ch;
}
void GetPetKind(char **receiver, char *source)
{
	*receiver=(char*)malloc(strlen(source)*sizeof(char));
	strcpy(*receiver,source);
}
void addpet(Tree * pt)
{
    Item temp;
	char petkind[SLEN];
    if (TreeIsFull(pt))
        puts("В клубе больше нет мест!");
    else
    {
        puts("Введите кличку животного:");
        s_gets(temp.petname,SLEN);
        puts("Введите вид животного:");
        s_gets(petkind,SLEN);
		temp.petkind=(char**)malloc(sizeof(temp.petkind));
		GetPetKind(temp.petkind,petkind);
		temp.petkinds_count=1;
        uppercase(temp.petname);
        uppercase(*temp.petkind);
        AddItem(&temp, pt);
    }
}

void showpets(const Tree * pt)
{
    if (TreeIsEmpty(pt))
        puts("Записи отсутствуют!");
    else
        Traverse(pt, printitem);
}

void printitem(Item item)
{
    if(item.petkinds_count==1)
		printf("Животное: %-19s  Вид: %s\n", item.petname,*item.petkind);
	else
	{
		printf("Все животные по кличке %s:\n",item.petname);
		for(int i=0; i<item.petkinds_count; i++)
			printf("%s\n",item.petkind[i]);
	}
}

void findpet(const Tree * pt)
{
    Item temp;
	char petkind[SLEN];
    if (TreeIsEmpty(pt))
    {
        puts("Записи отсутствуют!");
        return;     // если дерево пустое, выйти из функции 
    }

    puts("Введите кличку животного, которое хотите найти:");
    s_gets(temp.petname, SLEN);
    puts("Введите вид животного:");
    s_gets(petkind,SLEN);
	temp.petkind=(char**)malloc(sizeof(temp.petkind));
	GetPetKind(temp.petkind,petkind);
	temp.petkinds_count=1;
    uppercase(temp.petname);
    uppercase(*temp.petkind);
    printf("%s по имени %s ", *temp.petkind, temp.petname);
    if (InTree(&temp, pt))
        printf("является членом клуба.\n");
    else
        printf("не является членом клуба.\n");
	free(petkind);
}

void droppet(Tree * pt)
{
    Item temp;
	char petkind[SLEN];
    if (TreeIsEmpty(pt))
    {
        puts("Записи отсутствуют!");
        return;     // если дерево пустое, выйти из функции 
    }

    puts("Введите кличку животного, которое нужно исключить из клуба:");
    s_gets(temp.petname, SLEN);
    puts("Введите вид животного:");
    s_gets(petkind,SLEN);
	temp.petkind=(char**)malloc(sizeof(temp.petkind));
	GetPetKind(temp.petkind,petkind);
	temp.petkinds_count=1;
    uppercase(temp.petname);
    uppercase(*temp.petkind);
	bool b=DeleteItem(&temp, pt);
	if(b==true)
		printf("%s по имени %s исключен(а) из клуба.\n", *temp.petkind, temp.petname);
	else
		printf("%s по имени %s не является членом клуба.\n", *temp.petkind, temp.petname);
    /*printf("%s по имени %s ", *temp.petkind, temp.petname);
    if (DeleteItem(&temp, pt))
        printf("исключен(а) из клуба.\n");
    else
        printf("не является членом клуба.\n");*/
}

void uppercase(char * str)
{
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
}

char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');   // поиск новой строки
        if (find)                  // если адрес не равен NULL,
            *find = '\0';          // поместить туда нулевой символ
        else
            while (getchar() != '\n')
                continue;          // отбросить остаток строки
    }
    return ret_val;
}
void ReadPetsFromFile(Tree *pets)
{
	int ch,i;
    char choice,*temp,**arr=NULL;
	FILE *f=fopen("pets.txt","r");
	Item *my_pet;	
	while((ch=getc(f))!=EOF)
	{
		i=0;
		my_pet=(Item*)malloc(sizeof(Item));
		while(ch!=' ')
		{
			my_pet->petname[i]=ch;
			my_pet->petname[i+1]=0;
			ch=getc(f);
			i++;
		}
		i=0;
		temp=(char*)malloc(sizeof(char));
		while((ch=getc(f))!='\n' && ch!=EOF)
		{
			temp[i]=ch;
			i++;
			temp=(char*)realloc(temp,i*sizeof(char));
			temp[i]=0;
		}
		my_pet->petkind=(char**)malloc(sizeof(my_pet->petkind));
		GetPetKind(my_pet->petkind,temp);
		my_pet->petkinds_count=1;
		uppercase(my_pet->petname);
        uppercase(*my_pet->petkind);
		AddItem(my_pet, pets);
		free(my_pet);
	}
	fclose(f);
}

int main(void)
{
	/*int i,n=5;
	char *arr[5]={"45","dsf","56","df","bv"};
	for(int i=0; i<n; i++)
		printf("%s ",arr[i]);
	putchar('\n');
	if(DeleteString(arr,5,"45p"))
		n--;
	else
	{
		printf("Item not found");
		return 0;
	}
	for(int i=0; i<n; i++)
		printf("%s ",arr[i]);*/
	char choice;
	Tree pets;
	InitializeTree(&pets);
	ReadPetsFromFile(&pets);
	printf("Список животных из файла:\n");
	showpets(&pets);
	printf("==============================================\n");
    while ((choice = menu()) != 'q')
    {
        switch (choice)
        {
            case 'a' :  addpet(&pets);
                break;
            case 'l' :  showpets(&pets);
                break;
            case 'f' :  findpet(&pets);
                break;
            case 'n' :  printf("%d животных в клубе \n",
                               TreeItemCount(&pets));
                break;
            case 'd' :  droppet(&pets);
                break;
            default  :  puts("Ошибка в switch");
        }
		printf("==============================================\n");
    }
    DeleteAll(&pets);
    puts("Программа завершена.");
    return 0;
}
