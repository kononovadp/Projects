#include <iostream>
using namespace std;
class ListNode
{
    char *data;
    ListNode *prev;
    ListNode *next;
public:
    friend class DoublyLinkedList;
    ListNode()
    {
		prev=NULL;
		next=NULL;
	}
    ListNode(char *_data)
	{
		prev=NULL;
		next=NULL;
		data=_data;
	}
    ~ListNode(void)
    {}
};
class DoublyLinkedList
{
    ListNode *head;
public:
    DoublyLinkedList(void)
    {
		head=NULL;
    }
    ~DoublyLinkedList(void)
    {
	head=NULL;
	}
    int size()
	{
		ListNode *t;
		t=head;
		int size=0;
		if (head!=NULL)
		while(t!=NULL)
		{
			size++;
			t=t->next;
		}
		else size=0;
		return size;
	}
    bool empty()
	{
		if (head==NULL)
			return true; else return false;
	}
    void clear()
	{
		head=NULL;
	}
    void push_back(const ListNode &nd)
    {
		ListNode *ln;
		if (head==NULL)
		{
			head=new ListNode(nd);
			head->next=NULL;
			head->prev=NULL;
		}	
		else
		{
			ln=head;
			while(ln->next!=NULL)
				ln=ln->next;
			ln->next=new ListNode(nd);
			ln->next->prev=ln;
			ln->next->next=NULL;
		}
	}
    void push_front(const ListNode &nd)
	{
		ListNode *ln,*t;
		if (head==NULL)
		{
			head=new ListNode(nd);
			head->prev=NULL;
			head->next=NULL;
		}	
		else
		{
			t=head;
			head->prev=new ListNode(nd);
			head=head->prev;
			head->next=t;
			head->prev=NULL;
		}		
	}
    void pop_front()
	{
		head=head->next;
		head->prev=NULL;
	}
    void pop_back()
	{
		ListNode *ln,t;
		ln=head;
		if (head!=NULL)
		while(ln->next->next!=NULL)
			ln=ln->next;
		ln->next->prev=NULL;
		ln->next=NULL;
	}
    void insert_ord(const ListNode &nd)
	{
		ListNode *ln,*t;		
		if (head==NULL)
			push_back(nd);
		else
		{
			t=new ListNode(nd);
			ln=head;
			if(strcmp(t->data,head->data)<0)
				push_front(nd);
			else
			{
			while((strcmp(t->data,ln->data)>0)&&(ln->next!=NULL))
				ln=ln->next;
			if(strcmp(t->data,ln->data)>0) 
			{ push_back(nd);}
			else 
			{
				ln=ln->prev;
		    	t->next=ln->next;
				ln->next->prev=t;
				ln->next=t;
				t->prev=ln;
			}
			}
		}
	}
    void sort()
	{
		ListNode *c,*n,*t;
		bool b=false;
		int s=size();
		while(b!=true)
		{
			int i=0;
			c=head;
			while(c->next!=NULL)
			{
				n=c->next;
				if(strcmp(c->data,n->data)<=0)
					i++;
				c=c->next;
			}
			if (i==s-1)
				b=true;
			else		
			{
				c=head;
				while(c->next!=NULL)
				{
					n=c->next;
					if(strcmp(c->data,n->data)>0)
						{
							t=new ListNode;
							t->data=c->data;
							c->data=n->data;
							n->data=t->data;
							delete t;
						}
					c=c->next;
				}
			}
		}
	}
    bool insert_after(char *dat, const ListNode &nd)
	{
		bool b=false;
		ListNode *ln,*t,*t1,*t2;
		ln=head;
		while(ln!=NULL)
		{	
			if(strcmp(ln->data,dat)==0)
			{
				b=true;
				break;
			}
			else
			ln=ln->next;
		}
		if (ln->next==NULL)
			push_back(nd);
		else
		{
		t1=ln->next;
		t2=new ListNode(nd);
		ln->next=t2;
		t2->prev=ln;
		t2->next=t1;
		if(t1!=NULL)
		t1->prev=t2;
		t1->next=t2->next->next;
		}
		return b;
	}
    void operator=(const DoublyLinkedList &lst)
	{
		head=lst.head;
	}
    void merge(DoublyLinkedList &lst)
	{
		ListNode *ln,*ln2,*t;
		ln=head;
		if (head!=NULL)
			while(ln->next!=NULL)
				ln=ln->next;
		ln2=lst.head;
		while(ln2!=NULL)
		{
			push_back(ln2->data);
			ln=ln->next;
			ln2=ln2->next;
		}
		lst.head=NULL;
		sort();
	}		
    void erase(char *dat)
	{
		ListNode *ln,*t;
		ln=head;
		while(ln!=NULL)
		{
			if(strcmp(ln->data,dat)==0)
			{
				if (ln==head)
					pop_front();
				else
					if(ln->next==NULL)
						pop_back();
				else
				{
					ln=ln->prev;
					ln->next=ln->next->next;
					ln->next->prev=ln;
				}					
			}
			ln=ln->next;
		}
	}
    void unique()
	{
		sort();
		ListNode *ln,*t,*t1,*t2;
		ln=head; t=ln->next;
		while(t!=NULL)
		{
			if (strcmp(ln->data,t->data)==0)
			{
				if (ln==head)
 					pop_front();
				else
				{
					erase(ln->data);
					insert_ord(ln->data);				
				}
			}
			ln=ln->next;
			t=t->next;
		}
	}
    void assign(DoublyLinkedList &d1, int first, int last)
	{
		ListNode *ln,*ln2,*t;
		ln=head;
		if (head!=NULL)
			while(ln->next!=NULL)
				ln=ln->next;
			ln2=d1.head;
			int i;
			for(i=0; i<first; i++)
				ln2=ln2->next;
			t=ln2;
			for (i=first; i<last; i++)
			{
				if(t!=NULL)				
				push_back(t->data);
				t=t->next;
			}
			push_back(t->data);
			if(first==0)
			{
				
				d1.head=t->next;
				if (d1.head!=NULL)
					d1.head->prev=NULL;
			}
			else
			{
				ln2=ln2->prev;
				ln2->next=t->next;
				if (ln2->next!=NULL)
					ln2->next->prev=ln2;
			}
	}
    void splice(int where, const DoublyLinkedList &d1)
	{
		ListNode *ln1,*ln2,*t;		
		ln1=head;
		int i; bool b;
		for(i=0; i<where; i++)
			ln1=ln1->next;
		if(ln1->next==NULL)
			b=false; else b=true;
		DoublyLinkedList temp;
		if (b==true)
		{			
			ln2=ln1->next;
			while(ln2!=NULL)
			{
				temp.push_back(ln2->data);
				ln2=ln2->next;
			}
		}
		ln1->next=d1.head;
		ln1->next->prev=ln1;
		if (b==true)
		{
			while(ln1->next!=NULL)
				ln1=ln1->next;
			ln1->next=temp.head;
			ln1->next->prev=ln1;
		}
	}		
    void splice(int where, const DoublyLinkedList &dl, int first, int last)
	{
		ListNode *ln1,*ln2,*t,*t2;
		int i=0;
		ln1=head;
		for(i=0; i<where; i++)
			ln1=ln1->next;
		ln2=dl.head;
		for(i=0; i<first; i++)
			ln2=ln2->next;
		if(ln1->next==NULL)
			for(i=first; i<last+1; i++)
			{
				push_back(ln2->data);
				ln2=ln2->next;
			}
		else
			for(i=first; i<last+1; i++)
			{
				t=ln1->next;
				t2=ln1;
				ln1->next=new ListNode(ln2->data);
				ln1=ln1->next;
				ln1->prev=t2;
				ln1->next=t;
				ln1->next->prev=ln1;
				ln2=ln2->next;
			}
	}
    void print()
    {
        ListNode *ln;
        ln=head;
		if (head!=NULL)
        while(ln!=NULL)
        {
			cout<<ln->data<<endl;
            ln=ln->next;
        }
    }
    void print_bkw()
	{
		ListNode *ln;
		ln=head;
		if (head!=NULL)
			while(ln->next!=NULL)
				ln=ln->next;
		while(ln!=NULL)
		{
			cout<<ln->data<<endl;
			ln=ln->prev;
		}
	}
private:
};
int main()
{
    DoublyLinkedList dll;
	//dll.push_back("acdj");
	//dll.push_back("cbdk");
	dll.push_back("cbdk");
	dll.push_back("8");
	dll.push_back("8");
	dll.push_back("6");
	dll.push_back("7");
	dll.push_back("acdj");
//	dll.push_back("acdj");
	//dll.push_back("acdj");
//	dll.push_back("6");
//	dll.push_back("cbdk");
//	dll.push_back("6");
//	dll.push_back("cbdk");
//	dll.push_back("8");
	//dll.push_back("acdj");	
	//dll.insert_after("6","1111");
	DoublyLinkedList d2;
	d2.push_back("d1");
	d2.push_back("d2");
	d2.push_back("d3");
	d2.push_back("d4");
	d2.push_back("d5");
	d2.push_back("dA");
	d2.push_back("dB");
	d2.push_back("dC");
	//dll.merge(d2);
	//dll.erase("acdj");
	//dll.operator=(d2);
	//dll.print();	
	//dll.print();
	//dll.assign(d2,0,7);
	//dll.unique();	
	dll.splice(3,d2);
	//dll.splice(5,d2,0,7);
	dll.print();
	cout<<"======================="<<endl;
	dll.print_bkw();
	cin.get();
}