#include <stdio.h>
#include <malloc.h>
void invert(int *tower)
{
	int t=tower[2];
	tower[2]=tower[1];
	tower[1]=tower[0];
	tower[0]=t;
}
void SortTower(int tc,int **tow)
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
int **CheckTower(int tc,int **mem,int freepos,int *add,int ***pr,int rn)
{
	int i,j,**t,res=1;
	//if(pr[rn]!=NULL)
	//	return NULL;
	t=(int**)calloc(tc,sizeof(int*));
	for(i=0; i<tc; i++)
	{
		t[i]=(int*)calloc(3,sizeof(int));
			for(j=0; j<3; j++)
				t[i][j]=mem[i][j];
	}
	for(i=0; i<3; i++)
		t[freepos][i]=add[i];
	SortTower(tc,t);
	for(i=0; i<tc-1 && res==1; i++)
		if(t[i][0]>t[i+1][0] || t[i][1]>t[i+1][1])
			res=0;
	if(res==1)
	{
		if(pr[rn]!=NULL)
		{
			for(i=0; i<tc; i++)
				free(pr[rn][i]);
			free(pr[rn]);
			pr[rn]=NULL;
		}
		for(i=0; i<tc; i++)
			for(j=0; j<3; j++)
				t[i][j]=mem[i][j];
		for(i=0; i<3; i++)
			t[freepos][i]=add[i];
		return t;
	}		
	for(i=0; i<tc; i++)
		free(t[i]);
	free(t);
	return NULL;
}
char build(int tc,int ***pr,int **tow,int min,int rn,FILE *f)
{
	int i,j,k,l,x,y,rg,top,pos,mr,**res,min2=rn;
	if(pr[rn]!=NULL)
		return 0;
	for(i=0; i<tc; i++)
		for(j=0; j<3; j++,invert(tow[i]))
		{
			if(tow[i][2]==rn)
			{
				pr[rn]=(int**)calloc(tc,sizeof(int*));
				for(x=0; x<tc; x++)
					pr[rn][x]=(int*)calloc(3,sizeof(int));
				for(x=0; x<3; x++)
					pr[rn][i][x]=tow[i][x];
				return 1;
			}
			mr=rn-tow[i][2];
			if(mr>=min && pr[mr]!=NULL && pr[mr][i][0]==0)
			{
				if(pr[rn]==NULL || (pr[rn]!=NULL && mr<min2))
				{
					res=CheckTower(tc,pr[mr],i,tow[i],pr,rn);
					if(res!=NULL && mr<min2)
					{
						pr[rn]=res;
						min2=mr;
					}
				}
			}
		}
	if(min2<rn)
		return 1;
	return 0;
}
int GetRes(int tc,int **tow)
{
	int i,j,k,t,l,sn,res,min,max,***pr,sum=1;
	FILE *f=fopen("RESULTS__.txt","w");
	for(i=0,min=tow[0][0]; i<tc; i++)
	{
		for(j=0,max=tow[0][0]; j<3; j++)
		{
			if(tow[i][j]>max)
				max=tow[i][j];
			if(tow[i][j]<min)
				min=tow[i][j];
		}
		sum+=max;
	}
	pr=(int***)calloc(sum,sizeof(int**));
	for(i=min; i<sum; i++)
	{
		res=build(tc,pr,tow,min,i,f);
		if(res==1)
			max=i;
	}
	/*if(pr[max]!=NULL)
	{
		SortTower(tc,pr[max]);
		for(i=0,putchar('\n'); i<tc; i++,putchar('\n'))
			for(j=0; j<3; j++)
				printf("%5d",pr[max][i][j]);
	}*/
	for(i=0; i<sum; i++)
		if(pr[i]!=NULL)
		{
			for(j=0; j<tc; j++)
				free(pr[i][j]);
			free(pr[i]);
		}
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
		tower=(int**)calloc(BouldersCount,sizeof(int*));
		for(j=0; j<BouldersCount; j++)
		{
			tower[j]=(int*)calloc(3,sizeof(int));
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