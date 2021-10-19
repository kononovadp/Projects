#include <iostream>
#include <fstream>
#include <sstream>
#define _CRT_SECURE_NO_WARNINGS
#include "Iterator.h"
using namespace std;
class CFile{
public:
	CFile(){}
	CFile(char *filename,char *creation_date,int size)
	{
		_filename=filename;
		_creation_date=creation_date;
		_size=size;
	}
	friend ostream& operator<<(ostream& stream, CFile &obj);
	bool operator==(CFile obj);
	bool operator!=(CFile obj);
	CFile operator=(string s);
	char *GetFilename()
	{
		return _filename;
	}
	void SetFilename(char *filename)
	{
		_filename=filename;
	}
	char *GetDate()
	{
		return _creation_date;
	}
private:
	char *_filename;
	char *_creation_date;
	int _size;
};
ostream& operator<<(ostream& os, CFile &obj)
{
	if(&obj!=NULL)
		os<<obj._filename<<' '<<obj._creation_date<< ' '<<obj._size<<endl;
    return os;
}
bool CFile::operator==(CFile obj)
{
	return ((strcmp(obj._filename,_filename)==0)&&
	(strcmp(obj._creation_date,_creation_date)==0)
	&&(obj._size==_size));
}
bool CFile::operator!=(CFile obj)
{
	return!(*this==obj);
}
CFile CFile::operator=(string s)
{
		int t=s.find_first_of(";");
		string name=s.substr(0,t);
		s=s.erase(0,t+1);
		t=s.find_first_of(";");
		string date=s.substr(0,t);
		s=s.erase(0,t+1);
		t=s.find_first_of(";");
		string temp=s.substr(0,t);
		istringstream v1 (temp, istringstream::in);
		v1>>_size;
		s=s.erase(0,t+1);
		//cout<<name<<"|"<<date<<"|"<<filesize<<endl;
		_filename = new char [name.length()+1];
		std::strcpy (_filename, name.c_str());
		_creation_date = new char [date.length()+1];
		std::strcpy (_creation_date, date.c_str());
		return *this;
}		
template <class T>
class List{
	struct ListNode
	{
		T data;
		ListNode * next;
		ListNode()
		{
			next = NULL;
		}
		ListNode(T dat)
		{
			data = dat;
		}
		void Print()
		{
			cout<<data;
		}
	};	
public:
	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;
	List()
	{
		head=NULL;	
	}
	~List(){};	
	iterator begin()//Returns an iterator addressing the first element 
	{
		if (head==NULL)
			return NULL;
		else
			return head;//*first;
	}
	iterator end()//Returns an iterator that addresses the location succeeding the last element
	{
		//return *last;
		if(head==NULL)
			return NULL;
		_iterator<node_type> it;//*last;
		it=begin();
		ListNode t;
		t=*it; //cout<<"first: "<<t.data<<"||";		
		while(t.next!=NULL)
		{
			it++;
			t=*it;
		}//cout<<"last: "<<t.data<<endl;
		return it;
	}
	void clear() //Erases all the elements of a list.
	{
		head=NULL;
	}
	bool empty() //Tests if a list is empty.
	{
		if(head==NULL)
			return true;
			else
				return false;
	}
	iterator find(const node_type &val)//Returns an iterator to the first element in a list that match a specified value.
	{
		_iterator<node_type> it=begin();
		ListNode *ln1=&*it;
		ListNode *ln2=new ListNode(val);
		if (ln1->data==ln2->data)
			return it;
		else
		
			while(it!=NULL)
			{
				it++;
				ln1=&*it;
				if (ln1->data==ln2->data)
					return it;
			}
	}
	void pop_front()//Deletes the element at the beginning of a list.
	{
		if(head==NULL)
			return;
		head=head->next;
		_iterator<node_type> it=head;
		first=&it;
	}
    void pop_back()
	{		
		if (head==NULL)
			return;
		_iterator<node_type> it=begin();
		ListNode *ln=&*it;
		if(ln->next==NULL)
			head=NULL;
		else
			if(ln->next->next==NULL)
			{
				ln->next=NULL;
				it++;
			}
			else
				while(ln->next->next!=NULL)
				{
					it++;
					ln=&*it;
				} //cout<<ln->data<<"*/*/*"<<endl;
				ln->next=NULL;
				last=&it;
		/*ListNode *ln=head; //через указатель
		if (head!=NULL)
		while(ln->next->next!=NULL)
			ln=ln->next;
		ln->next=NULL;*/
	}
	void push_front(const node_type val)//Adds an element to the beginning of a list.
	{			
		if (head==NULL)
		{
			head=new ListNode(val);
			head->next=NULL;
			_iterator<node_type> it=head;
			first=&it;
			last=first;
		}
		else
		{
			ListNode *t=head;
			head=new ListNode(val);
			head->next=t;
			_iterator<node_type> it=head;
			first=&it;			
		}
	}
	void push_back(const node_type val) //added by myself
    {		
		if (head==NULL)
		{
			head=new ListNode(val);
			head->next=NULL;
			_iterator<node_type> it=&*head;
			first=&it;
			last=&it;
		}	
		else
		{			
			_iterator<node_type> it=end();
			ListNode *ln=&*it;
			ln->next=new ListNode(val);
			ln->next->next=NULL;
			it++;
			last=&it;
			/*ListNode *ln=head; //через указатель
			while(ln->next!=NULL)
				ln=ln->next;
			ln->next=new ListNode(val);
			ln->next->next=NULL;*/
		}		 
	}
	void remove(const node_type val) //Erases first element in a list that match a specified value.
	{
		if (head==NULL)
			return;
		_iterator<node_type> it=begin();
		ListNode *ln1=&*it;
		ListNode *ln2=new ListNode(val);
		if(ln1->data==ln2->data)
			pop_front();
		else
		{
			while((ln1->next->data!=ln2->data)
				&&(it!=NULL))
				{
					it++;
					ln1=&*it;
				}//cout<<endl<<"!!!"<<ln1->data;
			if(ln1->next==NULL)
				pop_back();
			else
				ln1->next=ln1->next->next;
		}		
	}
	int size() //Returns the number of elements in a list.
	{
		if (head==NULL)
			return 0;
		else
		{
			_iterator<node_type> it;
			it=begin();
			int n=0;
			for(it=begin(); it!=NULL; it++)
				n++;
			return n;
		}
	}
	void splice(iterator _Where, List<T>& _Right) //Removes element from the target list and inserts it in first position of the argument list.
	{
		if(head==NULL)
			return;
		ListNode *ln=&*_Where;
		remove(ln->data);
		_Right.push_front(ln->data);
	}
	void print()//Dumps list into the screen
	{
		if (head==NULL)
			return;
		_iterator<node_type> it=begin();
		ListNode t;
		for(it=begin(); it!=NULL; it++)		
		{
			t=*it;
			cout<<"     "<<t.data;
		}
		/*ListNode *ln; //вариант с указателем
		ln=head;
		if (head!=NULL)
			while(ln>NULL)
			{
				cout<<ln->data<<"  ";
				ln=ln->next;
			}*/
	}
	void load(const char *filename,bool push_back_true)	
	{
		ifstream f;
		f.open(filename);
		string s;
		ListNode obj;
		if(push_back_true==true)
		while(!f.eof())
		{
			f>>s;
			obj.data=s;
			push_back(obj);
		}
		else
			while(!f.eof())
			{
				f>>s;
				obj.data=s;
				push_front(obj);
			}
		f.close();
	}
	void testintlist()
	{		
		int a[10];
		cout<<"List 1: ";
		for (int i=0; i<10; i++)
		{
			int n=rand()%99;
			a[i]=n;
			cout<<a[i]<<"  ";
		}   cout<<endl;
		for (int i=0; i<10; i++)
			push_back(a[i]);
		cout<<"push_back: ";
		print();
		clear();
		for (int i=0; i<10; i++)
			push_front(a[i]);
		cout<<endl<<"push_front: ";
		print();
		cout<<endl<<"pop_front: ";
		pop_front();		
		print();
		cout<<endl<<"pop_back: ";
		pop_back();		
		print();
		int t=34;
		remove(t);
		cout<<endl<<"Removed el. "<<t<<":  ";
		print();
		cout<<endl<<"Size of list 1: "<<size();
		cout<<endl<<"List 2: ";
		List<int> l2;
		for (int i=0; i<10; i++)
		{
			int n=rand()%99;
			a[i]=n;
			l2.push_back(a[i]);
		}
		l2.print();
		srand(time(NULL));
		int n=rand()%size();
		_iterator<node_type> it=begin();
		for (int i=1; i<n; i++)
			it++;
		ListNode *ln=&*it;
		cout<<endl<<"Splice element number "<<n
		<<" ("<<ln->data<<")"<<endl<<"List 1: ";
		splice(it,l2);
		print();
		cout<<endl<<"List 2: ";
		l2.print();
	}
	bool date_less(string first,string second)
	{
		int t=first.find_first_of(".");
		string temp=first.substr(0,t);
		istringstream v1 (temp, istringstream::in);
		int f_day;
		v1>>f_day;		
		first=first.erase(0,t+1);		
		t=first.find_first_of(".");
		temp=first.substr(0,t);
		istringstream v2 (temp, istringstream::in);
		int f_month;
		v2>>f_month;
		first=first.erase(0,t+1);		
		t=first.find_first_of(".");
		temp=first.substr(0,t);
		istringstream v3 (temp, istringstream::in);
		int f_year;
		v3>>f_year;
		first=first.erase(0,t+1);		
		t=second.find_first_of(".");
		temp=second.substr(0,t);
		istringstream v4 (temp, istringstream::in);
		int s_day;
		v4>>s_day;		
		second=second.erase(0,t+1);		
		t=second.find_first_of(".");
		temp=second.substr(0,t);
		istringstream v5 (temp, istringstream::in);
		int s_month;
		v5>>s_month;
		second=second.erase(0,t+1);		
		t=second.find_first_of(".");
		temp=second.substr(0,t);
		istringstream v6 (temp, istringstream::in);
		int s_year;
		v6>>s_year;
		second=second.erase(0,t+1);
		
		if(f_year>s_year)
			return false;
			else
				if(f_year<s_year)
					return true;
					else
						if(f_month>s_month)
							return false;
							else
								if(f_month<s_month)
									return true;
									else
										if(f_day>s_day)
											return false;
											else
												if(f_day<s_day)
													return false;
		return false;
	}
		

void TestObjList()
{
	List<CFile> l2;
	cout<<"load (push_back):"<<endl;
	load("files.txt",true);	
	print();
	cout<<"clear:"<<endl;
	clear();
	cout<<"load (push_front):"<<endl;
	load("files.txt",false);	
	print();
	cout<<"empty: "<<empty()<<endl
	<<"pop_front:"<<endl;	
	pop_front();
	print();
	srand(time(NULL));
	int n=rand()%size();
	List<CFile>::iterator it;
	it=begin();
	cout<<"iterator begin: ";
	ListNode ln(*it);
	cout<<ln.data;
	for(int i=1; i<n; i++)
		it++;
	ln=*it;
	remove(ln);
	cout<<"removed random element:"<<ln.data;	
	print();
	it=end();
	ln=*it;
	cout<<"iterator end: "<<ln.data<<"Size of list: "<<size()<<endl
	<<"--------------------------------------------------------------"<<endl;
	List<CFile> DeletedElements;
	srand(time(NULL));
	int count=rand()%size();
	cout<<"deleted elements:"<<endl;
	for(int i=1; i<count; i++)
	{	
		srand(time(NULL));
		n=rand()%size();
		it=begin();
		for(int i=1; i<n; i++)
			it++;
		ln=*it;
		cout<<"   "<<ln.data;
		splice(it,DeletedElements);
	}
	cout<<"list of deleted elements:"<<endl;
	DeletedElements.print();
	cout<<"main list:"<<endl;
	print();	
	while(DeletedElements.size()>0)
	{
		it=DeletedElements.begin();
		DeletedElements.splice(it,*this);
	}	
	cout<<"All elements restored:"<<endl;
	print();
	cout<<"list of deleted elements:"<<endl;
	
	DeletedElements.print();
	cout<<"--------------------------------------------------------------"<<endl
	<<"Changed file name of random file (extension not changed!):"<<endl;
	srand(time(NULL));
	n=rand()%size();
	it=begin();
	for(int i=1; i<n-1; i++)
		it++;
	ln=*it;
	string t=ln.next->data.GetFilename();
	n=t.find_first_of(".");
	t=t.erase(0,n);
	char *extension=new char[t.length()+1];
	std::strcpy (extension, t.c_str());
	t="CHANGED_FileName";
	char *new_filename=new char[t.length()+1];
	std::strcpy (new_filename, t.c_str());
	strcat(new_filename,extension);
	ln.next->data.SetFilename(new_filename);
	print();
	
	srand(time(NULL));
	n=rand()%size();
	it=begin();
	for(int i=1; i<n; i++)
		it++;
	ln=*it;
	t=ln.data.GetDate();
	cout<<"--------------------------------------------------------------"<<endl
	<<"List after removing of files, created earlier then "<<t<<":"<<endl;
	it=begin();
	while(it!=NULL)
	{
		ln=*it;
		if(date_less(ln.data.GetDate(),t)==1)
			remove(ln);		
		it++;
	}	
	print();	
	//cout<<date_less("27.09.2016",t);
}	
	node_type *GetHead()
	{
		return head;
	}

private:
	node_type *head;
	iterator *first, *last;	
};


int main()
{	
	List<CFile> l1;
	l1.TestObjList();
	//List<int> l1;
	//l1.testintlist();
	cin.get();
}
