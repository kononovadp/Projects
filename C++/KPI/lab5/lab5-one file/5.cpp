#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;
class cArray{
#define GROWBY 10 //The minimum number of element slots to allocate if a size increase is necessary. 
int *a;
int size;
int count;
public:	
	cArray(void) //Constructs an empty array.
	{
		a=new int[0];
		size=0;	
		count=0;
	}
	~cArray(void)
	{
		a=NULL;
	}
	int GetSize() //const //Gets the number of elements in this array.
	{
		return size;
	}
	int GetCount() const //Gets the number of elements in this array.
	{
		return count;
	}
	int GetUpperBound() const //Returns the largest valid index.
	{
		if(count>0)
			return count-1; //size-1;
		else return 0;
	}
	bool IsEmpty()const //Determines whether the array is empty.
	{
		if (count==0)
			return true;
		else
			return false;
	}
	void SetSize(int nNewSize) //Establishes the size of an empty or existing array; allocates memory if necessary.
	{
		if (nNewSize<size)
		{
			int i=count;
			while(i>nNewSize-1)
			{
				RemoveAt(i);
				i--;
			}
		}
		size=nNewSize;
	}
	void FreeExtra() //Frees all unused memory above the current upper bound.	
	{
		size=count;
	}
	void RemoveAll() //Removes all the elements from this array.
	{
		//SetSize(0);
		int i=count;
		while(i>-1)
		{
			RemoveAt(i);
			i--;
		}
	}
	int GetAt(int indx)const //Returns the value at a given index.
	{
		int i=GetUpperBound();
		if((indx>=0) && (indx<=i))
			return a[indx];
		else
			return 0;
	}	
	void SetAt(int n, int indx) //Sets the value for a given index; array not allowed to grow.
	{	
		int i=GetUpperBound();
		if((indx>=0) && (indx<=i))
			a[indx]=n;
	}
	void Add(int n) //Adds an element to the end of the array; grows the array if necessary.
	{
		if(count>=size)
			size+=GROWBY;
		a[count]=n;
		count++;
	}
	void Append(cArray *ar) //Appends another array to the array; grows the array if necessary
	{
		Copy(ar);	
		ar->RemoveAll();
	}
	void Copy(cArray *ar) //Copies another array to the array; grows the array if necessary.
		{
		int t=ar->GetCount();
		for (int i=0; i<t; i++)
			Add(ar->a[i]);		
		}	
	void InsertAt(int n, int indx) //Inserts an element at a specified index.
	{
		if ((indx>-1) && (indx<=count-1))
		{
			int t=a[indx];
			a[indx]=n;
			Add(a[count-1]);
			for (int i=indx; i<count; i++)
			{
				int t2=a[i+1];
				a[i+1]=t;
				t=t2;
			}
		}
	}
	void RemoveAt(int indx) //Removes an element at a specific index.
	{
		if (indx<=count-1)
		{
			for (int i=indx; i<count; i++)
				a[i]=a[i+1];
			count--;
		}		
	}
	int& operator [](int indx) //Sets or gets the element at the specified index.
	{
		return a[indx];
	}
	void show()
	{
		for (int i=0; i<count; i++)
			cout<<a[i]<<"  ";
		cout<<endl;
	}
private:
};
int main()
{
	srand(time(NULL));
	int n=rand()%20;
	cArray obj;
	obj.SetSize(n);
	cout<<"New empty vector created with the size "<<obj.GetSize()<<endl;	
	for (int i=0; i<rand()%15; i++)
	{
		int n=rand()%99;
		obj.Add(n);
	}
	cout<<"Vector of random numbers: ";
	obj.show();
	cout<<"New size of vector is "<<obj.GetSize()
	<<", count of elements "<<obj.GetCount()
	<<", largest valid index "<<obj.GetUpperBound();
	obj.FreeExtra();
	cout<<endl<<"Procedure FreeExtra executed:"<<endl
	<<"New size of vector is "<<obj.GetSize()
	<<", count of elements "<<obj.GetCount()
	<<", largest valid index "<<obj.GetUpperBound()<<endl;
	if (obj.GetUpperBound()==0)
		n=0;
	else
		n=rand()%obj.GetUpperBound();
	cout<<"The value at random index "<<n<<": "<<obj.GetAt(n);
	obj.SetAt(rand()%99,n);
	cout<<endl<<"The value at random index "<<n
	<<" was changed:"<<endl;
	obj.show();	
	n=rand()%20;
	cArray obj2;
	obj2.SetSize(n);
	cout<<"New empty vector created with the size "<<obj2.GetSize()<<endl;	
	for (int i=0; i<rand()%15; i++)
	{
		int n=rand()%99;
		obj2.Add(n);
	}
	cout<<"Vector 2 of random numbers: ";
	obj2.show();
	obj.Copy(&obj2);
	cout<<"Elements of vector 2 copied into vector 1:"<<endl
	<<"Vector 1: ";
	obj.show();
	cout<<"Vector 2: ";
	obj2.show();
	obj.Append(&obj2);
	cout<<"Elements of vector 2 appended into vector 1:"<<endl
	<<"Vector 1: ";
	obj.show();
	cout<<"Vector 2: ";
	obj2.show();
	n=rand()%obj.GetUpperBound();
	obj.InsertAt(rand()%99,n);
	cout<<"Element with random value inserted at random position "<<n<<":"<<endl;
	obj.show();
	n=rand()%obj.GetUpperBound();
	obj.RemoveAt(n);
	cout<<"Element at random index "<<n<<" was removed:"<<endl;
	obj.show();
	n=rand()%obj.GetUpperBound();
	obj[n]=rand()%99;
	cout<<"The value at random index "<<n
	<<" changed by operator []:"<<endl;
	obj.show();	
	obj.RemoveAll();
	cout<<"All elements removed. Vector of random numbers: ";
	obj.show();
	cout<<"New size of vector is "<<obj.GetSize()
	<<", count of elements "<<obj.GetCount()
	<<", largest valid index "<<obj.GetUpperBound();
	cin.get();
}