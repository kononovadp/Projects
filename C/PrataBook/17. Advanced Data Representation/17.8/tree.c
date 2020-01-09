// tree.c -- функции поддержки дерева 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SLEN 20
#define MAXITEMS 10
// переопределение типа Item подходящим образом 
typedef struct item
{
    char petname[SLEN];
    char **petkind;//[SLEN];
	int petkinds_count;
} Item;

typedef struct trnode
{
    Item item;
    struct trnode * left;  // указатель на левую ветвь  
    struct trnode * right; // указатель на правую ветвь 
} Trnode;

typedef struct tree
{
    Trnode * root;         // указатель на корень дерева    
    int size;              // количество элементов в дереве 
} Tree;
// локальный тип данных 
typedef struct pair {
    Trnode * parent;
    Trnode * child;
} Pair;

// прототипы локальных функций 
static Trnode * MakeNode(const Item * pi);
static bool ToLeft(const Item * i1, const Item * i2);
static bool ToRight(const Item * i1, const Item * i2);
static void AddNode (Trnode * new_node, Trnode * root);
static void InOrder(const Trnode * root, void (* pfun)(Item item));
static Pair SeekItem(const Item * pi, const Tree * ptree);
static void DeleteNode(Trnode **ptr);
static void DeleteAllNodes(Trnode * ptr);

// определения функций 
void InitializeTree(Tree * ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
}

bool TreeIsEmpty(const Tree * ptree)
{
    if (ptree->root == NULL)
        return true;
    else
        return false;
}

bool TreeIsFull(const Tree * ptree)
{
    if (ptree->size == MAXITEMS)
        return true;
    else
        return false;
}

int TreeItemCount(const Tree * ptree)
{
    return ptree->size;
}
bool AddPetKind(const Item *new_item, Item *prev_item)
{
	int i;
	for(i=0; i<prev_item->petkinds_count; i++)
	if(strcmp(new_item->petkind[0],prev_item->petkind[i])==0)
		return false;
	prev_item->petkind[i]=(char*)malloc(strlen(new_item->petkind[0])*sizeof(char));
	strcpy(prev_item->petkind[prev_item->petkinds_count],new_item->petkind[0]);
	prev_item->petkinds_count=prev_item->petkinds_count+1;
	return true;
}

bool AddItem(const Item * pi, Tree * ptree)
{
    Trnode * new_node;
	Pair look;
    if  (TreeIsFull(ptree))
    {
        fprintf(stderr, "Дерево переполнено\n");
        return false;             // преждевременный возврат       
    }	
    look = SeekItem(pi, ptree);
    if (look.child != NULL)
    {
        //fprintf(stderr, "Попытка добавления дублированного элемента\n");
		if(AddPetKind(pi,&look.child->item))
		{
			ptree->size++;			
			return true;
		}
		else
			return false;             // преждевременный возврат
    }
    new_node = MakeNode(pi);      // указывает на новый узел       
    if (new_node == NULL)
    {
        fprintf(stderr, "Не удалось создать узел\n");
        return false;             // преждевременный возврат       
    }
    // успешное создание нового узла 
    ptree->size++;

    if (ptree->root == NULL)      // случай 1: дерево пустое       
        ptree->root = new_node;   // новый узел – корень дерева    
    else                          // случай 2: дерево не пустое    
        AddNode(new_node,ptree->root); // добавление узла к дереву 

    return true;                  // возврат в случае успеха       
}

bool InTree(const Item * pi, const Tree * ptree)
{
    //return (SeekItem(pi, ptree).child == NULL) ? false : true;
	Pair look=SeekItem(pi, ptree);
	if(look.child == NULL)
		return false;
	else
		for(int i=0; i<look.child->item.petkinds_count; i++)
			if(strcmp(look.child->item.petkind[i],*pi->petkind)==0)
				return true;
	return false;
}
bool DeleteString(char **arr, int count, char *str)
{
	int i=0;
	while(i<count && strcmp(arr[i],str)!=0)
		i++;
	if(i==count)
		return false;
	for(; i<count; i++)
		arr[i]=arr[i+1];
	return true;
}
bool DeleteItem(const Item * pi, Tree * ptree)
{
    Pair look;
	
    look = SeekItem(pi, ptree);
    if (look.child == NULL)
        return false;
	if(look.child->item.petkinds_count>1)
	{		
		if(DeleteString(look.child->item.petkind,look.child->item.petkinds_count,*pi->petkind)==true)
		{
			look.child->item.petkinds_count=look.child->item.petkinds_count-1;
			ptree->size--;
			return true;
		}
		else
			return false;
	}
    if (look.parent == NULL)      /* удаление корневого элемента */
        DeleteNode(&ptree->root);
    else if (look.parent->left == look.child)
        DeleteNode(&look.parent->left);
    else
        DeleteNode(&look.parent->right);
    ptree->size--;

    return true;
}

