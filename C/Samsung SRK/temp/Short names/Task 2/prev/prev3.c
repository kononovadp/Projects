#include <stdio.h>
#include <malloc.h>
struct num
{
	int pc;
	int ic;	
	int *it;
};
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
struct num *PlusOrMult(struct num **a,int rn, char op)
{
	int i,t,j,ind,prevrn=rn;
	int min=rn*2;
	int minind=rn*2;
	struct num *res=(struct num *)malloc(sizeof(struct num));
	res->pc=0;
	res->ic=0;
	for(i=1; i<rn; i++)
	{
		if(op=='+')
		{
			if(a[i]->ic==0)
				continue;
			ind=rn-i;
			if(ind<0 || a[ind]->ic==0)
				continue;
		}
		else
			if(op=='*')
			{
				if(a[i]->ic==0 || rn%i>0)
					continue;
				ind=rn/i;
				if(a[ind]->ic==0)
					continue;
			}
		t=a[i]->ic+a[ind]->ic;
		if(t<min)
		{
			min=t;
			minind=ind;
		}
	}
	
	if(min<rn*2)
	{
		res->ic=min;
		res->it=(int*)malloc(sizeof(int)*min);
		for(i=0,res->pc=0; i<a[minind]->ic; i++)
		{
			res->it[i]=a[minind]->it[i];
			res->pc=res->pc+GetDigitsCount(res->it[i])+1;
			if(op=='+')
				rn=rn-res->it[i];
			else
				if(op=='*')
					rn=rn/res->it[i];
		}
		res->it[i]=rn;
		res->pc=res->pc+1;
	}
	return res;
}
int GetRes(int *numbers,int nc,char *ops,int oc,int mpc,int rn)
{
	int i,j,t,minreq,divreq,nrn;
	struct num **a,*multres=NULL;
	struct num *plusres=NULL;
	for(i=0; i<oc; i++)
	{
		if(ops[i]=='-')
			minreq=1;
		if(ops[i]=='/')
			divreq=1;
	}
	if(divreq==1)
		nrn=rn*rn;
	else
		if(minreq==1)
			nrn=rn+rn;
		else
			nrn=rn+1;
	nrn=rn+1;
	a=(struct num**)malloc(sizeof(struct num*)*nrn);
	for(i=0; i<nrn; i++)
	{
		t=CheckNumber(numbers,nc,i);
		a[i]=(struct num*)malloc(sizeof(struct num));
		if(t>0)
		{			
			a[i]->pc=t;
			a[i]->ic=1;
			a[i]->it=(int*)malloc(sizeof(int));
			a[i]->it[0]=i;
		}
		else
		{
			for(j=0; j<oc; j++)
				if(ops[j]=='+')
					plusres=PlusOrMult(a,i,'+');
				else
					if(ops[j]=='*')
						multres=PlusOrMult(a,i,'*');
			/*printf("\n+ i=%d, pc=%d: ",i,plusres->pc);
			for(j=0; j<plusres->ic; j++)
				printf("%d ",plusres->it[j]);
			printf("\n* i=%d, pc=%d: ",i,multres->pc);
			for(j=0; j<multres->ic; j++)
				printf("%d ",multres->it[j]);*/
			if(plusres==NULL && multres==NULL)
			{
				a[i]=(struct num*)malloc(sizeof(struct num));
				a[i]->pc=0;
				a[i]->ic=0;
			}
			else
				if(plusres!=NULL && multres==NULL)
					a[i]=plusres;
				else
					if(plusres==NULL && multres!=NULL)
						a[i]=multres;
					else
						if(plusres!=NULL && multres!=NULL)
							if(plusres->pc==0 && multres->pc==0)
								a[i]=multres;
							else
								if(plusres->pc==0 && multres->pc>0)
									a[i]=multres;
								else
									if(plusres->pc>0 && multres->pc==0)
										a[i]=plusres;
									else
										if(plusres->pc<multres->pc)
											a[i]=plusres;
										else
											if(multres->pc<plusres->pc)
												a[i]=multres;
		}
	}
	for(i=0; i<nrn; i++)
	{
		printf("\ni=%d, pc=%d: ",i,a[i]->pc);
		for(j=0; j<a[i]->ic; j++)
			printf("%d ",a[i]->it[j]);
	}
	return nrn;
}
int main(void)
{
	int res,i,j,NumbersCount,OperationsCount,MaxPressCount,RequiredNumber,*numbers,TasksCount=0;
	char *operations;
	FILE *f=fopen("test.txt","r");
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
		printf("\n		RES = %d",res);
		printf("\n=====================================================\n");
		free(numbers);
		free(operations);
	}
	fclose(f);
	return 0;
}