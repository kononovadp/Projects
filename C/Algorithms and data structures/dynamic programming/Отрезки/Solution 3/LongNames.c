#include <stdio.h>
#include <malloc.h>
void SortParts(int *parts,int PartsCount)
{
	char sorted=0;
	int i,t;
	while(sorted!=1)
	{
		sorted=1;
		for(i=0; i<PartsCount-1; i++)
			if(parts[i]<parts[i+1])
			{
				sorted=0;
				t=parts[i];
				parts[i]=parts[i+1];
				parts[i+1]=t;
			}
	}
}
//ф-я рекурсивно пытается получить отрезок требуемой длины
char GetPart(int PartsCount,int *parts,char *BusyParts,int RequiredNumber,char **CacheOfUnaccessibleParts)
{
	int i;
	if(RequiredNumber==0)
		return 1;
	for(i=0; i<PartsCount; i++)
		//если отрезок можно получить с помощью одного из существующих и он не был определен как недосягаемый...
		if(parts[i]<=RequiredNumber && BusyParts[i]==0 && CacheOfUnaccessibleParts[RequiredNumber][i]==0)
		{
			BusyParts[i]=1;
			if(GetPart(PartsCount,parts,BusyParts,RequiredNumber-parts[i],CacheOfUnaccessibleParts)==1)
				return 1;
			else
			{	//иначе помечаем его как недосягаемый и ищем дальше
				BusyParts[i]=0;
				CacheOfUnaccessibleParts[RequiredNumber][i]=1;
			}
		}
	return 0;
}
int GetBiggestLengthOfTwoEqualParts(int PartsCount, int *parts)
{	
	int i,j,PreviousSum,sum,result;
	char **CacheOfUnaccessibleParts,*BusyParts;
	if(PartsCount<2)
		return 0;
	BusyParts=(char*)calloc(PartsCount,sizeof(char));
	for(i=0,sum=0; i<PartsCount; i++)
		sum=sum+parts[i];
	sum=sum/2;
	PreviousSum=sum+1;
	CacheOfUnaccessibleParts=(char**)calloc(PreviousSum,sizeof(char*));
	for(i=0; i<PreviousSum; i++)
		CacheOfUnaccessibleParts[i]=(char*)calloc(PartsCount,sizeof(char));
	for(result=0; sum>parts[PartsCount-1] && result==0; sum--)
	{	//перед поиском нового отрезка обнуляем кэш
		for(i=0; i<=sum; i++)
			for(j=0; j<PartsCount; j++)
				CacheOfUnaccessibleParts[i][j]=0;
		if(GetPart(PartsCount,parts,BusyParts,sum,CacheOfUnaccessibleParts)==1)
			result=GetPart(PartsCount,parts,BusyParts,sum,CacheOfUnaccessibleParts);
		for(i=0; i<PartsCount; i++)
			BusyParts[i]=0;
	}	
	for(i=0; i<PreviousSum; i++)
		free(CacheOfUnaccessibleParts[i]);
	free(BusyParts);
	free(CacheOfUnaccessibleParts);
	if(result==0)
		sum=-1;	
	return sum+1;
}
int main(void)
{
	int i,MyResult,RightResult,GeneralPartsCount,PartsCount,*parts;
	FILE *TestFile=fopen("test.txt","r");
	FILE *ResultsFile=fopen("test cases output.txt","r");
	fscanf(TestFile,"%d",&GeneralPartsCount);
	while(GeneralPartsCount-->0)
	{
		fscanf(TestFile,"%d",&PartsCount);
		fscanf(ResultsFile,"%d",&RightResult);
		parts=(int*)malloc(PartsCount*sizeof(int));
		for(i=0; i<PartsCount; i++)
		{
			fscanf(TestFile,"%d ",&parts[i]);
			printf("%d ",parts[i]);
		}
		printf("\nsorted: ");
		SortParts(parts,PartsCount);
		for(i=0; i<PartsCount; i++)
			printf("%d ",parts[i]);
		MyResult=GetBiggestLengthOfTwoEqualParts(PartsCount,parts);
		printf("\nBiggest length of two equal parts: %d; right resultult=%d;\n",MyResult,RightResult);
		free(parts);
		printf("==============================================================\n");
	}
	fclose(TestFile);
	fclose(ResultsFile);
	return 0;
}