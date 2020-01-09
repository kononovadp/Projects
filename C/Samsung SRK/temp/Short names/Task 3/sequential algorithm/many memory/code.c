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
//выравнивает последовательность элементов отсортированной башни
void sort(int bc,int **bs)
{
	char ReightResult=0;
	int i,j,t;
	while(ReightResult!=1)
	{
		ReightResult=1;
		for(i=0; i<bc; i++)
			for(j=i+1; j<bc; j++)
				if(bs[j][0]<bs[i][0] || bs[j][1]<bs[i][1])
				{
					ReightResult=0;
					t=bs[j][0];
					bs[j][0]=bs[j][1];
					bs[j][1]=t;
				}
	}
}
//bc - кол-во валунов, tow - массив результатов, bb - помеченные использованные валуны для всех башен, tc - кол-во башен каждого размера, bs - все валуны, mh - минимальная высота валуна, rh - высота, которую пытаемся получить.
void BuildTower(int bc,int ****tow,char ***bb,int *tc,int ***bs,int mh,int rh)
{
	int i,j,x,y,z,mr;
	for(i=0; i<bc; i++)
		for(j=0; j<3; j++)
		{
			//смотрим, какую из предыдущих конструкций можно добавить к текущему валуну
			mr=rh-bs[i][j][2];			
			//если такая конструкция есть, шагаем по всем вариантам одной и той же высоты: смотрим, не входит ли в ее состав текущий камень и можно ли ее установить на текущий валун
			if(mr>=mh && tow[mr]!=NULL)
				for(z=0; z<tc[mr]; z++)
					if((bb[mr][z][i]==0) && ((bs[i][j][0]>=tow[mr][z][bc-1][0] && bs[i][j][1]>=tow[mr][z][bc-1][1]) || (bs[i][j][0]>=tow[mr][z][bc-1][1] && bs[i][j][1]>=tow[mr][z][bc-1][0])))
					{
						if(tow[rh]==NULL)
						{
							//bc*3 - максимальное кол-во валунов одной и той же высоты
							tow[rh]=(int***)calloc(bc*3,sizeof(int**));
							bb[rh]=(char**)calloc(bc*3,sizeof(char*));
						}
						//добавляем новую башню в память
						tow[rh][tc[rh]]=(int**)calloc(bc,sizeof(int*));
						for(x=0; x<bc; x++)
							tow[rh][tc[rh]][x]=(int*)calloc(3,sizeof(int));
						for(x=0; x<bc-1; x++)
							for(y=0; y<3; y++)
								tow[rh][tc[rh]][x][y]=tow[mr][z][x+1][y];
						for(x=0; x<3; x++)
							tow[rh][tc[rh]][bc-1][x]=bs[i][j][x];
						bb[rh][tc[rh]]=(char*)calloc(bc,sizeof(char));
						for(x=0; x<bc; x++)
							bb[rh][tc[rh]][x]=bb[mr][z][x];
						bb[rh][tc[rh]][i]=1;
						tc[rh]=tc[rh]+1;
						break;
					}
		}
}
//bc - BouldersCount; bs - boulders
int GetMaxHigh(int bc,int ***bs,FILE *ResultsFile)
{
	int i,j,k,MinHigh,MaxHigh,****tow,*tc,TotalHigh=1;
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
	tow=(int****)calloc(TotalHigh,sizeof(int***));
	bb=(char***)calloc(TotalHigh,sizeof(char**));
	tc=(int*)calloc(TotalHigh,sizeof(int));
	for(i=0,MaxHigh=bs[0][0][2]; i<bc; i++)
		for(j=0; j<3; j++)
		{
			if(bs[i][j][2]>MaxHigh)
				MaxHigh=bs[i][j][2];
			if(tow[bs[i][j][2]]==NULL)
			{
				tow[bs[i][j][2]]=(int***)calloc(bc*3,sizeof(int**));
				bb[bs[i][j][2]]=(char**)calloc(bc*3,sizeof(int*));
			}
			tow[bs[i][j][2]][tc[bs[i][j][2]]]=(int**)calloc(bc,sizeof(int*));
			for(k=0; k<bc; k++)
				tow[bs[i][j][2]][tc[bs[i][j][2]]][k]=(int*)calloc(3,sizeof(int));
			for(k=0; k<3; k++)
				tow[bs[i][j][2]][tc[bs[i][j][2]]][bc-1][k]=bs[i][j][k];
			bb[bs[i][j][2]][tc[bs[i][j][2]]]=(char*)calloc(bc,sizeof(char));
			bb[bs[i][j][2]][tc[bs[i][j][2]]][i]=1;
			tc[bs[i][j][2]]=tc[bs[i][j][2]]+1;
		}
	//последовательно пытаемся получить каждую высоту
	for(i=MinHigh; i<TotalHigh; i++)
		if(tow[i]==NULL)
			BuildTower(bc,tow,bb,tc,bs,MinHigh,i);
	i=TotalHigh-1;
	while(tow[i]==NULL)
		i--;
	if(i>MaxHigh)
		MaxHigh=i;
	for(i=0; i<tc[MaxHigh]; i++)
	{
		sort(bc,tow[MaxHigh][i]);
		fprintf(ResultsFile,"\nTOWER %d:\n",i+1);
		for(j=0; j<bc-1; j++,fprintf(ResultsFile,"\n"))
			for(k=0; k<3; k++)
				fprintf(ResultsFile,"%5d",tow[MaxHigh][i][j][k]);
		for(k=0; k<3; k++)
			fprintf(ResultsFile,"%5d",tow[MaxHigh][i][j][k]);
		if(i!=tc[MaxHigh]-1)
			fprintf(ResultsFile,"\n");
	}
	for(i=0; i<TotalHigh; i++)
		if(tow[i]!=NULL)
		{
			for(j=0; j<tc[i]; j++)
			{
				for(k=0; k<bc; k++)
					free(tow[i][j][k]);
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
