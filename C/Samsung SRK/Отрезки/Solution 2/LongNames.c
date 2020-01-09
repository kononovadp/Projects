#include <stdio.h>
#include <malloc.h>
void sort(int *parts,int PartsCount)
{
	char sorted=0;
	int i,t;
	while(sorted!=1)
	{
		sorted=1;
		for(i=0; i<PartsCount-1; i++)
			if(parts[i]>parts[i+1])
			{
				sorted=0;
				t=parts[i];
				parts[i]=parts[i+1];
				parts[i+1]=t;
			}
	}
}
//ф-я проверяет, можно ли получить отрезок путем отнимания его от существующего свободного
char GetPart(int PartsCount,int *parts,char **BusyPartsIndexes,int PartNumber,int RequiredNumber)
{
	int i,MinusResult;
	MinusResult=RequiredNumber-parts[PartNumber];
	if(MinusResult>=parts[0] && BusyPartsIndexes[MinusResult]!=NULL && BusyPartsIndexes[MinusResult][PartNumber]==0)
	{
		if(BusyPartsIndexes[RequiredNumber]==NULL)
			BusyPartsIndexes[RequiredNumber]=(char*)calloc(PartsCount,sizeof(char));
		for(i=0; i<PartsCount; i++)
			BusyPartsIndexes[RequiredNumber][i]=BusyPartsIndexes[MinusResult][i];
		BusyPartsIndexes[RequiredNumber][PartNumber]=1;
		return 1;
	}
	return 0;
}
int GetBiggestLengthOfTwoEqualParts(int PartsCount, int *parts)
{
	int i,j,FirstPartNumber,SecondPartNumber,FuncRes,result,sum=0;
	char **FirstPart,***SecondPart;
	if(PartsCount<2)
		return 0;
	for(i=0; i<PartsCount; i++)
		sum=sum+parts[i];	
	sum=sum/2+1;
	FirstPart=(char**)calloc(sum,sizeof(char*));
	SecondPart=(char***)calloc(sum,sizeof(char**));
	//формируем список существующих отрезков
	for(i=0; i<PartsCount; i++)
		if(parts[i]<sum && FirstPart[parts[i]]==NULL)
		{
			FirstPart[parts[i]]=(char*)calloc(PartsCount,sizeof(char));
			FirstPart[parts[i]][i]=1;
		}
	for(i=parts[0],result=0; i<sum; i++)
		//последовательно пытаемся получить отрезок с помощью других
		for(FirstPartNumber=0; FirstPartNumber<PartsCount; FirstPartNumber++)
		{
			FuncRes=GetPart(PartsCount,parts,FirstPart,FirstPartNumber,i);
			if(FuncRes==1)
			{
				//если второй отрезок уже пытались получить другим способом, очищаем память
				if(SecondPart[i]!=NULL)
				{
					for(j=0; j<=i; j++)
						if(SecondPart[i][j]!=NULL)
							free(SecondPart[i][j]);
					free(SecondPart[i]);
				}
				//выделяем память и формируем новый список отрезков с учетом первого
				SecondPart[i]=(char**)calloc(i+1,sizeof(char*));
				for(j=0; parts[j]<=i && j<PartsCount; j++)
					if(FirstPart[i][j]==0 && SecondPart[i][parts[j]]==NULL)
					{
						SecondPart[i][parts[j]]=(char*)calloc(PartsCount,sizeof(char));
						for(SecondPartNumber=0; SecondPartNumber<PartsCount; SecondPartNumber++)
							SecondPart[i][parts[j]][SecondPartNumber]=FirstPart[i][SecondPartNumber];
						SecondPart[i][parts[j]][j]=1;
					}
				//тем же способом пытаемся получить второй отрезок
				for(j=parts[0]; j<=i; j++)
					if(SecondPart[i][j]==NULL)
						for(SecondPartNumber=0,FuncRes=0; SecondPartNumber<PartsCount && FuncRes==0; SecondPartNumber++)
							FuncRes=GetPart(PartsCount,parts,SecondPart[i],SecondPartNumber,j);
				if(SecondPart[i][i]!=NULL)
					result=i;
			}
		}
	for(i=parts[0]; i<sum; i++)
		if(FirstPart[i]!=NULL)
		{
			if(SecondPart[i]!=NULL)
			{
				for(j=parts[0]; j<=i; j++)
					if(SecondPart[i][j]!=NULL)
						free(SecondPart[i][j]);
				free(SecondPart[i]);
			}			
			free(FirstPart[i]);
		}
	free(FirstPart);
	free(SecondPart);
	return result;
}
int main(void)
{
	int FuncResult,i,RightFuncResult,StrPartsCount,PartsCount,*numbers=NULL;
	FILE *f=fopen("test.txt","r");
	FILE *f2=fopen("test cases output.txt","r");
	fscanf(f,"%d",&StrPartsCount);	
	while(StrPartsCount-->0)
	{
		fscanf(f,"%d",&PartsCount);
		fscanf(f2,"%d",&RightFuncResult);
		numbers=(int*)malloc(PartsCount*sizeof(int));
		for(i=0; i<PartsCount; i++)
		{
			fscanf(f,"%d ",&numbers[i]);
			printf("%d ",numbers[i]);
		}		
		sort(numbers,PartsCount);
		printf("\nsorted: ");
		for(i=0; i<PartsCount; i++)
			printf("%d ",numbers[i]);
		FuncResult=GetBiggestLengthOfTwoEqualParts(PartsCount,numbers);
		printf("\nBiggest length of two equal parts: %d; right FuncResult=%d;\n",FuncResult,RightFuncResult);
		free(numbers);
		printf("==============================================================\n");
	}
	fclose(f);
	fclose(f2);
	return 0;
}
