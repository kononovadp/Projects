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
char FindPart(int *p, char *ind, int pc, int rn)
{
	int i;
	//жадный алгоритм
	i=pc-1;
	while(i>=0 && rn>0)
	{
		while(i>-1 && p[i]>rn)
			i--;
		if(i>-1)
		{
			rn-=p[i];
			ind[i]='1';
		}
		i--;
	}
	if(rn==0)
		return 1;
	else
		return 0;
}
char FindTwoEqualParts(int *p, int pc, int rn)
{
	//npc - NewPartsCount; ns - NewSum; np - NewParts
	int i,npc,ns,res;
	int *np=(int*)malloc(sizeof(int)*pc);
	char *ind=(char*)calloc(sizeof(char),pc);
	res=FindPart(p,ind,pc,rn);
	if(res==1)
	{	//формируем новый список отрезок, исключающий уже использованные
		for(i=0,npc=0; i<pc; i++)
			if(ind[i]==0)
			{			
				np[npc]=p[i];
				npc++;
			}
		res=FindPart(np,ind,npc,rn);
		if(res==0)
		{
			//жадный алгоритм иногда дает не правильное значение,
			//поэтому пытаемся получить его другим способом
			for(i=0,ns=0; i<npc && ns<rn; i++)
				ns+=np[i];
			if(ns!=rn)
			{
				ns-=rn;
				for(i=0; i<npc && np[i]<ns; i++);
					if(ns-np[i]==0)
						res=1;
					else
						res=0;
			}
		}
	}
	free(ind);
	free(np);
	return res;
}
int GetBiggestLengthOfTwoEqualParts(int pc, int *p)
{
	int res,i,sum=0;
	if(pc<2)
		return 0;
	for(i=0; i<pc; i++)
		sum+=p[i];
	sum/=2;
	res=0;
	while(res==0 && sum>-1)
	{				
		res=FindTwoEqualParts(p,pc,sum);
		sum--;
	}
	return sum+1;
}
int main(void)
{	
	int result,i,Rightresult,StrPartsCount,pc,*numbers=NULL;
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
		fscanf(f,"%d",&pc);
		fscanf(f2,"%d",&Rightresult);
		numbers=(int*)malloc(pc*sizeof(int));
		for(i=0; i<pc; i++)
		{
			fscanf(f,"%d ",&numbers[i]);
			printf("%d ",numbers[i]);
		}
		printf("\nsorted: ");
		sort(numbers,pc);
		for(i=0; i<pc; i++)
			printf("%d ",numbers[i]);
		result=GetBiggestLengthOfTwoEqualParts(pc,numbers);
		printf("\nBiggest length of two equal p: %d; right result=%d;\n",result,Rightresult);
		free(numbers);
		//free(fn);
		//free(FilePath);
		printf("==============================================================\n");
	}
	fclose(f);
	fclose(f2);
	return 0;
}