#include <stdio.h>
#include <malloc.h>
//ф-я получает кол-во цифр в числе
int GetDigitsCount(unsigned long long n)
{
	int i=0;
	while(n>0)
	{
		n/=10;
		i++;
	}
	return i;
}
//ф-я проверяет, можно ли число набрать без арифметических действий
//n - numbers; nc - NumbersCount; rn - RequiredNumber
int CheckNumber(int *n,int nc,unsigned long long rn)
{
	int i,j,mod,dg=GetDigitsCount(rn);
	char found=1;
	if(rn==0)
	{
		for(i=0; i<nc; i++)
			if(n[i]==0)
				return 1;
		return -1;
	}
	for(i=0; i<dg && found==1; i++)
	{
		found=0;
		mod=rn%10;
		rn/=10;
		for(j=0; j<nc && found==0; j++)
			if(n[j]==mod)
				found=1;
	}
	if(found==1)
		return dg;
	return 0;
}
//ф-я возвращает максимальный предел для операций деления и умножения
unsigned long long GetMaxForDivAndMinus(unsigned long long rn)
{
	unsigned long long max=1;
	while(rn>1)
	{		
		max*=10;
		rn/=10;
	}
	return max*10;
}
/*Основная рекурсивная ф-я пересчета. Список переменных:
op - массив символов арифметических операций;
oc - кол-во операций;
mpc - максимальное кол-во нажатий;
rn - число, которое нужно набрать;
max - максимум для операций деления и отнимания;
c - кэш, который хранит минимальное кол-во нажатий для получения каждого числа;
с2 - кэш, который хранит текущее кол-во нажатий для получения каждого числа;
PlusMult и MinusDiv - определяют, нужно ли запускать определенный цикл вычислений.
Переменные для сохранения арифметического выражения (пути к результату):
oprnds - массив, который хранит пару операндов для получения каждого числа;
oprs - массив, который хранит операции для получения каждого числа.*/
int calc(char *op,int oc,int mpc,unsigned long long rn,unsigned long long max,int *c,int *c2,char PlusMult,char MinusDiv,unsigned long long **oprnds,char *oprs)
{	
	unsigned long long i,op1,op2;
	int j,res,min=mpc;
	//если результат для данного числа уже был получен, то возвращаем его
	if(c[rn]>0)
		return c[rn];
	//если предыдущий результат равен -1 или текущее кол-во нажатий
	//превышает текущий минимум, то возвращаем -1
	if(c[rn]==-1 || c2[rn]>=mpc)
		return -1;
	c[rn]=-1; //чтобы повторно не вызывать ф-ю для этого же числа
	if(PlusMult==1) //если есть операция сложения или умножения
		for(i=rn-1; i>0; i--)
			//если число уже было получено
			if(c[i]>0)
			{
				c2[rn]=c2[rn]+c[i]+1;
				res=c2[rn];
				for(j=0; j<oc; j++)
				{				
					if(op[j]=='+')
						res=c2[rn]+calc(op,oc,mpc,rn-i,max,c,c2,PlusMult,MinusDiv,oprnds,oprs);
					else
						if(op[j]=='*' && rn%i==0)
							res=c2[rn]+calc(op,oc,mpc,rn/i,max,c,c2,PlusMult,MinusDiv,oprnds,oprs);
					if(res>c2[rn] && res<min)
					{
						min=res;
						//сохранение "пути" к результату
						op1=i;
						oprs[rn]=op[j];
						if(op[j]=='+')
							op2=rn-i;
						else
							if(op[j]=='*')
								op2=rn/i;
					}
				}
				c2[rn]=c2[rn]-c[i]-1;
			}
	if(MinusDiv==1) //если есть операция отнимания или деления
		for(i=rn+1; i<max; i++)
			//если число уже было получено
			if(c[i]>0)
			{
				c2[rn]=c2[rn]+c[i]+1;
				res=c2[rn];
				for(j=0; j<oc; j++)
				{				
					if(op[j]=='-')
						res=c2[rn]+calc(op,oc,mpc,i-rn,max,c,c2,PlusMult,MinusDiv,oprnds,oprs);
					else
						if(op[j]=='/' && i%rn==0)
							res=c2[rn]+calc(op,oc,mpc,i/rn,max,c,c2,PlusMult,MinusDiv,oprnds,oprs);
					if(res>c2[rn] && res<min)
					{
						min=res;
						//сохранение "пути" к результату
						op1=i;
						oprs[rn]=op[j];
						if(op[j]=='-')
							op2=i-rn;
						else
							if(op[j]=='/')
								op2=i/rn;
					}
				}
				c2[rn]=c2[rn]-c[i]-1;
			}
	//если минимум не поменялся, значит число нельзя набрать
	if(min==mpc)
		return c[rn]=-1;
	//иначе сохраняем "путь" к нему и записываем результат в кэш
	oprnds[rn]=(unsigned long long*)calloc(2,sizeof(unsigned long long));
	oprnds[rn][0]=op1;
	oprnds[rn][1]=op2;
	return c[rn]=min;
}
/*определение приоритета выражения перед выводом на экран
o - все операнды; op - символы операций;
k - числа, которые можно получить только с помощью заданного набора цифр;
rn - число, арифметическое выражение которого нужно вывести; res - результат*/
void ChoosePriority(unsigned long long **o,char *op,int *k,unsigned long long rn,char *res)
{
	if(k[o[rn][0]]==0)
		ChoosePriority(o,op,k,o[rn][0],res);
	if(k[o[rn][1]]==0)
		ChoosePriority(o,op,k,o[rn][1],res);
	if(op[rn]=='*' || op[rn]=='/')
		*res=1;
}
/*вывод выражения на экран
o - все операнды; op - символы операций;
k - числа, которые можно получить только с помощью заданного набора цифр;
rn - число, арифметическое выражение которого нужно вывести*/
void ShowExpression(unsigned long long **o,char *op,int *k,unsigned long long rn)
{
	unsigned long long t;
	char prior=0;
	//если второй операнд "составной", выясняем, использовались ли для его получения
	//операции умножения или деления. Если использовались, выводим сначала его.
	if(k[o[rn][1]]==0)
	{
		ChoosePriority(o,op,k,o[rn][1],&prior);
		if(prior==1)
		{
			t=o[rn][1];
			o[rn][1]=o[rn][0];
			o[rn][0]=t;
		}
	}
	if(k[o[rn][0]]==0)
		ShowExpression(o,op,k,o[rn][0]);
	else
		printf("%lld",o[rn][0]);
	putchar(op[rn]);
	if(k[o[rn][1]]==0)
		ShowExpression(o,op,k,o[rn][1]);
	else
		printf("%lld",o[rn][1]);
}
int GetResult(int *ds,int dc,char *op,int oc,int mpc,unsigned long long rn)
{
	unsigned long long i,**oprnds,max=rn+1;
	int *c,*c2,*k,res,j;
	char *oprs,PlusMult=0,MinusDiv=0;	
	for(j=0; j<oc; j++)
		if(op[j]=='-' || op[j]=='/')
			MinusDiv=1;
		else
			if(op[j]=='+' || op[j]=='*')
				PlusMult=1;
	//если есть операции деления или отнимания, нужен разумный предел,
	//так как выполняем обратные действия
	if(MinusDiv==1)
		max=GetMaxForDivAndMinus(rn)+1;
	//формируем список чисел, которые можно набрать, не выполняя 
	//арифметические действия
	c=(int*)calloc(max,sizeof(int));
	k=(int*)calloc(max,sizeof(int));
	c2=(int*)calloc(max,sizeof(int));
	for(i=0; i<max; i++)
	{
		c[i]=CheckNumber(ds,dc,i);
		k[i]=c[i];
	}
	if(c[rn]>0)
	{
		printf("\n%lld",rn);
		res=c[rn];
	}
	else
	{
		oprnds=(unsigned long long**)calloc(max,sizeof(unsigned long long*));
		oprs=(char*)calloc(max,sizeof(char));
		res=calc(op,oc,mpc,rn,max,c,c2,PlusMult,MinusDiv,oprnds,oprs);
		//если результат получен, прибавляем знак "равно"
		if(res>0)
			res++;
		if(res==mpc)
			res=-1;		
		if(res>0)
		{
			putchar('\n');
			ShowExpression(oprnds,oprs,k,rn);		
			printf("=%lld",rn);
		}
		for(i=0; i<max; i++)
			if(oprnds[i]!=NULL)
				free(oprnds[i]);
		free(oprnds);
		free(oprs);
	}
	free(c);
	free(k);
	free(c2);
	return res;
}
int main(void)
{
	int i,j,nc,res,OperationsCount,MaxPressCount,*n,RightResult,TasksCount=0;
	unsigned long long rn;
	char *operations;
	FILE *f=fopen("tests-input.txt","r");
	FILE *ft=fopen("MyResults.txt","r");
	fscanf(f,"%d",&TasksCount);
	for(j=0; j<TasksCount; j++)
	{
		fscanf(f,"%d",&nc);
		n=(int*)malloc(nc*sizeof(int));
		for(i=0; i<nc; i++)
			fscanf(f,"%d ",&n[i]);
		fscanf(f,"%d",&OperationsCount);
		operations=(char*)malloc(OperationsCount*sizeof(char));
		for(i=0; i<OperationsCount; i++)
			fscanf(f," %c",&operations[i]);
		fscanf(f,"%d",&MaxPressCount);
		fscanf(f," %lld",&rn);
		printf("%d. nc = %d: ",j+1,nc);
		for(i=0; i<nc; i++)
			printf("%d ",n[i]);
		printf("OperationsCount = %d ",OperationsCount);
		for(i=0; i<OperationsCount; i++)
			printf("%c ",operations[i]);
		printf("\nMaxPressCount = %d; rn = %lld; ",MaxPressCount,rn);
		res=GetResult(n,nc,operations,OperationsCount,MaxPressCount+1,rn);
		fscanf(ft,"%d",&RightResult);
		printf("\n		MY RESULT = %d; REQUIRED RESULT = %d",res,RightResult);
		printf("\n================================================================\n");
		free(n);
		free(operations);
	}
	fclose(f);
	fclose(ft);
	return 0;
}
