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
			if(a[i]<a[i+1])
			{
				sorted=0;
				t=a[i];
				a[i]=a[i+1];
				a[i+1]=t;
			}
	}
}
char func(int pc,int *p,char *bp,int rn)
{
	if(rn==0)
		return 1;
	for(int i=0; i<pc; i++)
		if(p[i]<=rn && bp[i]==0)
		{
			bp[i]=1;
			if(func(pc,p,bp,rn-p[i])==1)
				return 1;
		}
	return 0;
}
int GetBiggestLengthOfTwoEqualParts(int pc, int *p)
{
	if(pc<2)
		return 0;
	int res,i,sum,r;
	char *bp=(char*)calloc(pc,sizeof(char));
	for(i=0,sum=0; i<pc; i++)
		sum=sum+p[i];
	sum=sum/2;
	for(r=0; sum>p[pc-1] && r==0; sum--)
	{
		if(func(pc,p,bp,sum)==1)
			r=func(pc,p,bp,sum);
		for(i=0; i<pc; i++)
			bp[i]=0;
	}
	free(bp);
	if(r==0)
		sum=-1;
	return sum+1;
}
int main(void)
{	
	int resultult,i,Rightresultult,StrPartsCount,PartsCount,*numbers=NULL;
	FILE *f=fopen("test.txt","r");
	FILE *f2=fopen("test cases output.txt","r");
	fscanf(f,"%d",&StrPartsCount);	
	while(StrPartsCount-->0)
	{
		fscanf(f,"%d",&PartsCount);
		fscanf(f2,"%d",&Rightresultult);
		numbers=(int*)malloc(PartsCount*sizeof(int));
		for(i=0; i<PartsCount; i++)
		{
			fscanf(f,"%d ",&numbers[i]);
			printf("%d ",numbers[i]);
		}
		printf("\nsorted: ");
		sort(numbers,PartsCount);
		for(i=0; i<PartsCount; i++)
			printf("%d ",numbers[i]);
		resultult=GetBiggestLengthOfTwoEqualParts(PartsCount,numbers);
		printf("\nBiggest length of two equal parts: %d; right resultult=%d;\n",resultult,Rightresultult);
		free(numbers);
		printf("==============================================================\n");
	}
	fclose(f);
	fclose(f2);
	return 0;
}