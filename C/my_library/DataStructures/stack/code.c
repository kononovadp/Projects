#include "stack.h"
int main(void)
{
	char str[50];
	stack mystack;
	InitializeStack(&mystack);
	printf("String: ");
	scanf("%s",str);
	for(int i=0; i<strlen(str); i++)
		AddToStack(&mystack,str[i]);
	printf("Res: ");
	ShowStack(&mystack);
	printf("Deleting elements:\n");
	for(int i=0; i<strlen(str); i++)
	{
		DeleteFromStack(&mystack);
		ShowStack(&mystack);
	}
    return 0;
}
