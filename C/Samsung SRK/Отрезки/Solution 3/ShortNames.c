#include <stdio.h>
#include <malloc.h>
void SortParts(int *p,int pc)
{
	char sorted=0;
	int i,t;
	while(sorted!=1)
	{
		sorted=1;
		for(i=0; i<pc-1; i++)
			if(p[i]<p[i+1])
			{
				sorted=0;
				t=p[i];
				p[i]=p[i+1];
				p[i+1]=t;
			}
	}
}
//ф-я рекурсивно пытается получить отрезок требуемой длины
//pc - PartsCount; p - parts; bp - BusyParts; rn - RequiredNumber
//c - CacheOfUnaccessibleParts
char GetPart(int pc,int *p,char *bp,int rn,char **c)
{
	int i;
	if(rn==0)
		return 1;
	for(i=0; i<pc; i++)
		//если отрезок можно получить с помощью одного из существующих и он не был определен как недосягаемый...
		if(p[i]<=rn && bp[i]==0 && c[rn][i]==0)
		{
			bp[i]=1;
			if(GetPart(pc,p,bp,rn-p[i],c)==1)
				return 1;
			else
			{	//иначе помечаем его как недосягаемый и ищем дальше
				bp[i]=0;
				c[rn][i]=1;
			}
		}
	return 0;
}
int GetBiggestLengthOfTwoEqualParts(int pc, int *p)
{
	int i,j,PrevSum,sum,res;
	char **c,*bp;
	if(pc<2)
		return 0;
	bp=(char*)calloc(pc,sizeof(char));	
	for(i=0,sum=0; i<pc; i++)
		sum=sum+p[i];
	sum=sum/2;
	PrevSum=sum+1;
	c=(char**)calloc(PrevSum,sizeof(char*));
	for(i=0; i<PrevSum; i++)
		c[i]=(char*)calloc(pc,sizeof(char));
	for(res=0; sum>p[pc-1] && res==0; sum--)
	{	//перед поиском нового отрезка обнуляем кэш
		for(i=0; i<=sum; i++)
			for(j=0; j<pc; j++)
				c[i][j]=0;
		if(GetPart(pc,p,bp,sum,c)==1)
			res=GetPart(pc,p,bp,sum,c);
		for(i=0; i<pc; i++)
			bp[i]=0;
	}	
	for(i=0; i<PrevSum; i++)
		free(c[i]);
	free(bp);
	free(c);
	if(res==0)
		sum=-1;	
	return sum+1;
}
int main(void)
{
	int i,MyResult,RightResult,GeneralPartsCount,pc,*p;
	FILE *TestFile=fopen("test.txt","r");
	FILE *ResultsFile=fopen("test cases output.txt","r");
	fscanf(TestFile,"%d",&GeneralPartsCount);
	while(GeneralPartsCount-->0)
	{
		fscanf(TestFile,"%d",&pc);
		fscanf(ResultsFile,"%d",&RightResult);
		p=(int*)malloc(pc*sizeof(int));
		for(i=0; i<pc; i++)
		{
			fscanf(TestFile,"%d ",&p[i]);
			printf("%d ",p[i]);
		}
		printf("\nsorted: ");
		SortParts(p,pc);
		for(i=0; i<pc; i++)
			printf("%d ",p[i]);
		MyResult=GetBiggestLengthOfTwoEqualParts(pc,p);
		printf("\nBiggest length of two equal p: %d; right resultult=%d;\n",MyResult,RightResult);
		free(p);
		printf("==============================================================\n");
	}
	fclose(TestFile);
	fclose(ResultsFile);
	return 0;
}