//#include <string>
#include <iostream>
//#include <algorithm>
#include <fstream>
//#include <stdio.h>
#include <sstream>
//#include <cstdlib>
//#include <stdlib.h>
//#include <stdio.h>
//#pragma once
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
template <typename T>
class _iterator
{
private:
	T *ptr;
public:
	typedef T value_type;
	typedef _iterator<T> it_type;
	_iterator() 
	{
		ptr = 0;
	}
	_iterator(T *_ptr) 
	{
		ptr = _ptr;
	}
	T& operator *();
	void operator++();
	//dummy operator to keep compiler quiet
	void operator++(int);
	bool operator==(const it_type& _iter) const;
	bool operator!=(const it_type& _iter) const;
	bool empty(){ return ptr == NULL;}
};
template <typename T>
T& _iterator<T>::operator *()
{
	return *ptr;
}
template <typename T>
void _iterator<T>::operator ++()
{
	ptr = ptr->next;
}

template <typename T>
void _iterator<T>::operator ++(int)
{
	ptr = ptr->next;
}

template <typename T>
bool _iterator<T>::operator ==(const it_type &_iter) const
{
	return (ptr == _iter.ptr);
}

template <typename T>
bool _iterator<T>::operator !=(const it_type &_iter) const
{
	return !(*this == _iter);
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
		/*if(first==NULL)
			return NULL;
		_iterator<node_type> it=head;//*first;
		return it;*/
	}
	iterator end()//Returns an iterator that addresses the location succeeding the last element
	{
		/*if (head==NULL)
			return NULL;
		return *last;*/
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
	iterator find(const node_type & val)//Returns an iterator to the first element in a list that match a specified value.
	{
		if(head==NULL)
			return NULL;
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
			last=first;
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
		ListNode *ln=&*_Where;//it;
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
			cout<<t.data<<" ";
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
	void testlist()
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
		int t=53;
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
private:
	node_type *head;
	iterator *first, *last;
};

int main()
{
	List<int> l1;
	l1.testlist();
	cin.get();
}