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
struct part *FindEqualParts(struct part **parts, int ps, int pc)
{
	int i,j,k,ep;
	struct part *max=(struct part*)malloc(sizeof(struct part));
	max->indexes=(char*)malloc(sizeof(char)*ps);
	max->part=0;
	for(i=0; i<ps; i++)
		max->indexes[i]='0';
	for(i=0; i<ps; i++)
		for(j=i+1; j<ps; j++)
		{			
			if(parts[i]->part==parts[j]->part)
			{
				ep=0;
				for(k=i; k<pc; k++)
					if(parts[i]->indexes[k]=='1' && parts[j]->indexes[k]=='1')
					{
						ep=1;
						break;
					}
				if(ep==0 && parts[i]->part>max->part)
				{
					max->part=parts[i]->part;
					max->indexes[j]='1';
					max->indexes[i]='1';
				}
			}
		}
	return max;
}
				
int GetBiggestLengthOfTwoEqualParts(int pc, int *a, char *FilePath)
{
	if(pc<2)
		return 0;
	struct part *maxpart=(struct part*)malloc(sizeof(struct part));
	struct part **parts=(struct part**)malloc(sizeof(struct part*)*pc);
	struct part **maxparts=(struct part**)malloc(sizeof(struct part*)*pc);
	maxpart->indexes=(char*)malloc(sizeof(char)*pc);
	int i,j,k,l,sum,max,maxind,t,end;
	struct part *ep=NULL;
	struct part *temp=NULL;
	for(i=0,sum=0; i<pc; i++)
	{
		maxpart->indexes[i]='1';
		sum+=a[i];
	}
	sum/=2;
	max=-1;
	maxind=0;
	for(i=0; i<pc; i++)
	{
		parts[i]=(struct part*)malloc(sizeof(struct part));
		maxparts[i]=(struct part*)malloc(sizeof(struct part));
		parts[i]->indexes=(char*)malloc(sizeof(char)*pc);
		maxparts[i]->indexes=(char*)malloc(sizeof(char)*pc);
		maxparts[i]->part=0;		
		for(j=0; j<pc; j++)
			parts[i]->indexes[j]='0';
		if(a[i]<=sum)
		{
			parts[i]->part=a[i];
			parts[i]->indexes[i]='1';
		}
		else
			parts[i]->part=0;
		if(a[i]>max)
		{
			max=a[i];
			maxind=i;
		}
	}
	if(max>-1)
	{
		maxparts[0]->part=max;
		maxparts[0]->indexes[maxind]='1';
	}
	ep=FindEqualParts(parts,pc,pc);
	for(i=1,end=1; i<pc && end!=0; i++)
	{
		end=0;
		for(j=0; j<pc; j++)
		{
			for(max=0,maxind=-1,k=0; k<pc; k++)
				if(parts[j]->indexes[k]=='0' && parts[j]->part+a[k]<=sum && parts[j]->part+a[k]>max)
				{
					end=1;
					max=parts[j]->part+a[k];
					maxind=k;
				}
			if(maxind>-1)
			{
				parts[j]->part=max;
				parts[j]->indexes[maxind]='1';
			}
			if(parts[j]->part>maxparts[i]->part)
			{
				maxparts[i]->part=parts[j]->part;
				for(k=0; k<pc; k++)
					maxparts[i]->indexes[k]=parts[j]->indexes[k];
			}
			temp=FindEqualParts(parts,pc,pc);
			if(temp->part>ep->part)
			{
				ep->part=temp->part;
				for(j=0; j<pc; j++)
					ep->indexes[k]=temp->indexes[k];
			}
			temp=FindEqualParts(maxparts,pc,pc);
			if(temp->part>ep->part)
			{
				ep->part=temp->part;
				for(j=0; j<pc; j++)
					ep->indexes[k]=temp->indexes[k];
			}
		}
		
	}
	temp=FindEqualParts(parts,pc,pc);
	if(temp->part>ep->part)
	{
		ep->part=temp->part;
		for(j=0; j<pc; j++)
			ep->indexes[k]=temp->indexes[k];
	}
	temp=FindEqualParts(maxparts,pc,pc);
	if(temp->part>ep->part)
	{
		ep->part=temp->part;
		for(j=0; j<pc; j++)
			ep->indexes[k]=temp->indexes[k];
	}
	for(i=0; i<pc; i++)
	{
	/*	printf("\n%d.  %d: ",i,parts[i]->part);
		for(j=0; j<pc; j++)
			printf("%c ",parts[i]->indexes[j]);*/
		free(parts[i]->indexes);
		free(parts[i]);
		free(maxparts[i]->indexes);
		free(maxparts[i]);
	}
	free(parts);
	free(maxparts);
	return ep->part;			
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
		//sort(numbers,PartsCount);
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