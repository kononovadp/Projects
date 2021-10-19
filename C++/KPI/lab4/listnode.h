#include <iostream>
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