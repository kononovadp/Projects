#include <stdio.h>
#include <malloc.h>
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
char FindPart(int *parts, char *indexes, int PartsCount, int RequiredNumber)
{
	int i;
	//жадный алгоритм
	i=PartsCount-1;
	while(i>=0 && RequiredNumber>0)
	{
		while(i>-1 && parts[i]>RequiredNumber)
			i--;
		if(i>-1)
		{
			RequiredNumber-=parts[i];
			indexes[i]='1';
		}
		i--;
	}
	if(RequiredNumber==0)
		return 1;
	else
		return 0;
}
char FindTwoEqualParts(int *parts, int PartsCount, int RequiredNumber)
{
	int i,NewPartsCount,NewSum,result;
	int *NewParts=(int*)malloc(sizeof(int)*PartsCount);
	char *indexes=(char*)calloc(sizeof(char),PartsCount);
	result=FindPart(parts,indexes,PartsCount,RequiredNumber);
	if(result==1)
	{	//формируем новый список отрезок, исключающий уже использованные
		for(i=0,NewPartsCount=0; i<PartsCount; i++)
			if(indexes[i]==0)
			{			
				NewParts[NewPartsCount]=parts[i];
				NewPartsCount++;
			}
		result=FindPart(NewParts,indexes,NewPartsCount,RequiredNumber);
		if(result==0)
		{
			//жадный алгоритм иногда дает не правильное значение,
			//поэтому пытаемся получить его другим способом
			for(i=0,NewSum=0; i<NewPartsCount && NewSum<RequiredNumber; i++)
				NewSum+=NewParts[i];
			if(NewSum!=RequiredNumber)
			{
				NewSum-=RequiredNumber;
				for(i=0; i<NewPartsCount && NewParts[i]<NewSum; i++);
					if(NewSum-NewParts[i]==0)
						result=1;
					else
						result=0;
			}
		}
	}
	free(indexes);
	free(NewParts);
	return result;
}
int GetBiggestLengthOfTwoEqualParts(int PartsCount, int *parts)
{
	int result,i,sum=0;
	if(PartsCount<2)
		return 0;
	for(i=0; i<PartsCount; i++)
		sum+=parts[i];
	sum/=2;
	result=0;
	while(result==0 && sum>-1)
	{				
		result=FindTwoEqualParts(parts,PartsCount,sum);
		sum--;
	}
	return sum+1;
}
int main(void)
{	
	int result,i,Rightresult,StrPartsCount,PartsCount,*numbers=NULL;
	FILE *f=fopen("test.txt","r");
	FILE *f2=fopen("test cases output.txt","r");
	/*char *FilePath,*fn=NULL;
	int FileNumber=1;
	_mkdir("logs");*/
	fscanf(f,"%d",&StrPartsCount);	
	while(StrPartsCount-->0)
	{
		/*fn=(char*)malloc(4+(GetDigitsCount(FileNumber)*sizeof(char)));
		_itoa(FileNumber,fn,10);
		strcat(fn,".txt");
		FilePath=(char*)malloc(6+strlen(fn));
		strcpy(FilePath,"logs\\");
		strcat(FilePath,fn);
		printf("%d. |",FileNumber);
		FileNumber++;*/
		fscanf(f,"%d",&PartsCount);
		fscanf(f2,"%d",&Rightresult);
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
		result=GetBiggestLengthOfTwoEqualParts(PartsCount,numbers);
		printf("\nBiggest length of two equal parts: %d; right result=%d;\n",result,Rightresult);
		free(numbers);
		//free(fn);
		//free(FilePath);
		printf("==============================================================\n");
	}
	fclose(f);
	fclose(f2);
	return 0;
}