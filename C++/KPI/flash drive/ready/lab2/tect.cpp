#include <iostream> 
#include "mem_dispatcher.h"
int main()
{	mem_dispatcher *md;
	md=new mem_dispatcher;
	init(md);
	menu(md);
	//allocate(md,5); //show_memory_map(md);
	//allocate(md,20); //show_memory_map(md);
	//allocate(md,30); //show_memory_map(md);
	//allocate(md,3); //show_memory_map(md);
	//deallocate(md,4); show_memory_map(md);
	//deallocate(md,2); show_memory_map(md);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//deallocate(md,3); deallocate(md,3); show_memory_map(md);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
	//cin.get();
}
