#include <iostream>
#include "DoublyLinkedList.h"
using namespace std;
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
	//dll.push_back("acdj");
	//dll.push_back("acdj");
	//dll.push_back("6");
	//dll.push_back("cbdk");
	//dll.push_back("6");
	//dll.push_back("cbdk");
	//dll.push_back("8");
	//dll.push_back("acdj");	
	//dll.insert_after("6","1111");
	DoublyLinkedList d2;
	d2.push_front("d1");
	d2.push_front("d2");
	d2.push_front("d3");
	d2.push_front("d4");
	d2.push_front("d5");
	d2.push_front("dA");
	d2.push_front("dB");
	d2.push_front("dC");
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