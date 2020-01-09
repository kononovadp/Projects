#include <stdio.h>
#include <string>
#include <cstring>
#include <iostream> 
#include "argz.h"
using namespace std;
int main()
{ int kch;
	char s[] = "SHELL=/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8";//"abc:degd:efhf"; 
	int sep=58;
	char **argz;
	size_t *argz_len; 
	argz= new char * [10];
	int k=error_t_argz_create_sep (s,sep,argz,argz_len);
    for (int i=0; i<=k;i++) 
		cout<<argz[i]<<endl;
	//cout<<argz_len<<endl;
	cin.get();	
}