#include "headers.h"
using namespace std;
	int cArray::GetSize() //const //Gets the number of elements in this array.
	{
		return size;
	}
	int cArray::GetCount() const //Gets the number of elements in this array.
	{
		return count;
	}
	int cArray::GetUpperBound() const //Returns the largest valid index.
	{
		if(count>0)
			return count-1; //size-1;
		else return 0;
	}
	bool cArray::IsEmpty()const //Determines whether the array is empty.
	{
		if (count==0)
			return true;
		else
			return false;
	}
	void cArray::SetSize(int nNewSize) //Establishes the size of an empty or existing array; allocates memory if necessary.
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
	void cArray::FreeExtra() //Frees all unused memory above the current upper bound.	
	{
		size=count;
	}
	void cArray::RemoveAll() //Removes all the elements from this array.
	{
		//SetSize(0);
		int i=count;
		while(i>-1)
		{
			RemoveAt(i);
			i--;
		}
	}
	int cArray::GetAt(int indx)const //Returns the value at a given index.
	{
		int i=GetUpperBound();
		if((indx>=0) && (indx<=i))
			return a[indx];
		else
			return 0;
	}	
	void cArray::SetAt(int n, int indx) //Sets the value for a given index; array not allowed to grow.
	{	
		int i=GetUpperBound();
		if((indx>=0) && (indx<=i))
			a[indx]=n;
	}
	void cArray::Add(int n) //Adds an element to the end of the array; grows the array if necessary.
	{
		if(count>=size)
			size+=GROWBY;
		a[count]=n;
		count++;
	}
	void cArray::Append(cArray *ar) //Appends another array to the array; grows the array if necessary
	{
		Copy(ar);	
		ar->RemoveAll();
	}
	void cArray::Copy(cArray *ar) //Copies another array to the array; grows the array if necessary.
		{
		int t=ar->GetCount();
		for (int i=0; i<t; i++)
			Add(ar->a[i]);		
		}	
	void cArray::InsertAt(int n, int indx) //Inserts an element at a specified index.
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
	void cArray::RemoveAt(int indx) //Removes an element at a specific index.
	{
		if (indx<=count-1)
		{
			for (int i=indx; i<count; i++)
				a[i]=a[i+1];
			count--;
		}		
	}
	int& cArray::operator [](int indx) //Sets or gets the element at the specified index.
	{
		return a[indx];
	}
	void cArray::show()
	{
		for (int i=0; i<count; i++)
			cout<<a[i]<<"  ";
		cout<<endl;
	}