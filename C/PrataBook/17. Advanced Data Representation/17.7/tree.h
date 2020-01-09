#include "tree.c"
void InitializeTree(tree *mytree);
struct Node *AddNode(struct Node *mynode,void *item,char ComparisonFunction
					(void*,void*), void (*ChangeItemFunction)(void*));
void ShowTree(struct Node *mynode, void ShowItem(void*));
struct Node *SearchInTree(struct Node *mynode, void *required, int *steps,
						  char (*ComparisonFunction)(void*, void*));
struct Node *GetPreviousNode(struct Node *mynode, void *next, 
							 char ComparisonFunction(void*,void*));
struct Node *GetLastItem(struct Node *receiver, void *required,
						 char ComparisonFunction(void*,void*));
void AddSubtree(struct Node *MainTree, struct Node *subtree,
				char *ComparisonFunction(void*,void*));
bool RemoveTreeNode(tree *mytree, void *required,
					char ComparisonFunction(void*,void*));