void Traverse (const Tree * ptree, void (* pfun)(Item item))
{

    if (ptree != NULL)
        InOrder(ptree->root, pfun);
}

void DeleteAll(Tree * ptree)
{
    if (ptree != NULL)
        DeleteAllNodes(ptree->root);
    ptree->root = NULL;
    ptree->size = 0;
}

// локальные функции 
static void InOrder(const Trnode * root, void (* pfun)(Item item))
{
    if (root != NULL)
    {
        InOrder(root->left, pfun);
        (*pfun)(root->item);
        InOrder(root->right, pfun);
    }
}

static void DeleteAllNodes(Trnode * root)
{
    Trnode * pright;

    if (root != NULL)
    {
        pright = root->right;
        DeleteAllNodes(root->left);
        free(root);
        DeleteAllNodes(pright);
    }
}

static void AddNode (Trnode * new_node, Trnode * root)
{
    if (ToLeft(&new_node->item, &root->item))
    {
        if (root->left == NULL)      // пустое поддерево,          
            root->left = new_node;   // поэтому добавить сюда узел 
        else
            AddNode(new_node, root->left); // иначе обработать поддерево 
    }
    else if (ToRight(&new_node->item, &root->item))
    {
        if (root->right == NULL)
            root->right = new_node;
        else
            AddNode(new_node, root->right);
    }
    else                         // дубликаты не допускаются 
    {
        fprintf(stderr, "Ошибка местоположения в AddNode()\n");
        exit(1);
    }
}

static bool ToLeft(const Item * i1, const Item * i2)
{
    int comp1;

    if ((comp1 = strcmp(i1->petname, i2->petname)) < 0)
        return true;
    /*else if (comp1 == 0 &&
             strcmp(i1->petkind, i2->petkind) < 0 )
        return true;*/
    else
        return false;
}

static bool ToRight(const Item * i1, const Item * i2)
{
    int comp1;

    if ((comp1 = strcmp(i1->petname, i2->petname)) > 0)
        return true;
    /*else if (comp1 == 0 &&
             strcmp(i1->petkind, i2->petkind) > 0 )
        return true;*/
    else
        return false;
}

static Trnode * MakeNode(const Item * pi)
{
    Trnode * new_node;

    new_node = (Trnode *) malloc(sizeof(Trnode));
    if (new_node != NULL)
    {
        new_node->item = *pi;
        new_node->left = NULL;
        new_node->right = NULL;
    }

    return new_node;
}

static Pair SeekItem(const Item * pi, const Tree * ptree)
{
    Pair look;
    look.parent = NULL;
    look.child = ptree->root;

    if (look.child == NULL)
        return look;  /* преждевременный возврат */

    while (look.child != NULL)
    {
        if (ToLeft(pi, &(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->left;
        }
        else if (ToRight(pi, &(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->right;
        }
        else       /* если элемент не расположен ни слева, ни справа, он должен быть таким же */
            break; /* look.child - это адрес узла, содержащего элемент */
    }

    return look;   /* возврат в случае успеха   */
}

static void DeleteNode(Trnode **ptr)
/* адрес родительского элемента, указывающего на целевой узел */
{
    Trnode * temp;

    if ( (*ptr)->left == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->right;
        free(temp);
    }
    else if ( (*ptr)->right == NULL)
    {
        temp = *ptr;
        *ptr = (*ptr)->left;
        free(temp);
    }
    else    /* удаляемый узел имеет два дочерних узла */
    {
        /* выяснение места присоединения правого поддерева */
        for (temp = (*ptr)->left; temp->right != NULL;
             temp = temp->right)
            continue;
        temp->right = (*ptr)->right;
        temp = *ptr;
        *ptr =(*ptr)->left;
        free(temp);
    }
}

