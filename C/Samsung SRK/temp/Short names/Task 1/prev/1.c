#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
struct part
{
	int part;
	char *indexes;
};
int GetDigitsCount(int n)
{
	int i=0;
	while(n>0)
	{
		n/=10;
		i++;
	}
	return n;
}
void sort(int *a,int n)
{
	char sorted=0;
	int i,t;
	while(sorted!=1)
	{
		sorted=1;
		for(i=0; i<n-1; i++)
			if(a[i]<a[i+1])
			{
				sorted=0;
				t=a[i];
				a[i]=a[i+1];
				a[i+1]=t;
			}
	}
}
int GetBiggestLengthOfTwoEqualParts(int PartsCount, int *AllParts, char *FilePath)
{
	if(PartsCount<2)
		return 0;
	struct part *parts=(struct part*)malloc(sizeof(struct part)*(PartsCount*PartsCount*PartsCount));
	struct part *TempPart=(struct part*)malloc(1*sizeof(struct part));	
	int i,j,k,MaxPart,HalfOfAllPartsSum=0;
	int pn; //PartNumber - номер обрабатываемого отрезка
	int cpn; //CurrentPartNumber - новый номер отрезка, с которого начинаем считать допустимые суммы
	int pns=0; //PartNumberSum - номер отрезка-результата
	int ipn; //InitialPartNumber - номер отрезка, начиная с которого пытаемся добавить третий отрезок
	int ppc; //PreviousPartsCount - количество предыдущих отрезков в цикле добавления третьего отрезка
	char EqualIndexFound;
	FILE *f=fopen(FilePath,"wb"); //все результаты записываются в папку logs (хорошо выглядит только в Notepad++)
	//выделение памяти
	for(i=0; i<PartsCount*PartsCount*PartsCount; i++)
	{
		parts[i].part=0;
		parts[i].indexes=(char*)malloc(sizeof(char)*PartsCount);
		for(j=0; j<PartsCount; j++)
			parts[i].indexes[j]='0';
	}
	TempPart->indexes=(char*)malloc(sizeof(char)*PartsCount);
	TempPart->part=0;
	for(i=0; i<PartsCount; i++)
		TempPart->indexes[i]='0';
	//получаем сумму всех отрезков и затем делим ее на 2
	for(i=0; i<PartsCount; i++)
		HalfOfAllPartsSum+=AllParts[i];
	for(i=0; i<PartsCount; i++)
		fprintf(f,"%d ",AllParts[i]);
	fprintf(f,"\nSum of all parts = %d; HalfOfAllPartsSum = %d\n",HalfOfAllPartsSum,HalfOfAllPartsSum/2);
	HalfOfAllPartsSum/=2;
	//формируем список подходящих отрезков
	for(pn=0; pn<PartsCount; pn++)
	{		
		//если текущий отрезок меньше либо равен половине суммы всех отрезков, добавляем его
		if(AllParts[pn]<=HalfOfAllPartsSum)
		{
			parts[pns].part=AllParts[pn];
			parts[pns].indexes[pn]='1';
			pns++;
		}		
		cpn=pn+1; //цикл начинаем со следующего элемента
		//в отсортированном по убыванию списке ищем номер начального отрезка, подходящего нам по размеру, который является суммой двух рядом стоящих
		while(AllParts[pn]+AllParts[cpn]>HalfOfAllPartsSum && cpn<PartsCount)
			cpn++;
		//если перебрали весь список но подхоядщий отрезок не нашли, переходим на следующую итерацию цикла
		if(AllParts[cpn]+AllParts[pn]>HalfOfAllPartsSum)
			continue;
		//складываем отрезки между собой, подходящие добавляем в список
		for(i=0,ipn=cpn; i<PartsCount-cpn; i++,ipn=cpn)
		{
			//обнуляем временный отрезок
			TempPart->part=AllParts[pn];
			for(j=0; j<PartsCount; j++)
				TempPart->indexes[j]='0';
			TempPart->indexes[pn]='1';
			//наращиваем сумму во временном отрезке
			for(j=0; j<i && TempPart->part<HalfOfAllPartsSum; j++,ipn++)
			{
				TempPart->part=TempPart->part+AllParts[ipn];
				TempPart->indexes[ipn]='1';
				//если подходит по размеру, заносим ее в таблицу
				if(TempPart->part<=HalfOfAllPartsSum)
				{
					parts[pns].part=TempPart->part;
					for(k=0; k<=ipn; k++)
						parts[pns].indexes[k]=TempPart->indexes[k];
					pns++;
				}
			}
			//при выходе за предел переходим на следующую итерацию цикла
			if(TempPart->part>HalfOfAllPartsSum)
				continue;
			//смотрим, можно ли к временному отрезку добавить что-то еще
			while(ipn<PartsCount)
			{
				if(TempPart->part+AllParts[ipn]<=HalfOfAllPartsSum)
				{
					parts[pns].part=TempPart->part+AllParts[ipn];
					for(k=0; k<=ipn; k++)
						parts[pns].indexes[k]=TempPart->indexes[k];
					parts[pns].indexes[ipn]='1';
					pns++;
				}
				ipn++;
			}
		}
	}
	//ищем максимальный отрезок в таблице и запоминаем его индекс
	MaxPart=0;
	for(i=0; i<pns; i++)
		if(parts[i].part>MaxPart)
		{
			ppc=i;
			MaxPart=parts[i].part;
		}
	if(MaxPart>0)
	{
		//во временном отрезке помечаем, из каких элементов состоит максимальный отрезок
		for(i=0; i<PartsCount; i++)
			TempPart->indexes[i]=parts[ppc].indexes[i];
		//исходя из помеченных элементов, формируем второй отрезок. Если он равен предыдущему, то все правильно.
		pn=0;
		for(i=0; i<PartsCount && pn<MaxPart; i++)
			if(TempPart->indexes[i]=='0')
				pn+=AllParts[i];
		//иначе ищем два других максимальных отрезка, элементы которых между собой не пересекаются
		if(pn!=MaxPart)
		{
			MaxPart=0;
			for(i=0; i<pns; i++)
			{		
				for(j=i+1; j<pns; j++)
				{
					EqualIndexFound=0;
					if(parts[i].part==parts[j].part)
					{				
						for(k=0; k<PartsCount && EqualIndexFound<1; k++)
							if(parts[i].indexes[k]=='1' && parts[j].indexes[k]=='1')
								EqualIndexFound=1;
						if(EqualIndexFound==0 && parts[j].part>MaxPart)
							MaxPart=parts[j].part;
					}
				}
			}
		}
	}
	//записываем все результаты в файл
	fprintf(f,"\n-----------------------------------------------");
	fprintf(f,"\npns = %d",pns);
		for(i=0; i<pns; i++)
		{
			fprintf(f,"\npart = %d; ",parts[i].part);
			fprintf(f,"indexes: ");
			for(j=0; j<PartsCount; j++)
				fprintf(f,"%c",parts[i].indexes[j]);
		}
	fprintf(f,"\nMaxPart = %d",MaxPart);
	free(TempPart);
	free(parts);
	fclose(f);
	return MaxPart;
}	
int main(void)
{
	FILE *f=fopen("test.txt","r");
	int result;
	int i,temp,StrPartsCount,PartsCount,*numbers=NULL;
	int FileNumber=1;
	char *FilePath,*FileName=NULL;
	_mkdir("logs");
	fscanf(f,"%d",&StrPartsCount);	
	while(StrPartsCount-->0)
	{	
		FileName=(char*)malloc(4+(GetDigitsCount(FileNumber)*sizeof(char)));
		itoa(FileNumber,FileName,10);		
		strcat(FileName,".txt");
		FilePath=(char*)malloc(6+strlen(FileName));
		strcpy(FilePath,"logs\\");
		strcat(FilePath,FileName);
		FileNumber++;		
		fscanf(f,"%d",&PartsCount);
		numbers=(int*)malloc(PartsCount*sizeof(int));
		for(i=0; i<PartsCount; i++)
		{
			fscanf(f,"%d ",&numbers[i]);
			printf("%d ",numbers[i]);
		}
		printf("\nsorted: ");
		sort(numbers,PartsCount);
		for(i=0; i<PartsCount; i++)
			printf("%d ",numbers[i]);
		result=GetBiggestLengthOfTwoEqualParts(PartsCount,numbers,FilePath); 
		printf("\nBiggest length of two equal parts: %d; indexes:\n",result);
		free(numbers);		
		printf("======================================================\n");		
	}
	fclose(f);
	return 0;
}