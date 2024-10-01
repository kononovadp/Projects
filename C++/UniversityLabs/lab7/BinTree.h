#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "TreeNode.h"
using namespace std;
struct CBinTree
{
	CBinTree()
	{
		l=NULL;
		r=NULL;
	}
	bool st_b;
	CTreeNode *data;
	CBinTree *l,*r;

void addnode(CTreeNode *node,CBinTree *&tree);
void showtree(CBinTree *&tree);
CBinTree *readnode();
CBinTree* findtraininf(int tr,CBinTree *tree);
void showtraininf(int train,CBinTree *tree);
void findstationinf(string station,CBinTree *tree);
void showstationinf(string station,CBinTree *tree);
int minimum(CBinTree *&tree);
CBinTree *deletenode(CBinTree *&tree,int n);
};