#include <stdio.h>
#include <malloc.h>
#include <time.h>
//переворачивает камень
void invert(int *b)
{
	int t=b[2];
	b[2]=b[1];
	b[1]=b[0];
	b[0]=t;
}
//bc - кол-во валунов, tow - массив результатов, bb - помеченные использованные валуны для всех башен, rescount - кол-во башен каждого размера, bs - все валуны, mh - минимальная высота валуна, rh - высота, которую пытаемся получить.
void build(int bc,int ***tow,char ***bb,int *tc,int ***bs,int mh,int rh)
{
	int i,j,x,y,z,mr; // mr - MinusResult
	for(i=0; i<bc; i++)
		for(j=0; j<3; j++)
		{
			//смотрим, какую из предыдущих конструкций можно добавить к текущему валуну
			mr=rh-bs[i][j][2];
			if(mr>=mh && tow[mr]!=NULL)
			//если такая конструкция есть, шагаем по всем вариантам одной и той же высоты: смотрим, не входит ли в ее состав текущий камень и можно ли ее установить на текущий валун
				for(z=0; z<tc[mr]; z++)
					if((bb[mr][z][i]==0) && ((bs[i][j][0]>=tow[mr][z][0] && bs[i][j][1]>=tow[mr][z][1]) || (bs[i][j][0]>=tow[mr][z][1] && bs[i][j][1]>=tow[mr][z][0])))
					{
						if(tow[rh]==NULL)
						{
							//bc*3 - максимальное кол-во валунов одной и той же высоты
							tow[rh]=(int**)calloc(bc*3,sizeof(int**));
							bb[rh]=(char**)calloc(bc*3,sizeof(char*));
						}
						//добавляем новую башню в память
						tow[rh][tc[rh]]=(int*)calloc(3,sizeof(int));
						for(x=0; x<3; x++)
							tow[rh][tc[rh]][x]=bs[i][j][x];
						bb[rh][tc[rh]]=(char*)calloc(bc,sizeof(char));
						for(x=0; x<bc; x++)
							bb[rh][tc[rh]][x]=bb[mr][z][x];
						bb[rh][tc[rh]][i]=1;
						tc[rh]=tc[rh]+1;
						break;
					}
		}
}
int GetMaxHigh(int bc,int ***bs)
{
	int i,j,k,MinHigh,MaxHigh,***tow,*tc,TotalHigh=1;
	char ***bb;
	//ищем максимально допустимую высоту башни и наименьший камень
	for(i=0,MinHigh=bs[0][0][0]; i<bc; i++)
	{
		for(j=0,MaxHigh=bs[0][0][0]; j<3; j++)
		{
			if(bs[i][0][j]>MaxHigh)
				MaxHigh=bs[i][0][j];
			if(bs[i][0][j]<MinHigh)
				MinHigh=bs[i][0][j];
		}
		TotalHigh+=MaxHigh;
	}
	//заполняем память и добавляем все существующие валуны как отдельные башни
	tow=(int***)calloc(TotalHigh,sizeof(int***));
	bb=(char***)calloc(TotalHigh,sizeof(char**));
	tc=(int*)calloc(TotalHigh,sizeof(int));	
	for(i=0,MaxHigh=bs[0][0][2]; i<bc; i++)
		for(j=0; j<3; j++)
		{
			if(bs[i][j][2]>MaxHigh)
				MaxHigh=bs[i][j][2];
			if(tow[bs[i][j][2]]==NULL)
			{
				tow[bs[i][j][2]]=(int**)calloc(bc*3,sizeof(int*));
				bb[bs[i][j][2]]=(char**)calloc(bc*3,sizeof(int*));
			}
			tow[bs[i][j][2]][tc[bs[i][j][2]]]=(int*)calloc(3,sizeof(int));
			for(k=0; k<3; k++)
				tow[bs[i][j][2]][tc[bs[i][j][2]]][k]=bs[i][j][k];
			bb[bs[i][j][2]][tc[bs[i][j][2]]]=(char*)calloc(bc,sizeof(char));
			bb[bs[i][j][2]][tc[bs[i][j][2]]][i]=1;
			tc[bs[i][j][2]]=tc[bs[i][j][2]]+1;
		}
	//последовательно пытаемся получить каждую высоту
	for(i=MinHigh; i<TotalHigh; i++)
		if(tow[i]==NULL)
			build(bc,tow,bb,tc,bs,MinHigh,i);
	i=TotalHigh-1;
	while(tow[i]==NULL)
		i--;
	if(i>MaxHigh)
		MaxHigh=i;
	for(i=0; i<TotalHigh; i++)
		if(tow[i]!=NULL)
		{
			for(j=0; j<tc[i]; j++)
			{
				free(tow[i][j]);
				free(bb[i][j]);
			}
			free(tow[i]);
			free(bb[i]);
		}
	free(tow);
	free(bb);
	free(tc);
	return MaxHigh;
}
int main(void)
{
	int i,j,k,l,***boulders,RequiredResult,towersCount,BouldersCount,MyResult;
	time_t StartTime,EndTime;
	FILE *TestsFile=fopen("tests.txt","r");
	FILE *ResultsFile=fopen("correct-results.txt","r");
	fscanf(TestsFile,"%d",&towersCount);
	for(i=0; i<towersCount; i++)
	{
		StartTime=time(&StartTime);
		fscanf(TestsFile,"%d",&BouldersCount);
		printf("boulders %d; BouldersCount = %d\n",i+1,BouldersCount);
		boulders=(int***)malloc(sizeof(int**)*BouldersCount);
		for(j=0; j<BouldersCount; j++)
		{
			boulders[j]=(int**)malloc(sizeof(int*)*3);
			boulders[j][0]=(int*)malloc(sizeof(int)*3);
			for(k=0; k<3; k++)
			{
				fscanf(TestsFile,"%d",&boulders[j][0][k]);
				printf("%5d",boulders[j][0][k]);
			}
			for(k=1; k<3; k++)
			{
				boulders[j][k]=(int*)malloc(sizeof(int)*3);
				for(l=0; l<3; l++)
					boulders[j][k][l]=boulders[j][k-1][l];
				invert(boulders[j][k]);
			}
			putchar('|');
		}
		MyResult=GetMaxHigh(BouldersCount,boulders);
		fscanf(ResultsFile,"%d",&RequiredResult);
		printf("\nMY RESULT = %d;		 REQUIRED RESULT = %d ",MyResult,RequiredResult);
		for(j=0; j<BouldersCount; j++)
		{
			for(k=0; k<3; k++)
				free(boulders[j][k]);
			free(boulders[j]);
		}
		free(boulders);
		EndTime=time(&EndTime);
		printf("time: %d sec.\n--------------------------------------------------------------\n",EndTime-StartTime);
	}
	fclose(TestsFile);
	fclose(ResultsFile);
	return 0;
}
