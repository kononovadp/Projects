#include <stdio.h>
#include <malloc.h>
int power(int n,int p)
{
	int r=1;
	if(p>0)
		r=n*power(n,p-1);
	return r;
}
void invert(int *tower)
{
	int t=tower[2];
	tower[2]=tower[1];
	tower[1]=tower[0];
	tower[0]=t;
}
void sort(int tc,int **tow)
{
	char rr=0;
	int i,j;
	int *t,tn;
	while(rr!=1)
	{
		rr=1;
		for(i=0; i<tc; i++)
			for(j=i+1; j<tc; j++)
			{
				if((tow[i][0]>tow[j][0] && tow[i][1]>tow[j][1]) || (tow[i][0]>tow[j][1] && tow[i][1]>tow[j][0]))
				{
					rr=0;
					t=tow[i];
					tow[i]=tow[j];
					tow[j]=t;
				}
				if(tow[j][0]<tow[i][0] || tow[j][1]<tow[i][1])
				{
					tn=tow[j][0];
					tow[j][0]=tow[j][1];
					tow[j][1]=tn;
				}
			}
	}
}
void AddTowerToCache(int tc,int ***pr,int **tow,int n,char *bb)
{
	int x,y,z;
	if(pr[n]==NULL)
		pr[n]=(int**)calloc(tc,sizeof(int*));
	for(y=0; y<tc; y++)
	{								
		if(pr[n][y]==NULL)
			pr[n][y]=(int*)calloc(3,sizeof(int));
		if(bb[y]==1)
			for(z=0; z<3; z++)
				pr[n][y][z]=tow[y][z];
	}
}
int build(int tc,int **tow,int cb,int cr,char *bb,int pw,int pl,int ***pr,FILE *f)
{
	int i,j,k,t,y,z,res,max=cr;
	fprintf(f,"\ncb=%d; cr=%d; max=%d: ",cb,cr,max);
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
							bb[j]=1;
							AddTowerToCache(tc,pr,tow,cr+tow[j][2],bb);
							bb[j]=0;
							res=build(tc,tow,j,cr+tow[j][2],bb,tow[cb][0],tow[cb][1],pr,f);
							if(res>max)
								max=res;
						}
						invert(tow[j]);
					}
			if(tow[cb][2]>max)
			{
				max=tow[cb][2];
				AddTowerToCache(tc,pr,tow,max,bb);
			}
		}
		cr=cr-tow[cb][2];
		invert(tow[cb]);
		cr=cr+tow[cb][2];
	}
	if(tow[cb][2]>max)
		max=tow[cb][2];
	bb[cb]=0;
	return max;
}
int GetRes(int tc,int **tow)
{
	int i,j,y,z,res,max=tow[0][2];
	int size=power(tc*2,tc);
	FILE *f=fopen("RESULTS__.txt","w");
	char *bb=(char*)calloc(tc,sizeof(char));
	int ***pr=(int***)calloc(tc*10000,sizeof(int**));
	for(i=0,res=tow[0][2]; i<tc; i++)
	{
		res=build(tc,tow,i,tow[i][2],bb,10001,10001,pr,f);
		if(res>max)
			max=res;
	}
	sort(tc,pr[max]);
	for(y=0; y<tc; y++)
	{
		putchar('\n');
		for(z=0; z<3; z++)
			printf("%5d ",pr[max][y][z]);
	}
	for(i=0,res=tc*10000; i<res; i++)
		if(pr[i]!=NULL)
		{
			for(j=0; j<tc; j++)
				free(pr[i][j]);
			free(pr[i]);
		}	
	free(bb);
	free(pr);
	fclose(f);
	return max;
}
int main(void)
{
	int i,j,k,reqres,CorrectResult,TowersCount,BouldersCount;
	int **tower;
	int myres;
	FILE *tf=fopen("tests.txt","r");
	FILE *rf=fopen("correct-results.txt","r");
	fscanf(tf,"%d",&TowersCount);
	for(i=0; i<TowersCount; i++)
	{
		fscanf(tf,"%d",&BouldersCount);
		printf("tower %d; BouldersCount = %d\n",i+1,BouldersCount);
		tower=(int**)malloc(sizeof(int *)*BouldersCount);
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