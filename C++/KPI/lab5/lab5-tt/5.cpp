#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <conio.h>
using namespace std;
class cArray{
#define GROWBY 10 //The minimum number of element slots to allocate if a size increase is necessary. 
int *myarr;

public:	
	cArray(void) //Constructs an empty array.
	{ myarr= (int*) malloc (10 * sizeof (int));
		//myarr=new int[0];
		size=0;	
        count=0;		
	}
	~cArray(void)
	{
		delete myarr;
	}
	int GetSize() const//Gets the number of elements in this array.
	
	{
		return size;
	}
	int GetCount() const //Gets the number of elements in this array.
	{
		return count;
	}
	int GetUpperBound()const //Returns the largest valid index.
		{
		return count-1;
     	}

	bool IsEmpty()const //Determines whether the array is empty.
	{
	if (cout==0) return true;
	else return false;
	}
	
	void SetSize(int nNewSize) //Establishes the size of an empty or existing array; allocates memory if necessary.
	{
		if(size!=nNewSize)
		{ 
			/*int x=nNewSize;
			int *t=new int[x];
			
			if (size<nNewSize)x=size;
			
			for(int i=0; i<x; i++)
				t[i]=myarr[i];
			t;
			delete t;*/
			myarr= (int*) realloc (myarr, nNewSize * sizeof (int)); 
		 size=nNewSize;
		 if (count>size)
			count=size;
		}
	}
	void FreeExtra() //Frees all unused memory above the current upper bound.	
	{
	if (size>count) {myarr= (int*) realloc (myarr, count * sizeof (int));
	size=count;
	}
	}
	
	void RemoveAll()	//Removes all the elements from this array.
	{free(myarr);
	 size=0; count=0;
	}
	
	int GetAt(int x)const //Returns the value at a given index.	
	{
		return myarr[x];
	}
	
	void SetAt(int n, int indx)
	//Sets the value for a given index; array not allowed to grow.
	{
		 myarr[indx]=n;
	}
	
	void Add(int x) //Adds an element to the end of the array; grows the array if necessary.
	{if (count==size) // еесли места все заняты, создаем новые
	  SetSize(size+GROWBY);
	
	myarr[count]=x;    count++;
	
	}
	void Append(cArray *ar) //Appends another array to the array; grows the array if necessary
	{
		for (int i=0; i<ar->count; i++)
		Add(ar->myarr[i]);
	}
	
	void Copy(cArray *); //Copies another array to the array; grows the array if necessary.
	
	void InsertAt(int n, int indx) //Inserts an element at a specified index.
	{if (count==size) // еесли места все заняты, создаем новые
	  SetSize(size+GROWBY);
	
	 for (int i=count; i>=indx; i--)
		 myarr[i+1]=myarr[i];
	 myarr[indx]=n;
	count++;	
	}

	void RemoveAt(int indx) //Removes an element at a specific index.
	{ for (int i=indx; i<count; i++)
		 myarr[i]=myarr[i+1];
	count--;
	
	}
	
	int& operator [](int); //Sets or gets the element at the specified index.
	void showarr()
	{
		for (int i=0; i<count; i++)
			cout<<myarr[i]<<"  ";
			cout<<endl;
	}
private:
	int size,count;
};
int main()
{
	cArray obj;
	obj.SetSize(5);
	//obj.SetSize(15);
	obj.showarr();
    cout<<"Size - "<<obj.GetSize()<<"   Alloceted - "<<obj.GetCount()<<endl;
	
	 for(int i=0; i<7;i++) { obj.Add(i+1);
	 cout<<"Size - "<<obj.GetSize()<<"   Alloceted - "<<obj.GetCount()<<endl;}
	 	 obj.showarr();
		 obj.SetAt(0,3);
	// obj.RemoveAll();
	// cout<<"Size - "<<obj.GetSize()<<"   Alloceted - "<<obj.GetCount()<<endl;
	  
		obj. InsertAt(10, 4);
		cout<<"Size - "<<obj.GetSize()<<"   Alloceted - "<<obj.GetCount()<<endl;
	   obj.showarr();
	   cout<<"Size - "<<obj.GetSize()<<"   Alloceted - "<<obj.GetCount()<<endl; 
	   cout<<"A[3] = "<<obj.GetAt(3)<<endl; 
	  obj.RemoveAt(3);
	  obj.showarr(); 
	  obj.FreeExtra();
	   cout<<"Size - "<<obj.GetSize()<<"   Alloceted - "<<obj.GetCount()<<endl;
	   
	   cArray NAr;
	    for(int i=0; i<7;i++) NAr.Add(i+10);
		NAr.showarr(); 
		obj.Append(&NAr);
		cout<<"Size - "<<obj.GetSize()<<"   Alloceted - "<<obj.GetCount()<<endl;
		 obj.showarr(); 
	 system("pause");
}
