#include <stdio.h>
#include <malloc.h>
#include <time.h>
//переворачивает камень
void invert(int *boulder)
{
	int t=boulder[2];
	boulder[2]=boulder[1];
	boulder[1]=boulder[0];
	boulder[0]=t;
}
//выравнивает последовательность элементов отсортированной башни
void sort(int BouldersCount,int **boulders)
{
	char ReightResult=0;
	int i,j,t;
	while(ReightResult!=1)
	{
		ReightResult=1;
		for(i=0; i<BouldersCount; i++)
			for(j=i+1; j<BouldersCount; j++)
				if(boulders[j][0]<boulders[i][0] || boulders[j][1]<boulders[i][1])
				{
					ReightResult=0;
					t=boulders[j][0];
					boulders[j][0]=boulders[j][1];
					boulders[j][1]=t;
				}
	}
}
//BouldersCount - кол-во валунов, towers - массив результатов, BusyBoulders - помеченные использованные валуны для всех башен, TowersCount - кол-во башен каждого размера, boulders - все валуны, MinHigh - минимальная высота валуна, RequiredHigh - высота, которую пытаемся получить.
void BuildTower(int BouldersCount,int ****towers,char ***BusyBoulders,int *TowersCount,int ***boulders,int MinHigh,int RequiredHigh)
{
	int i,j,x,y,z,MinusResult;
	for(i=0; i<BouldersCount; i++)
		for(j=0; j<3; j++)
		{
			//смотрим, какую из предыдущих конструкций можно добавить к текущему валуну
			MinusResult=RequiredHigh-boulders[i][j][2];			
			//если такая конструкция есть, шагаем по всем вариантам одной и той же высоты: смотрим, не входит ли в ее состав текущий камень и можно ли ее установить на текущий валун
			if(MinusResult>=MinHigh && towers[MinusResult]!=NULL)
				for(z=0; z<TowersCount[MinusResult]; z++)
					if((BusyBoulders[MinusResult][z][i]==0) && ((boulders[i][j][0]>=towers[MinusResult][z][BouldersCount-1][0] && boulders[i][j][1]>=towers[MinusResult][z][BouldersCount-1][1]) || (boulders[i][j][0]>=towers[MinusResult][z][BouldersCount-1][1] && boulders[i][j][1]>=towers[MinusResult][z][BouldersCount-1][0])))
					{
						if(towers[RequiredHigh]==NULL)
						{
							//BouldersCount*3 - максимальное кол-во валунов одной и той же высоты
							towers[RequiredHigh]=(int***)calloc(BouldersCount*3,sizeof(int**));
							BusyBoulders[RequiredHigh]=(char**)calloc(BouldersCount*3,sizeof(char*));
						}
						//добавляем новую башню в память
						towers[RequiredHigh][TowersCount[RequiredHigh]]=(int**)calloc(BouldersCount,sizeof(int*));
						for(x=0; x<BouldersCount; x++)
							towers[RequiredHigh][TowersCount[RequiredHigh]][x]=(int*)calloc(3,sizeof(int));
						for(x=0; x<BouldersCount-1; x++)
							for(y=0; y<3; y++)
								towers[RequiredHigh][TowersCount[RequiredHigh]][x][y]=towers[MinusResult][z][x+1][y];
						for(x=0; x<3; x++)
							towers[RequiredHigh][TowersCount[RequiredHigh]][BouldersCount-1][x]=boulders[i][j][x];
						BusyBoulders[RequiredHigh][TowersCount[RequiredHigh]]=(char*)calloc(BouldersCount,sizeof(char));
						for(x=0; x<BouldersCount; x++)
							BusyBoulders[RequiredHigh][TowersCount[RequiredHigh]][x]=BusyBoulders[MinusResult][z][x];
						BusyBoulders[RequiredHigh][TowersCount[RequiredHigh]][i]=1;
						TowersCount[RequiredHigh]=TowersCount[RequiredHigh]+1;
						break;
					}
		}
}
int GetMaxHigh(int BouldersCount,int ***boulders,FILE *MyResults)
{
	int i,j,k,MinHigh,MaxHigh,****towers,*TowersCount,TotalHigh=1;
	char ***BusyBoulders;
	//ищем максимально допустимую высоту башни и наименьший камень
	for(i=0,MinHigh=boulders[0][0][0]; i<BouldersCount; i++)
	{
		for(j=0,MaxHigh=boulders[0][0][0]; j<3; j++)
		{
			if(boulders[i][0][j]>MaxHigh)
				MaxHigh=boulders[i][0][j];
			if(boulders[i][0][j]<MinHigh)
				MinHigh=boulders[i][0][j];
		}
		TotalHigh+=MaxHigh;
	}
	//заполняем память и добавляем все существующие валуны как отдельные башни
	towers=(int****)calloc(TotalHigh,sizeof(int***));
	BusyBoulders=(char***)calloc(TotalHigh,sizeof(char**));
	TowersCount=(int*)calloc(TotalHigh,sizeof(int));
	for(i=0,MaxHigh=boulders[0][0][2]; i<BouldersCount; i++)
		for(j=0; j<3; j++)
		{
			if(boulders[i][j][2]>MaxHigh)
				MaxHigh=boulders[i][j][2];
			if(towers[boulders[i][j][2]]==NULL)
			{
				towers[boulders[i][j][2]]=(int***)calloc(BouldersCount*3,sizeof(int**));
				BusyBoulders[boulders[i][j][2]]=(char**)calloc(BouldersCount*3,sizeof(int*));
			}
			towers[boulders[i][j][2]][TowersCount[boulders[i][j][2]]]=(int**)calloc(BouldersCount,sizeof(int*));
			for(k=0; k<BouldersCount; k++)
				towers[boulders[i][j][2]][TowersCount[boulders[i][j][2]]][k]=(int*)calloc(3,sizeof(int));
			for(k=0; k<3; k++)
				towers[boulders[i][j][2]][TowersCount[boulders[i][j][2]]][BouldersCount-1][k]=boulders[i][j][k];
			BusyBoulders[boulders[i][j][2]][TowersCount[boulders[i][j][2]]]=(char*)calloc(BouldersCount,sizeof(char));
			BusyBoulders[boulders[i][j][2]][TowersCount[boulders[i][j][2]]][i]=1;
			TowersCount[boulders[i][j][2]]=TowersCount[boulders[i][j][2]]+1;
		}
	//последовательно пытаемся получить каждую высоту
	for(i=MinHigh; i<TotalHigh; i++)
		if(towers[i]==NULL)
			BuildTower(BouldersCount,towers,BusyBoulders,TowersCount,boulders,MinHigh,i);
	i=TotalHigh-1;
	while(towers[i]==NULL)
		i--;
	if(i>MaxHigh)
		MaxHigh=i;
	for(i=0; i<TowersCount[MaxHigh]; i++)
	{
		sort(BouldersCount,towers[MaxHigh][i]);
		fprintf(MyResults,"\nTOWER %d:\n",i+1);
		for(j=0; j<BouldersCount-1; j++,fprintf(MyResults,"\n"))
			for(k=0; k<3; k++)
				fprintf(MyResults,"%5d",towers[MaxHigh][i][j][k]);
		for(k=0; k<3; k++)
			fprintf(MyResults,"%5d",towers[MaxHigh][i][j][k]);
		if(i!=TowersCount[MaxHigh]-1)
			fprintf(MyResults,"\n");
	}
	for(i=0; i<TotalHigh; i++)
		if(towers[i]!=NULL)
		{
			for(j=0; j<TowersCount[i]; j++)
			{
				for(k=0; k<BouldersCount; k++)
					free(towers[i][j][k]);
				free(towers[i][j]);
				free(BusyBoulders[i][j]);
			}
			free(towers[i]);
			free(BusyBoulders[i]);
		}
	free(towers);
	free(BusyBoulders);
	free(TowersCount);
	return MaxHigh;
}
int main(void)
{
	int i,j,k,l,***boulders,RequiredResult,towersCount,BouldersCount,MyResult;
	time_t StartTime,EndTime;
	FILE *TestsFile=fopen("tests.txt","r");
	FILE *ResultsFile=fopen("correct-results.txt","r");
	FILE *MyResults=fopen("my results.txt","w");
	fscanf(TestsFile,"%d",&towersCount);
	for(i=0; i<towersCount; i++)
	{
		StartTime=time(&StartTime);
		fscanf(TestsFile,"%d",&BouldersCount);
		printf("boulders %d; BouldersCount = %d\n",i+1,BouldersCount);
		fprintf(MyResults,"boulders %d; BouldersCount = %d\n",i+1,BouldersCount);
		boulders=(int***)malloc(sizeof(int**)*BouldersCount);
		for(j=0; j<BouldersCount; j++)
		{
			boulders[j]=(int**)malloc(sizeof(int*)*3);
			boulders[j][0]=(int*)malloc(sizeof(int)*3);
			for(k=0; k<3; k++)
			{
				fscanf(TestsFile,"%d",&boulders[j][0][k]);
				printf("%5d",boulders[j][0][k]);
				fprintf(MyResults,"%5d",boulders[j][0][k]);
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
		MyResult=GetMaxHigh(BouldersCount,boulders,MyResults);
		fscanf(ResultsFile,"%d",&RequiredResult);
		printf("\nMY RESULT = %d;		 REQUIRED RESULT = %d ",MyResult,RequiredResult);
		fprintf(MyResults,"\nMY RESULT = %d;		 REQUIRED RESULT = %d ",MyResult,RequiredResult);
		for(j=0; j<BouldersCount; j++)
		{
			for(k=0; k<3; k++)
				free(boulders[j][k]);
			free(boulders[j]);
		}
		free(boulders);
		EndTime=time(&EndTime);
		printf("time: %d sec.\n--------------------------------------------------------------\n",EndTime-StartTime);
		fprintf(MyResults,"time: %d sec.\n--------------------------------------------------------------\n",EndTime-StartTime);
	}
	fclose(TestsFile);
	fclose(MyResults);
	fclose(ResultsFile);
	printf("All results written to the file my results.txt");
	return 0;
}
