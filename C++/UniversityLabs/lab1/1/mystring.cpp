#include <string>
#include <iostream> 
#include <stdio.h>
using namespace std;
int substr(char *s1,char *s2)
{	
	char t[] = ""; int i=0; int k=strlen(s1); int r=1;
	for (i=0; i<k; i++)
	{	char t[100]={0};
		strncpy(t,s1,strlen(s2));
		if (strcmp(t,s2)==0) 
			return r;	
		else
		if (i==k && t!=s2)
		{
			r=0; 
			return r;
		}
		r++; s1++;
	}
}
//вариант 2
/*int substr(char s1[], char s2[])
{ int s1len=strlen(s1);
char t[100]={0};
for (int i=1;i<s1len; i++)
{   strncpy(t,s1,strlen(s2));
	if (strcmp(t,s2)==0	) return i;
	s1=s1+1;	}
return 0;	}*/