#include <stdio.h>
#include <malloc.h>
#include <time.h>
void invert(int *b)
{
	int t=b[2];
	b[2]=b[1];
	b[1]=b[0];
	b[0]=t;
}
//рекурсивная функция, которая определяет максимальную высоту башни, которую можно получить установив свободные камни на поверхность определенных размеров.
//bc - кол-во валунов, bs - все валуны, cb - номер текущего установленного валуна в общем списке, ch - текущая высота башни, bb - помеченные занятые валуны, bw - ширина пола, bl - длина пола
int BuildTower(int bc,int ***bs,int cb,int ch,char *bb,int bw,int bl)
{
	int i,j,res,mh=0; //mh - MaxHigh	
	//помечаем текущий камень как использованный и смотрим, что на него можно установить
	bb[cb]=1;
	for(i=0,mh=ch; i<3; i++)
	{
		//устанавливаем камень на башню в i-м положении
		ch=ch+bs[cb][i][2];		
		//если текущий камень после изменения положения все еще может стоять на данной конструкции,...
		if((bs[cb][i][0]<=bw && bs[cb][i][1]<=bl) || (bs[cb][i][0]<=bl && bs[cb][i][1]<=bw))
		{	//то рекурсивно ищем что на него еще можно установить		
			for(j=0; j<bc; j++)
				if(bb[j]==0)
				{
					res=BuildTower(bc,bs,j,ch,bb,bs[cb][i][0],bs[cb][i][1]);
					if(res>mh)
						mh=res;
				}
			if(bs[cb][i][2]>mh)
				mh=bs[cb][i][2];
			if(ch>mh)
				mh=ch;
		}
		//снимаем камень с башни
		ch=ch-bs[cb][i][2];
	}
	bb[cb]=0;
	return mh;
}
int Getresult(int bc,int ***bs)
{
	int i,res,mh=bs[0][0][2];
	char *bb=(char*)calloc(sizeof(char),bc);
	//пытаемся получить максимальную высоту башни, начиная с i-го камня
	for(i=0,res=bs[0][0][2]; i<bc; i++)
	{
		res=BuildTower(bc,bs,i,0,bb,10001,10001);
		if(res>mh)
			mh=res;
	}
	free(bb);
	return mh;
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
