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
int GetDigitsCount(int n)
{
	int i=0;
	while(n>0)
	{
		n/=10;
		i++;
	}
	return i;
}
int CheckNumber(int *numbers,int NumbersCount,int RequiredNumber)
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
int GetMax(int rn)
{
	int max=1;	
	while(rn>1)
	{		
		max*=10;
		rn/=10;
	}
	return max*10;
}	
int calc(int *kn,int kc,char *op,int oc,int cpc,int mpc,int prevmin,int rn,unsigned long long int max,int *prevres, FILE *f)
{
	fprintf(f,"\nrn=%d cpc=%d",rn,cpc);
	int i,j,min,min2,res,t;	
	if(prevres[rn]>0)
		return cpc+prevres[rn];
	if(prevres[rn]==-1)
		return -1;
	if(cpc>prevmin || cpc>mpc)
		return -1;
	t=CheckNumber(kn,kc,rn);
	if(t>0)
	{
		if(cpc==0)
			cpc=t;
		else
			cpc+=t+1;
		return cpc;
	}
	min=mpc+1;
	for(i=1; i<rn; i++)
	{
		t=CheckNumber(kn,kc,i);
		if(t<1)
			continue;
		res=min;
		if(i*rn<=max)
		{
			res=calc(kn,kc,op,oc,cpc+t+1,mpc,min,rn*i,max,prevres,f);
			if(res>-1 && res<min)
				return res;
		}
	}
	if(min==mpc+1)
		return prevres[rn]=-1;
	return prevres[rn]=min;
}
int GetRes(int *kn,int kc,char *op,int oc,int mpc,int rn)
{
	int i,res,max,*prevres,t=rn;
	FILE *f=fopen("results.txt","w");
	max=GetMax(rn);
	prevres=(int*)calloc(max,sizeof(int));
	res=calc(kn,kc,op,oc,0,mpc,mpc,t,max,prevres,f);
	free(prevres);
	return res;
}
int main(void)
{
	int res,i,j,NumbersCount,OperationsCount,MaxPressCount,RequiredNumber,*numbers,RightResult,TasksCount=0;
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
		fscanf(f," %d",&RequiredNumber);
		printf("%d. NumbersCount = %d: ",j+1,NumbersCount);
		for(i=0; i<NumbersCount; i++)
			printf("%d ",numbers[i]);
		printf("OperationsCount = %d ",OperationsCount);
		for(i=0; i<OperationsCount; i++)
			printf("%c ",operations[i]);
		printf("\nMaxPressCount = %d; RequiredNumber = %d; ",MaxPressCount,RequiredNumber);
		res=GetRes(numbers,NumbersCount,operations,OperationsCount,MaxPressCount,RequiredNumber);
		fscanf(ft,"%d",&RightResult);
		printf("\n		RES = %d; Right Result = %d",res,RightResult);
		printf("\n=====================================================\n");
		free(numbers);
		free(operations);
	}
	fclose(f);
	fclose(ft);
	return 0;
}