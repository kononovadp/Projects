#include <stdio.h>
#include <malloc.h>
/*5. 6867/7=981 - 7 нажатий вместо 9;
7. 1111-122-2=987 - 11 нажатий вместо 12;
9. 1111-122-2=987 - 11 нажатий вместо 20;
13. 1000/2=500 - 7 нажатий вместо 8;*/

//ф-я получает кол-во цифр в числе
int GetDigitsCount(long long int n)
{
	int i=0;
	while(n>0)
	{
		n/=10;
		i++;
	}
	return i;
}
//ф-я возвращает максимальный предел для операций деления и умножения
long long int GetMaxForDivAndMinus(long long int rn)
{
	long long int max=1;	
	while(rn>1)
	{		
		max*=10;
		rn/=10;
	}
	return max*10;
}
//ф-я проверяет, можно ли число набрать без арифметических действий
//ds - digits; dc - DigitsCount; rn - RequiredNumber
long long int CheckNumber(int *ds,int dc,long long int rn)
{
	int i,j,mod,ndc;
	char found=1;
	if(rn==0)
	{
		for(i=0; i<dc; i++)
			if(ds[i]==0)
				return 1;
		return 0;
	}
	for(i=0,ndc=GetDigitsCount(rn); i<ndc && found==1; i++)
	{
		found=0;
		mod=rn%10;
		rn/=10;
		for(j=0; j<dc && found==0; j++)
			if(ds[j]==mod)
				found=1;
	}
	if(found==1)
		return ndc;
	return 0;
}
/*Основная рекурсивная ф-я пересчета. Список переменных:
*ds - массив чисел на клавиатуре; dc - кол-во доступных чисел на клавиатуре;
*op - массив символов арифметических операций; oc - кол-во операций;
cpc - текущее кол-во нажатий; min - текущее минимальное кол-во нажатий;
rn - число, которое нужно набрать; mfm - максимум для операций деления и
умножения; n - все результаты для избежания полного перебора; k - все числа,
которые можно набрать без арифметических операций; oprnds - числа, с 
помощью которых получен результат; oprs - операции; opc - кол-во операций.*/
long long int calc(int *ds,int dc,char *op,int oc,int cpc,int min,long long int rn,long long int mfm,char *n,char *k,long long int *oprnds,char *oprs,char *opc)
{
	long long int i,res,max,op1,op2;
	int j,prevmin=min;
	char charop;
	//если предыдущий результат равен -1 или текущее кол-во нажатий
	//превышает текущий минимум, то возвращаем -1
	if(n[rn]==-1 || cpc>min)
		return -1;
	//если результат для данного числа уже был получен, то возвращает его
	if(n[rn]>0)
	{	//если вызываем ф-ю первый раз, то знак "равно" не добавляем
		if(cpc==0)
			cpc=n[rn];
		else
			if(n[rn]>0)
				cpc=cpc+n[rn]+1;
		return cpc;
	}
	for(j=0; j<oc; j++)
		if(op[j]=='+')
		{
			for(i=rn-1; i>0; i--)
				if(n[i]>0)
				{
					res=calc(ds,dc,op,oc,cpc+n[i]+1,min,rn-i,mfm,n,k,oprnds,oprs,opc);
					if(res>0 && res<min)
					{
						min=res;
						op1=i;
						charop='+';
						op2=rn-i;
					}
				}
		}
		else
			if(op[j]=='*')
			{
				for(i=rn-1; i>1; i--)
					if(n[i]>0 && rn%i==0)
					{
						res=calc(ds,dc,op,oc,cpc+n[i]+1,min,rn/i,mfm,n,k,oprnds,oprs,opc);
						if(res>0 && res<min)
						{
							min=res;
							op1=i;
							charop='*';
							op2=rn/i;
						}
					}
			}
			else
				if(op[j]=='-')
				{
					for(max=mfm-rn,i=max; i>0; i--)
						if(n[i]>0)
						{
							res=calc(ds,dc,op,oc,cpc+n[i]+1,min,rn+i,mfm,n,k,oprnds,oprs,opc);
							if(res>0 && res<min)
							{
								min=res;
								op1=i;
								charop='-';
								op2=rn+i;
							}
						}
					}
					else
						if(op[j]=='/')
						{
							for(max=mfm/rn,i=max; i>1; i--)
								if(n[i]>0)
								{
									res=calc(ds,dc,op,oc,cpc+n[i]+1,min,rn*i,mfm,n,k,oprnds,oprs,opc);
									if(res>0 && res<min)
									{
										min=res;
										op1=i;
										charop='/';
										op2=rn*i;
									}
								}
						}
	if(min==prevmin)
		return n[rn]=-1;
	//сохранение чисел, с помощью которых получен результат
	if(k[op2]>0 && k[op1]>0)
	{
		*opc=0;
		oprnds[0]=op2;
		oprnds[1]=op1;
		oprs[0]=charop;
		*opc=1;
	}
	else
	{
		oprnds[*opc+1]=op1;
		oprs[*opc]=charop;
		*opc=*opc+1;
	}
	return n[rn]=min;
}
/*ds - числа на клавиатуре; dc - кол-во чисел на клавиатуре; op - операции;
oc - кол-во операций; mpc - максимальное допустимое кол-во нажатий; rn - 
число, которое нужно набрать.*/
long long int GetResult(int *ds,int dc,char *op,int oc,int mpc,long long int rn)
{
	long long int i,md,res,*oprnds,max=rn+1;
	char *k,*n,*oprs,opc=0;
	for(i=0,md=0; i<oc; i++)
		if(op[i]=='-' || op[i]=='/')
		{
			md=1;
			break;
		}
	if(md==1)
		max=GetMaxForDivAndMinus(rn);
	//формируем список чисел, которые можно набрать, не выполняя 
	//арифметические действия
	n=(char*)calloc(max,sizeof(char));
	k=(char*)calloc(max,sizeof(char));	
	for(i=0; i<max; i++)
	{
		n[i]=CheckNumber(ds,dc,i);
		k[i]=n[i];
	}
	if(n[rn]>0)
	{
		printf("\n%lld",rn);
		res=n[rn];
	}
	else
	{
		oprnds=(long long int*)malloc(mpc*sizeof(long long int));
		oprs=(char*)malloc(mpc*sizeof(char));
		res=calc(ds,dc,op,oc,0,mpc+1,rn,max-1,n,k,oprnds,oprs,&opc);
		if(res>0)
		{
			putchar('\n');
			for(i=0; i<opc; i++)
				printf("%lld%c",oprnds[i],oprs[i]);
			printf("%lld=%lld",oprnds[i],rn);
		}
		free(oprnds);
		free(oprs);
	}
	free(n);
	free(k);		
	return res;
}
int main(void)
{
	int i,j,dc,OperationsCount,MaxPressCount,*n,RightResult,TasksCount=0;
	long long int res,rn;
	char *operations;
	FILE *f=fopen("tests-input.txt","r");
	FILE *ft=fopen("correct-output.txt","r");
	fscanf(f,"%d",&TasksCount);
	for(j=0; j<TasksCount; j++)
	{
		fscanf(f,"%d",&dc);
		n=(int*)malloc(dc*sizeof(int));
		for(i=0; i<dc; i++)
			fscanf(f,"%d ",&n[i]);
		fscanf(f,"%d",&OperationsCount);
		operations=(char*)malloc(OperationsCount*sizeof(char));
		for(i=0; i<OperationsCount; i++)
			fscanf(f," %c",&operations[i]);
		fscanf(f,"%d",&MaxPressCount);
		fscanf(f," %lld",&rn);
		printf("%d. dc = %d: ",j+1,dc);
		for(i=0; i<dc; i++)
			printf("%d ",n[i]);
		printf("OperationsCount = %d ",OperationsCount);
		for(i=0; i<OperationsCount; i++)
			printf("%c ",operations[i]);
		printf("\nMaxPressCount = %d; rn = %lld; ",MaxPressCount,rn);
		res=GetResult(n,dc,operations,OperationsCount,MaxPressCount,rn);
		fscanf(ft,"%d",&RightResult);
		printf("\n		MY RESULT = %lld; RIGHT RESULT = %d",res,RightResult);
		printf("\n=====================================================\n");
		free(n);
		free(operations);
	}
	fclose(f);
	fclose(ft);
	return 0;
}
