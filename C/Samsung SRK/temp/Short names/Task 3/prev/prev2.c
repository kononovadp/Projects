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
long long int build(int tc,long long int **tow,int cb,long long int cr,char *bb,FILE *f, long long int pw,long long int pl)
{
	long long int i,j,k,l,t,rf,res,prl,prw,max=cr;
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
							res=build(tc,tow,j,cr+tow[j][2],bb,f,tow[cb][0],tow[cb][1]);
							if(res>max)
								max=res;						
						}
						invert(tow[j]);
					}
			if(tow[cb][2]>max)
				max=tow[cb][2];
		}		
		cr=cr-tow[cb][2];
		invert(tow[cb]);
		cr=cr+tow[cb][2];		
	}
	bb[cb]=0;
	if(tow[cb][2]>max)
		max=tow[cb][2];
	return max;
}
long long int GetRes(int tc,long long int **tow)
{
	int i,j;
	long long int res,max=tow[0][2];
	FILE *f=fopen("RESULTS__.txt","w");
	char *bb=(char*)calloc(tc,sizeof(char));
	long long int **pr=(long long int**)calloc(tc*3,sizeof(long long int *));
	long long int prc=0;
	for(i=0; i<tc*3; i++)
		pr[i]=(long long int*)calloc(3,sizeof(long long int));	
	for(i=0; i<tc; i++)
	{
		res=build(tc,tow,i,tow[i][2],bb,f,10001,10001);
		if(res>max)
			max=res;
	}
	free(bb);
	fclose(f);
	return max;
	//res=build(tc,tow,0,tow[0][2],bb);
	//return res;
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