#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
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
		cout<<"Train number "<<m_TrainNumber<<"  Destination "<<m_Destination
		<<" Departure time "<<m_DepartureTime<<endl;
	}
	int gettrainn()
	{
		return  m_TrainNumber;
	}
	
	string getstation()
	{
		return m_Destination;
	}
protected:
	int m_TrainNumber;
	string m_Destination;
	string m_DepartureTime; 
};


struct CBinTree
{
   CTreeNode *train; 
  CBinTree *l,*r;
   
  
  CBinTree()
  { train=NULL;
   l=NULL;r=NULL;
  }
  
 void addnode(CTreeNode *node)
{
	
	if (train==NULL)
		train=node;
	else
	{
	if(node->gettrainn() >	train-> gettrainn())
		{if (r==NULL)r=new CBinTree;
			r->addnode(node);
		}
	else
		{if (l==NULL)l=new CBinTree;
			l->addnode(node);
	
		}
	}
};//addnode
   



bool nodecompare(CTreeNode *n1,CTreeNode *n2)
{
}


void readnode()
{
		ifstream f;
		f.open("1.txt");
		string s;
		int i=0;
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
			cout<<"Created  "<<trainn<<"|"<<dest<<"|"<<dep<<"|"<<endl;
			addnode(obj);
			cout<<"Add"<<endl<<"**********"<<endl;
		}
		f.close();
}//read

void displaytree()
{   
	if (l!=NULL) l->displaytree();
	 train->Display();
	if (r!=NULL) r->displaytree();
} 

bool showtraininf(int n)
{   if (train-> gettrainn()==n)
	{train->Display(); return true;}
	else
	if ((train-> gettrainn()<n) &&(r!=NULL))return r->showtraininf(n);
	else
    if ((train-> gettrainn()>n)&&(l!=NULL)) return l->showtraininf(n);
	else return false;
} 


int displaystation(string s)
{  int k=0;
	if(train->getstation()==s)
		{train->Display();k++;}
//else
	if (l!=NULL) k=k+l->displaystation( s);
//	else
	if (r!=NULL) k=k+r->displaystation( s);
	return k;
}
};//struct


int main()
{
	CBinTree *L=new CBinTree;
	L->readnode();
	
	L->displaytree();
	cout<<"****************"<<endl;
	if(!L->showtraininf(5)) cout<<"Not Found"<<endl;
	cout<<"****************"<<endl;
	if (L->displaystation("Odessa")==0) cout<<"Not found"<<endl;
	cin.get();
}