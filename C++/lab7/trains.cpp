#include "BinTree.h"
int main()
{
	cout<<"List of all trains:";
	CBinTree *tree=NULL;
	tree=tree->readnode();
	tree->showtree(tree);
	cout<<endl<<"-------------deleted train 7-------------";
	tree=tree->deletenode(tree,7);
	tree->showtree(tree);
	cout<<endl<<"-----------------------------------------";
	tree->showtraininf(5,tree);
	tree->showstationinf("Kiev",tree);
	tree->showstationinf("Lviv",tree);
	cin.get();
}