#include <stdio.h>
#include <malloc.h>
struct part
{
	int part;
	char *indexes;
};
int GetDigitsCount(int n)
{
	int i=0;
	while(n>0)
	{
		n/=10;
		i++;
	}
	return n;
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
char FindEqualParts(int *a, int pc, int num, FILE *f)
{
	char *ind=(char*)malloc(sizeof(char)*pc);
	int res,i,j,k,t,sum=0;
	char f1=0;
	char f2=0;
	for(i=0; i<pc; i++)
		ind[i]='0';
	for(i=0; sum<num; i++)
	{
		sum+=a[i];
		ind[i]='1';
	}
	sum-=num;
	while(sum>0)
	{
		f2=0;
		for(j=0; j<i && f2!=1; j++)
			if(a[j]==sum)
			{
				sum-=a[j];
				ind[j]='0';
				f2=1;
			}
		if(f2==0)
		{
			while(a[j]>sum && j>-1)
				j--;
			if(sum>0)
			{
				sum-=a[j];
				ind[j]='0';
			}
		}
	}
	fprintf(f,"\n---------------------------------------\n");
	for(i=0,sum=0; i<pc; i++)
	{
		fprintf(f,"%d ",a[i]);
		if(ind[i]=='1')
			sum+=a[i];
	}
	fprintf(f,"\nsum=%d; part %d found: ",sum,num);
	for(i=0; i<pc; i++)
		fprintf(f,"%c ",ind[i]);
	if(sum==0)
		f1=1;
	else
		return 0;
	
	
	for(sum=0,i=pc-1; i>-1 && sum!=num; i--)
	{
		if(ind[i]=='0')
			sum+=a[i];
		if(sum>num)
			sum=0;
	}
	if(sum==num)
		return 1;
	else
		return 0;
}
int GetBiggestLengthOfTwoEqualParts(int pc, int *a, char *FilePath)
{
	int t,i,sum=0;
	FILE *f=fopen(FilePath,"w");
	if(pc<2)
		return 0;
	for(i=0; i<pc; i++)
		sum+=a[i];
	sum/=2;
	t=0;
	sum+=1;
	while(t==0 && sum>0)
	{
		sum--;
		t=FindEqualParts(a,pc,sum,f);
		//printf("\npart %d found: %d",sum,t);		
	}
	fclose(f);
	return sum;
}
int main(void)
{
	FILE *f=fopen("test.txt","r");
	int result;
	int i,temp,StrPartsCount,PartsCount,*numbers=NULL;
	int FileNumber=1;
	char *FilePath,*FileName=NULL;
	_mkdir("logs");
	fscanf(f,"%d",&StrPartsCount);	
	while(StrPartsCount-->0)
	{	
		FileName=(char*)malloc(4+(GetDigitsCount(FileNumber)*sizeof(char)));
		_itoa(FileNumber,FileName,10);
		strcat(FileName,".txt");
		FilePath=(char*)malloc(6+strlen(FileName));
		strcpy(FilePath,"logs\\");
		strcat(FilePath,FileName);
		printf("%d. |",FileNumber);
		FileNumber++;
		fscanf(f,"%d",&PartsCount);
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
		result=GetBiggestLengthOfTwoEqualParts(PartsCount,numbers,FilePath); 
		printf("\nBiggest length of two equal parts: %d; indexes:\n",result);
		free(numbers);		
		printf("======================================================\n");		
	}
	fclose(f);
	return 0;
}