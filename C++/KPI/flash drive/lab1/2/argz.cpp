#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream> 
using namespace std;
int error_t_argz_create_sep (const char *s,int sep,char **argz,size_t *argz_len)
{ int j=0,sl=0;
  size_t kch=0; 
  argz[0]=new char[10];
  for (int i=0; i<=strlen(s);i++)
	{  	kch++;
		if (s[i]==sep) 
		{
			sl++;
			argz[sl]=new char[10];
			j=0;	
		}
		else
		{
			argz[sl][j]=s[i];
			argz[sl][j+1]='\0';
			j++;
		}
	}
	argz_len=&kch;
	cout<<"argz_len= "<<*argz_len<<endl;
	return sl;	}	