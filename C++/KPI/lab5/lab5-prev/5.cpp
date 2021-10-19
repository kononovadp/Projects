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
		return size-1;
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
		//int k=a[indx];
		//a[indx]=indx;
		return a[indx];// k ;
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
	cArray obj;
	obj.SetSize(3);
	srand(time(NULL));
	for (int i=0; i<10; i++)
	{
		int n=rand()%99;
		obj.Add(n);
	}
	obj.show();
	//obj.RemoveAll();
	//obj.show();
	cArray obj2;
	obj2.SetSize(5);
	for (int i=0; i<6; i++)
	{
		int n=rand()%99;
		obj2.Add(n);
	}
	obj2.show();
	obj.Copy(&obj2);
	obj2.show();
	obj.show();
	int t;
	//t=obj.operator[](7); 
	t=obj[0]=9;
	obj.show();
	cout<<t;
	cin.get();
}