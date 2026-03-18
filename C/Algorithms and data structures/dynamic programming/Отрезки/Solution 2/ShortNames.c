#include <stdio.h>
#include <malloc.h>
void sort(int *p,int pc)
{
	char sorted=0;
	int i,t;
	while(sorted!=1)
	{
		sorted=1;
		for(i=0; i<pc-1; i++)
			if(p[i]>p[i+1])
			{
				sorted=0;
				t=p[i];
				p[i]=p[i+1];
				p[i+1]=t;
			}
	}
}
//ф-я проверяет, можно ли получить отрезок путем отнимания его от существующего свободного
char GetPart(int pc,int *p,char **bp,int pn,int rn)
{//bp - BusyParts; pn - PartNumber; rn - RequiredNumber
	int i,mn;
	mn=rn-p[pn];
	if(mn>=p[0] && bp[mn]!=NULL && bp[mn][pn]==0)
	{
		if(bp[rn]==NULL)
			bp[rn]=(char*)calloc(pc,sizeof(char));
		for(i=0; i<pc; i++)
			bp[rn][i]=bp[mn][i];
		bp[rn][pn]=1;
		return 1;
	}
	return 0;
}
int GetBiggestLengthOfTwoEqualParts(int pc, int *p)
{
	//fpn - FirstPartNumber; spn - SecondPartNumber
	int i,j,fpn,spn,FuncRes,res,sum=0;
	char **fp,***sp; //fp - FirstPart; sp - SecondPart
	if(pc<2)
		return 0;
	for(i=0; i<pc; i++)
		sum=sum+p[i];	
	sum=sum/2+1;
	fp=(char**)calloc(sum,sizeof(char*));
	sp=(char***)calloc(sum,sizeof(char**));
	//формируем список существующих отрезков
	for(i=0; i<pc; i++)
		if(p[i]<sum && fp[p[i]]==NULL)
		{
			fp[p[i]]=(char*)calloc(pc,sizeof(char));
			fp[p[i]][i]=1;
		}
	for(i=p[0],res=0; i<sum; i++)
		//последовательно пытаемся получить отрезок с помощью других
		for(fpn=0; fpn<pc; fpn++)
		{
			FuncRes=GetPart(pc,p,fp,fpn,i);
			if(FuncRes==1)
			{
				//если второй отрезок уже пытались получить другим способом, очищаем память
				if(sp[i]!=NULL)
				{
					for(j=0; j<=i; j++)
						if(sp[i][j]!=NULL)
							free(sp[i][j]);
					free(sp[i]);
				}
				//выделяем память и формируем новый список отрезков с учетом первого
				sp[i]=(char**)calloc(i+1,sizeof(char*));
				for(j=0; p[j]<=i && j<pc; j++)
					if(fp[i][j]==0 && sp[i][p[j]]==NULL)
					{
						sp[i][p[j]]=(char*)calloc(pc,sizeof(char));
						for(spn=0; spn<pc; spn++)
							sp[i][p[j]][spn]=fp[i][spn];
						sp[i][p[j]][j]=1;
					}
				//тем же способом пытаемся получить второй отрезок
				for(j=p[0]; j<=i; j++)
					if(sp[i][j]==NULL)
						for(spn=0,FuncRes=0; spn<pc && FuncRes==0; spn++)
							FuncRes=GetPart(pc,p,sp[i],spn,j);
				if(sp[i][i]!=NULL)
					res=i;
			}
		}
	for(i=p[0]; i<sum; i++)
		if(fp[i]!=NULL)
		{
			if(sp[i]!=NULL)
			{
				for(j=p[0]; j<=i; j++)
					if(sp[i][j]!=NULL)
						free(sp[i][j]);
				free(sp[i]);
			}			
			free(fp[i]);
		}
	free(fp);
	free(sp);
	return res;
}
int main(void)
{
	int FuncResult,i,RightFuncResult,StrPartsCount,pc,*numbers=NULL;
	FILE *f=fopen("test.txt","r");
	FILE *f2=fopen("test cases output.txt","r");
	fscanf(f,"%d",&StrPartsCount);	
	while(StrPartsCount-->0)
	{
		fscanf(f,"%d",&pc);
		fscanf(f2,"%d",&RightFuncResult);
		numbers=(int*)malloc(pc*sizeof(int));
		for(i=0; i<pc; i++)
		{
			fscanf(f,"%d ",&numbers[i]);
			printf("%d ",numbers[i]);
		}		
		sort(numbers,pc);
		printf("\nsorted: ");
		for(i=0; i<pc; i++)
			printf("%d ",numbers[i]);
		FuncResult=GetBiggestLengthOfTwoEqualParts(pc,numbers);
		printf("\nBiggest length of two equal p: %d; right FuncResult=%d;\n",FuncResult,RightFuncResult);
		free(numbers);
		printf("==============================================================\n");
	}
	fclose(f);
	fclose(f2);
	return 0;
}
