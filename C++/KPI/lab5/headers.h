#include <iostream>
#pragma once
class cArray{
#define GROWBY 10 //The minimum number of element slots to allocate if a size increase is necessary. 
int *a;
int size;
int count;
public:	
	cArray::cArray(void) //Constructs an empty array.
	{
		a=new int[0];
		size=0;	
		count=0;
	}
	~cArray(void)
	{
		a=NULL;
	}
	int GetSize(); //const //Gets the number of elements in this array.
	int GetCount() const; //Gets the number of elements in this array.
	int GetUpperBound() const; //Returns the largest valid index.
	bool IsEmpty()const; //Determines whether the array is empty.
	void SetSize(int nNewSize); //Establishes the size of an empty or existing array; allocates memory if necessary.
	void FreeExtra(); //Frees all unused memory above the current upper bound.	
	void RemoveAll(); //Removes all the elements from this array.
	int GetAt(int indx)const; //Returns the value at a given index.
	void SetAt(int n, int indx); //Sets the value for a given index; array not allowed to grow.
	void Add(int n); //Adds an element to the end of the array; grows the array if necessary.
	void Append(cArray *ar); //Appends another array to the array; grows the array if necessary
	void Copy(cArray *ar); //Copies another array to the array; grows the array if necessary.
	void InsertAt(int n, int indx); //Inserts an element at a specified index.
	void RemoveAt(int indx); //Removes an element at a specific index.
	int& operator [](int indx); //Sets or gets the element at the specified index.
	void show();
private:
};