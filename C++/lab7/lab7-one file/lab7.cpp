#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
bool st_b=false;
using namespace std;
class CTreeNode
{
public:
	CTreeNode(){};
	CTreeNode(int tn,string dest,string depart)
	{
		m_TrainNumber=tn;
		m_Destination=dest;
		m_DepartureTime=depart;
	};
	void Display()
	{
		cout<<endl<<"Train number "<<m_TrainNumber<<" Destination "<<m_Destination
		<<" Departure time "<<m_DepartureTime;
	}
	int GetTrainNumber()
	{
		if (m_TrainNumber!=NULL)
			return m_TrainNumber;
	}
	string GetStationName()
	{
		if (m_Destination!="")
			return m_Destination;
	}
	void SetTrainNumber(int n)
	{
		m_TrainNumber=n;
	}
protected:
	int m_TrainNumber;
	string m_Destination;
	string m_DepartureTime;
};
struct CBinTree
{
	CBinTree()
	{
		l=NULL;
		r=NULL;
	}
	CTreeNode *data;
	CBinTree *l,*r;

/*void addnode(CTreeNode *node,CBinTree *&tree)
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
}*/
void addnode(CTreeNode *node,CBinTree *&tree)
{
	if (tree==NULL)
	{
		tree=new CBinTree;
		tree->data=node;
		tree->l=tree->r=NULL;
	}
	else
	if(node->GetTrainNumber()<tree->data->GetTrainNumber())
	{
		if(tree->l!=NULL)
			addnode(node,tree->l);
		else
			{
				tree->l=new CBinTree;
				tree->l->l=tree->l->r=NULL;
				tree->l->data=node;			
			}
	}
	else
	if((node->GetTrainNumber()>tree->data->GetTrainNumber())
	||(node->GetTrainNumber()==tree->data->GetTrainNumber()))
	{
		if(tree->r!=NULL)
			addnode(node,tree->r);
			else
			{
				tree->r=new CBinTree;
				tree->r->r=tree->r->l=NULL;
				tree->r->data=node;
			}
	}
}
void showtree(CBinTree *&tree)
{
	if(tree!=NULL)
	{
		showtree(tree->l);
		tree->data->Display();
		showtree(tree->r);
	}
}
CBinTree *readnode()
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
		//tree->showtree(tree);
		f.close();
		return tree;
}
CBinTree* findtraininf(int tr,CBinTree *tree)
{
	if((tree==NULL)||(tree->data->GetTrainNumber()==tr))
		return tree;
	if(tr<tree->data->GetTrainNumber())
		return findtraininf(tr,tree->l);
		else
			return findtraininf(tr,tree->r);
}

void showtraininf(int train,CBinTree *tree)
{
	cout<<endl<<"Information about train No "<<train;
	CBinTree *t=findtraininf(train,tree);	
	if (t!=NULL)
		t->data->Display();
	else 
		cout<<" not found";
}
//*****************************************************************
CBinTree* stinf_exist(string st,CBinTree *tree)
{
	if ((tree==NULL)||(tree->data->GetStationName()==st))
		return tree;
	if(tree!=NULL)
	{
		stinf_exist(st,tree->l);			
		stinf_exist(st,tree->r);			
	}
	return NULL;
}

void findstationinf(string station,CBinTree *tree)
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
void showstationinf(string station,CBinTree *tree)
{
	cout<<endl<<"Information about trains bound for "<<station;
	findstationinf(station,tree);
	if (st_b==false)
		cout<<"not found";
}
int minimum(CBinTree *&tree)
{
	if(tree->l==NULL)
		return (tree->data->GetTrainNumber());
	return minimum(tree->l);
}
CBinTree *deletenode(CBinTree *&tree,int n)
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
/*Node delete(root : Node, z : T): // корень поддерева, удаляемый ключ
  if root == null
    return root
  if z < root.key
    root.left = delete(root.left, z)
  else if z > root.key
    root.right = delete(root.right, z)
  else if root.left != null and root.right != null
    root.key = minimum(root.right).key
    root.right = delete(root.right, root.right.key)
  else
    if root.left != null
      root = root.left
    else
      root = root.right
  return root*/
};
int main()
{
	CBinTree *tree=NULL;
	tree=tree->readnode();
	tree->showtree(tree);
	/*cout<<endl<<"------------deleted train 9------------";
	tree=tree->deletenode(tree,9);
	tree->showtree(tree);
	cout<<endl<<"-----------------------------------";*/
	//tree->showtraininf(9,tree);
	tree->showstationinf("Zaporizhia",tree);
	cin.get();
}