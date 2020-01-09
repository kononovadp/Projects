#include <stdio.h>
#include <malloc.h>
void invert(int *tower)
{
	int t=tower[2];
	tower[2]=tower[1];
	tower[1]=tower[0];
	tower[0]=t;
}
//cb-CurrentBoulder; bb-BusyBoulders; cr-CurrentRes
int build(int tc,int **tow,int cb,long long int cr,char *bb)
{
	int i,j,k,l,t;
	long long res,max=cr;
	bb[cb]=1;
	for(i=0; i<3; i++)
	{
		if(tow[cb][2]>max)
			max=tow[cb][2];
		for(j=0; j<tc; j++)
			if(bb[j]==0)
				for(k=0; k<3; k++)
				{
					if((tow[j][0]<=tow[cb][0] && tow[j][1]<=tow[cb][1]) || (tow[j][0]<=tow[cb][1] && tow[j][1]<=tow[cb][0]))
					{						
						res=build(tc,tow,j,cr+tow[j][2],bb);
						if(res>max)
						{
							/*fprintf(f,"\ncb=%d: ",cb);
						for(l=0; l<3; l++)
							fprintf(f,"%lld ",tow[cb][l]);
						fprintf(f,"j=%lld: ",j);
						for(l=0; l<3; l++)
							fprintf(f,"%lld ",tow[j][l]);
						fprintf(f,"; %lld+%lld=%lld; res=%lld",cr,tow[j][2],cr+tow[j][2],res);*/
							max=res;
						}
					}
					invert(tow[j]);
				}
		//fprintf(f,"\ncurh=%lld; tow[cb][2]=%lld",cr,tow[cb][2]);
		cr=cr-tow[cb][2];
		invert(tow[cb]);
		cr=cr+tow[cb][2];
		if(tow[cb][2]>max)
			max=tow[cb][2];
	}
	bb[cb]=0;
	return max;
}
int GetRes(int tc, int **tow)
{
	int i,j,res,max=tow[0][2];
	char *bb=(char*)calloc(tc,sizeof(char));
	for(i=0; i<tc; i++)
	{
		res=build(tc,tow,i,tow[i][2],bb);
		if(res>max)
			max=res;
		for(j=0; j<tc; j++)
			bb[j]=0;
	}
	free(bb);
	return max;
	//res=build(tc,tow,0,tow[0][2],bb);
	//return res;
}
int main(void)
{
	int i,j,k,myres,reqres,CorrectResult,TowersCount,BouldersCount,**tower;
	FILE *tf=fopen("tests.txt","r");
	FILE *rf=fopen("correct-results.txt","r");
	fscanf(tf,"%d",&TowersCount);
	for(i=0; i<TowersCount; i++)
	{
		fscanf(tf,"%d",&BouldersCount);
		printf("tower %d; BouldersCount = %d\n",i+1,BouldersCount);
		tower=(int**)malloc(sizeof(int*)*BouldersCount);
		for(j=0; j<BouldersCount; j++)
		{
			tower[j]=(int*)malloc(sizeof(int)*3);
			for(k=0; k<3; k++)
			{
				fscanf(tf,"%d",&tower[j][k]);
				printf("%5d",tower[j][k]);
			}
			putchar('|');
		}
		myres=GetRes(BouldersCount,tower);
		fscanf(rf,"%d",&reqres);
		printf("\nMY RESULT = %d;		 REQUIRED RESULT = %d \n------------------------------------------------\n",myres,reqres);
		for(j=0; j<BouldersCount; j++)
			free(tower[j]);
		free(tower);
	}
	fclose(tf);
	fclose(rf);
	return 0;
}