#include <stdio.h>
#include <stdlib.h>
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
			if(a[i]<a[i+1])
			{
				sorted=0;
				t=a[i];
				a[i]=a[i+1];
				a[i+1]=t;
			}
	}
}
int GetBiggestLengthOfTwoEqualParts(int PartsCount, int *a, char *FilePath)
{
	if(PartsCount<2)
		return 0;
	int max1,max2,max3,i,j,k,m;
	int sum=0;
	int rn=0;
	int in=0;
	int *res=(int*)malloc(sizeof(int)*PartsCount*PartsCount*PartsCount);
	int **ind=(int**)malloc(sizeof(int*)*PartsCount*PartsCount*PartsCount);
	FILE *f = fopen(FilePath,"w");
	for(i=0; i<PartsCount*PartsCount*PartsCount; i++)
	{
		res[i]=0;
		ind[i]=(int*)malloc(sizeof(int)*PartsCount);
		for(j=0; j<PartsCount; j++)
			ind[i][j]=0;			
	}
	for(i=0; i<PartsCount; i++)
		sum+=a[i];
	sum/=2;
	for(i=0; i<PartsCount; i++)
	{
		if(a[i]<=sum)
		{
			res[rn]=a[i];
			rn++;
			ind[in][i]=1;
			in++;
		}
		else
			continue;
		j=i+1;		
		while(res[rn-1]+a[j]>sum && j<PartsCount)
			j++;
		k=j;
		while(j<PartsCount/* && res[rn-1]<sum*/)
		{
			if(res[rn-1]+a[j]<=sum /*&& res[rn-1]+a[j]!=res[rn-1]*/)
			{
				res[rn]=res[rn-1]+a[j];
				rn++;
				for(m=0; m<PartsCount; m++)
					ind[in][m]=ind[in-1][m];
				ind[in][j]=1;
				in++;
			}
			j++;
		}
		while(k<PartsCount/* && res[rn-1]<sum*/)
		{
			if(a[i]+a[k]<=sum /*&& a[i]+a[k]!=res[rn-1]*/)
			{
				res[rn]=a[i]+a[k];
				rn++;
				ind[in][i]=1;
				ind[in][k]=1;
				in++;
			}
			k++;
		}
	}
	for(i=0; i<PartsCount; i++)
		fprintf(f,"%d ",a[i]);	
	fprintf(f,"\nsum = %d\n",sum);
	/*max1=0;
	for(i=0; i<rn; i++)
		for(j=i+1; j<rn; j++)
			if(res[j]==res[i] && res[i]>max1)
				max1=res[i];*/
	max2=0;
	for(i=0; i<rn; i++)
	{
		for(j=i+1; j<rn; j++)
		{
			if(res[j]==res[i])
			{
				sum=0;
				for(m=0; m<PartsCount && sum!=1; m++)
					if(ind[i][m]==ind[j][m] && (ind[i][m]!=0 && ind[j][m]!=0))
						sum=1;
				if(sum==0 && res[i]>max2)
					max2=res[i];
			}
		}
	}
	for(i=0; i<rn; i++)
	{
		fprintf(f,"\n%d. ",i);
		fprintf(f,"%d ",res[i]);
		fprintf(f,":");
		for(j=0; j<PartsCount; j++)
			fprintf(f,"%d ",ind[i][j]);
	}
	fprintf(f,"\nresult = %d",k);
	free(res);
	for(i=0; i<in; i++)
		free(ind[i]);
	free(ind);
	fclose(f);
	return max2;
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