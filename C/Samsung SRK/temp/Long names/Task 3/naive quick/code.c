#include <stdio.h>
#include <malloc.h>
#include <time.h>
void invert(int *boulder)
{
	int t=boulder[2];
	boulder[2]=boulder[1];
	boulder[1]=boulder[0];
	boulder[0]=t;
}
//рекурсивная функция, которая определяет максимальную высоту башни, которую можно получить установив свободные камни на поверхность определенных размеров.
//BouldersCount - кол-во валунов, boulders - все валуны, CurrentBoulder - номер текущего установленного валуна в общем списке, CurrentHigh - текущая высота башни, BusyBoulders - помеченные занятые валуны, BoulderWidth - ширина пола, BoulderLength - длина пола
int BuildTower(int BouldersCount,int ***boulders,int CurrentBoulder,int CurrentHigh,char *BusyBoulders,int BoulderWidth,int BoulderLength)
{
	int i,j,result,MaxHigh=0;	
	//помечаем текущий камень как использованный и смотрим, что на него можно установить
	BusyBoulders[CurrentBoulder]=1;
	for(i=0,MaxHigh=CurrentHigh; i<3; i++)
	{
		//устанавливаем камень на башню в i-м положении
		CurrentHigh=CurrentHigh+boulders[CurrentBoulder][i][2];		
		//если текущий камень после изменения положения все еще может стоять на данной конструкции,...
		if((boulders[CurrentBoulder][i][0]<=BoulderWidth && boulders[CurrentBoulder][i][1]<=BoulderLength) || (boulders[CurrentBoulder][i][0]<=BoulderLength && boulders[CurrentBoulder][i][1]<=BoulderWidth))
		{	//то рекурсивно ищем что на него еще можно установить		
			for(j=0; j<BouldersCount; j++)
				if(BusyBoulders[j]==0)
				{
					result=BuildTower(BouldersCount,boulders,j,CurrentHigh,BusyBoulders,boulders[CurrentBoulder][i][0],boulders[CurrentBoulder][i][1]);
					if(result>MaxHigh)
						MaxHigh=result;
				}
			if(boulders[CurrentBoulder][i][2]>MaxHigh)
				MaxHigh=boulders[CurrentBoulder][i][2];
			if(CurrentHigh>MaxHigh)
				MaxHigh=CurrentHigh;
		}
		//снимаем камень с башни
		CurrentHigh=CurrentHigh-boulders[CurrentBoulder][i][2];
	}
	BusyBoulders[CurrentBoulder]=0;
	return MaxHigh;
}
int Getresult(int BouldersCount,int ***boulders)
{
	int i,result,MaxHigh=boulders[0][0][2];
	char *BusyBoulders=(char*)calloc(sizeof(char),BouldersCount);
	//пытаемся получить максимальную высоту башни, начиная с i-го камня
	for(i=0,result=boulders[0][0][2]; i<BouldersCount; i++)
	{
		result=BuildTower(BouldersCount,boulders,i,0,BusyBoulders,10001,10001);
		if(result>MaxHigh)
			MaxHigh=result;
	}
	free(BusyBoulders);
	return MaxHigh;
}
int main(void)
{
	int i,j,k,l,RequiredResult,towersCount,BouldersCount,MyResult,***boulders;
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
		MyResult=Getresult(BouldersCount,boulders);
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
