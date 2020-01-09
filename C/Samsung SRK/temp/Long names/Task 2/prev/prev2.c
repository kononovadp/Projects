#include <stdio.h>
#include <malloc.h>
struct num
{
	char op;
	int n;
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
	return -1;
}
int GetMaxNumber(int rn, int c)
{
	int i,res=rn;
	for(i=0; i<c; i++)
	{
		res*=10;
		res+=rn;
	}
	return res;
}
struct num *plus(struct num **p,int pn,int *an,int kn,int rn)
{
	int i,k,t,min,minind,ind;
	struct num *res=(struct num*)malloc(sizeof(struct num));
	res->n=rn;
	res->ic=0;
	res->op='+';
	min=rn+1;
	minind=rn+1;
	for(i=0; i<kn; i++)
	{
		t=rn-an[i];
		ind=t-p[0]->n;
		if(ind>=0 && t>=p[0]->n && p[ind]->ic>0 && p[ind]->ic<min)
		{
			min=p[ind]->ic;
			minind=ind;
		}
	}
	if(min<rn+1)
	{		
		res->ic=min+1;
		res->it=(int*)malloc(sizeof(int)*(min+1));		
		for(i=0,t=rn; i<min; i++)
		{
			res->it[i]=p[minind]->it[i];
			t=t-p[minind]->it[i];
		}
		res->it[i]=t;
	}
	return res;
}
struct num *mult(struct num **p,int pn,int *an,int kn,int rn)
{
	int i,k,t,min,minind,ind;
	struct num *res=(struct num*)malloc(sizeof(struct num));
	res->n=rn;
	res->ic=0;
	res->op='*';
	min=rn+1;
	minind=rn+1;
	for(i=0; i<=kn; i++)
	{
		if(an[i]==0)
			continue;
		t=rn/an[i];
		ind=t-p[0]->n;
		if(ind>=0 && t>=p[0]->n && p[ind]->ic>0 && p[ind]->ic<min && an[i]*t==rn)
		{
			min=p[ind]->ic;
			minind=ind;
		}
	}
	if(min<rn+1)
	{
		res->ic=min+1;
		res->it=(int*)malloc(sizeof(int)*(min+1));
		for(i=0,t=rn; i<min; i++)
		{
			res->it[i]=p[minind]->it[i];
			t=t/p[minind]->it[i];
		}
		res->it[i]=t;		
	}
	return res;
}
struct num *minus(struct num **p,int pn,int *an,int kn,int rn)
{
	int i,t,min,max=10000;//GetMaxNumber(an[kn-1],kn-1);
	struct num *res=(struct num*)malloc(sizeof(struct num));
	res->n=rn;
	res->ic=0;
	res->op='-';
	for(i=rn,min=0; i<max && min!=1; i++)
	{
		if(CheckNumber(an,kn,i)==-1)
			continue;
		t=i-rn;
		if(CheckNumber(an,kn,t)>-1)
			min=1;
	}
	if(min==1)
	{
		res->ic=2;
		res->it=(int*)malloc(sizeof(int)*2);
		res->it[0]=i-1;
		res->it[1]=t;
	}
	return res;
}
struct num *divide(struct num **p,int pn,int *an,int kn,int rn)
{
	int i,t,min,max=10000;//GetMaxNumber(an[kn-1],kn-1);
	struct num *res=(struct num*)malloc(sizeof(struct num));
	res->n=rn;
	res->ic=0;
	res->op='/';
	for(i=rn,min=0; i<max && min!=1; i++)
	{
		if(CheckNumber(an,kn,i)==-1)
			continue;
		if(rn==0 || i==0)
			t=0;
		else
		{
			t=i/rn;
			if(CheckNumber(an,kn,t)>-1 && t*rn==i)
				min=1;
		}
	}
	if(min==1)
	{
		res->ic=2;
		res->it=(int*)malloc(sizeof(int)*2);
		res->it[0]=i-1;
		res->it[1]=t;
	}
	return res;
}
struct num **GetNumber(int *nums,int kc,char op,int rn)
{
	int i,pn,cn,enf,anc,kn,*an=(int*)malloc(sizeof(int)*rn);
	struct num **res;
	if(CheckNumber(nums,kc,rn)>-1)
	{
		res=(struct num**)malloc(sizeof(struct num*));
		res[0]=(struct num*)malloc(sizeof(struct num));
		res[0]->op=0;
		res[0]->n=rn;
		res[0]->ic=1;
		res[0]->it=(int*)malloc(sizeof(int));
		res[0]->it[0]=rn;
		return res;
	}
	res=(struct num**)malloc(sizeof(struct num*)*(rn+1));
	if(nums[0]=='0')
		kn=1;
	else
		kn=0;
	for(i=kn,anc=0; i<rn; i++)
		if(CheckNumber(nums,kc,i)>-1)
		{
			an[anc]=i;
			anc++;
		}
	for(cn=0,pn=0; cn<=rn; cn++,pn++)
	{
		if(cn==an[kn+1] && kn<anc)
			kn++;
		res[pn]=(struct num*)malloc(sizeof(struct num)*1);
		res[pn]->n=cn;		
		res[pn]->ic=0;
		res[pn]->pc=0;
		res[pn]->op=op;
		enf=0;
		if(cn==an[kn])
		{
			res[pn]->n=cn;
			res[pn]->ic=1;
			res[pn]->it=(int*)malloc(sizeof(int));
			res[pn]->it[0]=cn;
			res[pn]->pc=GetDigitsCount(cn);
			enf=1;
		}
		else
			if(op=='+')
				res[pn]=plus(res,pn,an,anc,cn);
			else
				if(op=='*')
					res[pn]=mult(res,pn,an,anc,cn);
				else
					if(op=='-')
						res[pn]=minus(res,pn,nums,kc,cn);
					else
						res[pn]=divide(res,pn,nums,kc,cn);
		if(enf==0)
			for(i=0,res[pn]->pc=0; i<res[pn]->ic; i++)
				res[pn]->pc=res[pn]->pc+GetDigitsCount(res[pn]->it[i])+1;
	}
	return res;
}
int GetRes(int *numbers,int nc,char *ops,int oc,int mpc,int rn)
{
	int i,j,k,min;
	struct num ***nums,**res;
	if(CheckNumber(numbers,nc,rn)>-1)
		return GetDigitsCount(rn);
	int nrn=rn;
	nums=(struct num ***)malloc(sizeof(struct num**)*oc);
	res=(struct num **)malloc(sizeof(struct num *)*(nrn+1));
	for(i=0; i<oc; i++)
		if(ops[i]=='+')
			nums[i]=GetNumber(numbers,nc,'+',nrn);
		else
			if(ops[i]=='-')
				nums[i]=GetNumber(numbers,nc,'-',nrn);
			else
				if(ops[i]=='*')
					nums[i]=GetNumber(numbers,nc,'*',nrn);
				else
					if(ops[i]=='/')
						nums[i]=GetNumber(numbers,nc,'/',nrn);	
	for(i=0; i<=nrn; i++)
	{
		res[i]=nums[0][i];
		for(j=0; j<oc; j++)
		{
			if((res[i]->pc==0 && nums[j][i]->pc>0) || (res[i]->pc>0 && nums[j][i]->pc>0 && nums[j][i]->pc<res[i]->pc))
				res[i]=nums[j][i];
			/*printf("\n%c %d: ",nums[j][i]->op,nums[j][i]->n);
			for(k=0; k<nums[j][i]->ic; k++)
				printf("%d ",nums[j][i]->it[k]);
			printf(" pc=%d",nums[j][i]->pc);*/
		}
		/*printf("\nMIN %c %d: ",res[i]->op,res[i]->n);
		for(k=0; k<res[i]->ic; k++)
			printf("%d ",res[i]->it[k]);
		printf(" pc=%d",res[i]->pc);
		printf("\n------------------");*/
	}
	/*for(i=0; i<=nrn; i++)
	{
		printf("\n%c %d: ",res[i]->op,res[i]->n);
		for(j=0; j<res[i]->ic; j++)
			printf("%d ",res[i]->it[j]);
		printf("pc = %d",res[i]->pc);
	}*/
	for(i=0; i<oc; i++)
	{
		printf("\n %c %d: ",nums[i][nrn]->op,nums[i][nrn]->n);
		for(j=0; j<nums[i][nrn]->ic; j++)
			printf("%d ",nums[i][nrn]->it[j]);
		printf("pc = %d",nums[i][nrn]->pc);
	}
	printf("\nMIN %c %d: ",res[nrn]->op,res[nrn]->n);
	for(j=0; j<res[nrn]->ic; j++)
		printf("%d ",res[nrn]->it[j]);
	printf("pc = %d",res[nrn]->pc);
	if(res[nrn]->pc==0 || res[nrn]->pc>mpc)
		return -1;
	else
		return res[nrn]->pc;
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