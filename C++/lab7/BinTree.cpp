#include "BinTree.h"
void CBinTree::addnode(CTreeNode *node,CBinTree *&tree)
{
	if (tree==NULL)
	{
		tree=new CBinTree;
		tree->data=node;
		tree->l=tree->r=NULL;
	}
	else
	if(node->GetTrainNumber()<tree->data->GetTrainNumber())
		addnode(node,tree->l);
	else
		addnode(node,tree->r);
}
void CBinTree::showtree(CBinTree *&tree)
{
	if(tree!=NULL)
	{
		showtree(tree->l);
		tree->data->Display();
		showtree(tree->r);
	}
}
CBinTree* CBinTree::readnode()
{
		ifstream f;
		f.open("1.txt");
		string s;
		int i=0;
		CBinTree *tree=NULL;
		while(!f.eof())
		{
			f>>s;
			int t=s.find_first_of(";");
			string temp=s.substr(0,t);
			istringstream v1 (temp, istringstream::in);
			int trainn;
			v1>>trainn;
			s=s.erase(0,t+1);
			t=s.find_first_of(";");
			string dest=s.substr(0,t);
			s=s.erase(0,t+1);
			t=s.find_first_of(";");
			string dep=s.substr(0,t);			
			CTreeNode *obj=new CTreeNode(trainn,dest,dep);
			addnode(obj,tree);
			//cout<<trainn<<"|"<<dest<<"|"<<dep<<"|"<<endl;
		}		
		f.close();
		return tree;
}
CBinTree* CBinTree::findtraininf(int tr,CBinTree *tree)
{
	if((tree==NULL)||(tree->data->GetTrainNumber()==tr))
		return tree;
	if(tr<tree->data->GetTrainNumber())
		return findtraininf(tr,tree->l);
		else
			return findtraininf(tr,tree->r);
}

void CBinTree::showtraininf(int train,CBinTree *tree)
{
	cout<<endl<<"Information about train No "<<train;
	CBinTree *t=findtraininf(train,tree);	
	if (t!=NULL)
		t->data->Display();
	else 
		cout<<" not found";
}
//*****************************************************************
/*CBinTree* CBinTree::stinf_exist(string st,CBinTree *tree)
{
	if ((tree==NULL)||(tree->data->GetStationName()==st))
		return tree;
	if(tree!=NULL)
	{
		stinf_exist(st,tree->l);			
		stinf_exist(st,tree->r);			
	}
	return NULL;
}*/

void CBinTree::findstationinf(string station,CBinTree *tree)
{
	if ((tree!=NULL)&&(tree->data->GetStationName()==station))
	{
		tree->data->Display();
		st_b=true;
	}
	if(tree!=NULL)
	{
		findstationinf(station,tree->l);			
		findstationinf(station,tree->r);			
	}
}
void CBinTree::showstationinf(string station,CBinTree *tree)
{
	cout<<endl<<"Information about trains bound for "<<station;
	st_b=false;
	findstationinf(station,tree);
	if (st_b==false)
		cout<<" not found";
	st_b=false;
}
int CBinTree::minimum(CBinTree *&tree)
{
	if(tree->l==NULL)
		return (tree->data->GetTrainNumber());
	return minimum(tree->l);
}
CBinTree* CBinTree::deletenode(CBinTree *&tree,int n)
{
	if(tree==NULL)
	return tree;
	if(n<tree->data->GetTrainNumber())
		tree->l=deletenode(tree->l,n);
	else
		if(n>tree->data->GetTrainNumber())
			tree->r=deletenode(tree->r,n);
		else
			if ((tree->l!=NULL)&&(tree->r!=NULL))
			{
				int t=minimum(tree->r);
				tree->data->SetTrainNumber(t);
				tree->r=deletenode(tree->r,tree->r->data->GetTrainNumber());				
			}
			else
				if(tree->l!=NULL)
					tree=tree->l;
				else
					tree=tree->r;
				return tree;
}