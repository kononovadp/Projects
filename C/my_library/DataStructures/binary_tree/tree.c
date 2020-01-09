#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "items.h"
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
void InitializeTree(tree *mytree)
{
	mytree->root=NULL;
}
struct Node *AddNode(struct Node *mynode, void *item, 
char *ComparisonFunction(void*,void*), void (*ChangeItemFunction)(void*))
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
		if((ComparisonFunction(mynode->item,item))=='=' &&
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
struct Node *GetPreviousNode(struct Node *mynode, void *next, char *ComparisonFunction(void*,void*))
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
					char *ComparisonFunction(void*,void*))
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
