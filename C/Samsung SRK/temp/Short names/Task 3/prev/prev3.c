#include <stdio.h>
#include <malloc.h>
void invert(long long int *tower)
{
	int t=tower[2];
	tower[2]=tower[1];
	tower[1]=tower[0];
	tower[0]=t;
}
//cb-CurrentBoulder; bb-BusyBoulders; cr-CurrentRes
long long int build(int tc,long long int **tow,int cb,long long int cr,char *bb,FILE *f,long long int pw,long long int pl,char **pr,long long int pm)
{
	char found=1;
	if(pr[cr]!=NULL)
	{
		for(int i=0; i<tc && found==1; i++)
			if(pr[cr][i]!=bb[i])
				found=0;
		if(found==1)
			return cr;
	}
	long long int i,j,k,res,max=cr;
	bb[cb]=1;
	for(i=0; i<3; i++)
	{
		if((tow[cb][0]<=pw && tow[cb][1]<=pl) || (tow[cb][0]<=pl && tow[cb][1]<=pw))
		{
			for(j=0; j<tc; j++)
				if(bb[j]==0)
					for(k=0; k<3; k++)
					{
						if((tow[j][0]<=tow[cb][0] && tow[j][1]<=tow[cb][1]) || (tow[j][0]<=tow[cb][1] && tow[j][1]<=tow[cb][0]))
						{
							res=build(tc,tow,j,cr+tow[j][2],bb,f,tow[cb][0],tow[cb][1],pr,max);
							if(res>max)
							{
								max=res;
								if(pr[max]==NULL)
									pr[max]=(char*)calloc(tc,sizeof(char));
								for(int k=0; k<tc; k++)
									pr[max][k]=bb[k];
							}
						}
						invert(tow[j]);
					}
			if(tow[cb][2]>max)
			{
				max=tow[cb][2];
				if(pr[max]==NULL)
					pr[max]=(char*)calloc(tc,sizeof(char));
				for(int k=0; k<tc; k++)
					pr[max][k]=bb[k];
			}
		}
		cr=cr-tow[cb][2];
		invert(tow[cb]);
		cr=cr+tow[cb][2];
	}
	if(tow[cb][2]>max)
		max=tow[cb][2];
	if(pr[max]==NULL)
		pr[max]=(char*)calloc(tc,sizeof(char));
	for(int k=0; k<tc; k++)
		pr[max][k]=bb[k];
	fprintf(f,"\ncb=%d; cr=%lld; max=%lld: ",cb,cr,max);
	for(i=0; i<tc; i++)
		fprintf(f,"%d ",bb[i]);
	bb[cb]=0;
	return max;
}
long long int GetRes(int tc,long long int **tow)
{
	long long int i,j,res,max=tow[0][2];
	FILE *f=fopen("RESULTS__.txt","w");
	char *bb=(char*)calloc(tc,sizeof(char));
	char **pr=(char**)calloc(tc*10000,sizeof(char*));
	for(i=0,res=tow[0][2]; i<tc; i++)
	{
		res=build(tc,tow,i,tow[i][2],bb,f,10001,10001,pr,res);
		if(res>max)
			max=res;
		//printf("\ni=%lld; res=%lld; max=%lld",i,res,max);
	}
	free(bb);
	free(pr);
	fclose(f);
	return max;
}
int main(void)
{
	int i,j,k,reqres,CorrectResult,TowersCount,BouldersCount;
	long long int **tower;
	long long int myres;
	FILE *tf=fopen("tests.txt","r");
	FILE *rf=fopen("correct-results.txt","r");
	fscanf(tf,"%d",&TowersCount);
	for(i=0; i<TowersCount; i++)
	{
		fscanf(tf,"%d",&BouldersCount);
		printf("tower %d; BouldersCount = %d\n",i+1,BouldersCount);
		tower=(long long int**)malloc(sizeof(long long int *)*BouldersCount);
		for(j=0; j<BouldersCount; j++)
		{
			tower[j]=(long long int*)malloc(sizeof(long long int)*3);
			for(k=0; k<3; k++)
			{
				fscanf(tf,"%lld",&tower[j][k]);
				printf("%5lld",tower[j][k]);
			}
			putchar('|');
		}
		myres=GetRes(BouldersCount,tower);
		fscanf(rf,"%d",&reqres);
		printf("\nMY RESULT = %lld;		 REQUIRED RESULT = %d \n------------------------------------------------\n",myres,reqres);
		for(j=0; j<BouldersCount; j++)
			free(tower[j]);
		free(tower);
	}
	fclose(tf);
	fclose(rf);
	return 0;
}