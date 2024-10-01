#include "headers.h"
using namespace std;
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
	cout<<"New size of vector is "<<obj2.GetSize()
	<<", count of elements "<<obj2.GetCount()
	<<", largest valid index "<<obj2.GetUpperBound()<<endl;
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