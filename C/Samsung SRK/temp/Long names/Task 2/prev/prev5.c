#include <stdio.h>
#include <malloc.h>
void sort(int *a,int n)
{
	char sorted=0;
	int i,t;
	while(sorted!=1)
	{
		sorted=1;
		for(i=0; i<n-1; i++)
			if(a[i]>a[i+1])
			{
				sorted=0;
				t=a[i];
				a[i]=a[i+1];
				a[i+1]=t;
			}
	}
}
int GetDigitsCount(long long int n)
{
	int i=0;
	while(n>0)
	{
		n/=10;
		i++;
	}
	return i;
}
long long int CheckNumber(int *numbers,int NumbersCount,long long int RequiredNumber)
{
	int i,j,mod,nc=GetDigitsCount(RequiredNumber);
	char found=1;
	if(RequiredNumber==0)
	{
		for(i=0; i<NumbersCount; i++)
			if(numbers[i]==0)
				return 1;
		return -1;
	}
	for(i=0; i<nc && found==1; i++)
	{
		found=0;
		mod=RequiredNumber%10;
		RequiredNumber/=10;
		for(j=0; j<NumbersCount && found==0; j++)
			if(numbers[j]==mod)
				found=1;
	}
	if(found==1)
		return nc;
	return 0;
}
long long int GetMax(long long int rn)
{
	long long int max=1;	
	while(rn>1)
	{		
		max*=10;
		rn/=10;
	}
	return max*10;
}
long long int GetDivRes(long long int *cache,long long int size,long long int rn)
{
	long long int i;
	for(i=1; rn*i<size+1; i++)
		if(cache[i]>0 && cache[rn*i]>0)
			return cache[i]+cache[rn*i]+2;
	return 0;
}
long long int GetMinusRes(long long int *cache,long long int size,long long int rn)
{
	long long int i;
	for(i=1; rn+i<size+1; i++)
		if(cache[i]>0 && cache[rn+i]>0)
			return cache[i]+cache[rn+i]+2;
	return 0;
}
long long int calc(int *kn,int kc,char *op,int oc,int cpc,int min,long long int rn,long long max,long long int *cache, FILE *f)
{
	long long int i,res,t;
	long long int divres=0;
	long long int minusres=0;
	int j,prevmin=min;
	if(cache[rn]==-1)
		return -1;
	if(cpc>min)
		return -1;
	if(cache[rn]>0)
	{
		if(cpc==0)
			cpc=cache[rn];
		else
			cpc+=cache[rn]+1;
		return cpc;
	}
	if(rn<kn[0])
		rn=max;
	for(i=0; i<kc; i++)
		if(op[i]=='/')
			divres=GetDivRes(cache,max,rn);
		else
			if(op[i]=='-')
				minusres=GetMinusRes(cache,max,rn);
	for(i=0; i<rn; i++)
	{
		t=cache[i];
		if(t<1)
			continue;
		for(j=0; j<oc; j++)
		{
			res=min;
			if(op[j]=='+')
				res=calc(kn,kc,op,oc,cpc+t+1,prevmin,rn-i,max,cache,f);
			else
				if(op[j]=='*' && i>1 && rn%i==0)
					res=calc(kn,kc,op,oc,cpc+t+1,prevmin,rn/i,max,cache,f);
				else
					if(op[j]=='/' && i>0 && rn*i<=max && cache[rn*i]>0)
						res=divres+cpc;//res=cpc+t+cache[rn*i]+2;
					else
						if(op[j]=='-' && rn+i<=max && cache[rn+i]>0)
							res=minusres+cpc;//res=cpc+t+cache[rn+i]+2;
			if(res>0 && res<min)
				min=res;
		}
	}
	if(min==prevmin)
		return cache[rn]=-1;
	cache[rn]=min;
	
	return min;
}
long long int GetRes(int *kn,int kc,char *op,int oc,int mpc,long long int rn)
{
	long long int i,res,*cache,max=rn;
	FILE *f=fopen("results.txt","w");
	for(int i=0; i<kc; i++)
		if(op[i]=='/' || op[i]=='-')
		{
			max=GetMax(max);
			break;
		}
	cache=(long long int*)calloc(max+1,sizeof(long long int));	
	for(i=0; i<=max; i++)
		cache[i]=CheckNumber(kn,kc,i);
	res=calc(kn,kc,op,oc,0,mpc+1,rn,max,cache,f);
	free(cache);
	return res;
}
int main(void)
{
	int i,j,NumbersCount,OperationsCount,MaxPressCount,*numbers,RightResult,TasksCount=0;
	long long int res,RequiredNumber;
	char *operations;
	FILE *f=fopen("test.txt","r");
	FILE *ft=fopen("tests-output.txt","r");
	fscanf(f,"%d",&TasksCount);
	for(j=0; j<TasksCount; j++)
	{
		fscanf(f,"%d",&NumbersCount);
		numbers=(int*)malloc(NumbersCount*sizeof(int));
		for(i=0; i<NumbersCount; i++)
			fscanf(f,"%d ",&numbers[i]);
		sort(numbers,NumbersCount);
		fscanf(f,"%d",&OperationsCount);
		operations=(char*)malloc(OperationsCount*sizeof(char));
		for(i=0; i<OperationsCount; i++)
			fscanf(f," %c",&operations[i]);
		fscanf(f,"%d",&MaxPressCount);
		fscanf(f," %lld",&RequiredNumber);
		printf("%d. NumbersCount = %d: ",j+1,NumbersCount);
		for(i=0; i<NumbersCount; i++)
			printf("%d ",numbers[i]);
		printf("OperationsCount = %d ",OperationsCount);
		for(i=0; i<OperationsCount; i++)
			printf("%c ",operations[i]);
		printf("\nMaxPressCount = %d; RequiredNumber = %lld; ",MaxPressCount,RequiredNumber);
		res=GetRes(numbers,NumbersCount,operations,OperationsCount,MaxPressCount,RequiredNumber);
		fscanf(ft,"%d",&RightResult);
		printf("\n		RES = %lld; Right Result = %d",res,RightResult);
		printf("\n=====================================================\n");
		free(numbers);
		free(operations);
	}
	fclose(f);
	fclose(ft);
	return 0;
}