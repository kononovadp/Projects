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
/*основная рекурсивная ф-я пересчета. Список переменных:
op - массив символов арифметических операций;
oc - кол-во операций;
mpc - максимальное кол-во нажатий;
rn - число, которое нужно набрать;
max - максимум для операций деления и отнимания;
*c - все предыдущие результаты для ускорения работы и избежания полного перебора;
PlusMult и MinusDiv - определяют, нужно ли запускать определенный цикл вычислений.
Переменные для сохранения арифметического выражения (пути к результату):
oprnds - массив, который хранит пару операндов для получения каждого числа;
oprs - массив, который хранит операции для получения каждого числа.*/
int calc(char *op,int oc,int mpc,unsigned long long rn,unsigned long long max,int *c,char PlusMult,char MinusDiv,unsigned long long **oprnds,char *oprs)
{
	unsigned long long i,or,op1,op2;
	int j,pc,min=mpc;
	if(PlusMult==1) //если есть операция сложения или умножения
		for(i=1; i<rn; i++)
			if(c[i]>0) //если число уже было получено
				for(j=0; j<oc; j++)
				{
					or=0;
					if(op[j]=='+')
						or=rn-i;
					else
						if(op[j]=='*' && rn%i==0)
							or=rn/i;
					//если результат операции больше 0 и он был уже ранее получен
					if(or>0 && c[or]>0)
					{
						pc=c[i]+c[or]+1;
						if(pc<min)
						{
							min=pc;
							//сохранение "пути" к результату
							op1=or;
							op2=i;
							oprs[rn]=op[j];
						}
					}
				}
	if(MinusDiv==1) //если есть операция отнимания или деления
		for(i=rn+1; i<max; i++)
		{
			if(c[i]>0) //если число уже было получено
				for(j=0; j<oc; j++)
				{
					or=0;
					if(op[j]=='-')
						or=i-rn;
					else
						if(op[j]=='/' && i%rn==0)
							or=i/rn;
					if(or>0 && c[or]>0) //если число уже было получено
					{
						pc=c[i]+c[or]+1;
						if(pc<min)
						{							
							min=pc;
							//сохранение "пути" к результату
							op1=i;
							op2=or;
							oprs[rn]=op[j];
							//устраняет некорректность арифметического выражения
							//в некоторых случаях (9-й пример)
							if(oprs[or]=='*')
								oprs[or]='/';
							else
								if(oprs[or]=='+')
									oprs[or]='-';
						}
					}
				}
		}
	//если минимум не поменялся, значит число нельзя набрать
	if(min==mpc)
		return -1;
	//иначе сохраняем "путь" к нему и записываем результат в кэш
	oprnds[rn]=(unsigned long long*)calloc(2,sizeof(unsigned long long));
	oprnds[rn][0]=op1;
	oprnds[rn][1]=op2;
	return min;
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
	int j,*n,*k,res,opc=0;
	char *oprs,PlusMult=0,MinusDiv=0;	
	for(j=0; j<oc; j++)
		if(op[j]=='-' || op[j]=='/')
			MinusDiv=1;
		else
			if(op[j]=='+' || op[j]=='*')
				PlusMult=1;
	//если есть операции деления или отнимания, нужен разумный предел,
	//так как выполняем обратные действия
	for(i=0; i<oc; i++)
		if(op[i]=='-' || op[i]=='/')
		{
			max=GetMaxForDivAndMinus(rn)+1;
			MinusDiv=1;
			break;
		}
	//формируем список чисел, которые можно набрать, не выполняя 
	//арифметические действия
	n=(int*)calloc(max,sizeof(int));
	k=(int*)calloc(max,sizeof(int));
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
		oprnds=(unsigned long long**)calloc(max,sizeof(unsigned long long*));
		oprs=(char*)calloc(max,sizeof(char));
		for(i=1; i<=rn; i++)
			if(n[i]<1)
				n[i]=calc(op,oc,mpc,i,max,n,PlusMult,MinusDiv,oprnds,oprs);
		res=n[rn];
		if(res>=mpc)
			res=-1;
		if(res>0)
		{
			res++;
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
	free(n);
	return res;
}
int main(void)
{
	int i,j,nc,OperationsCount,MaxPressCount,*n,RightResult,TasksCount=0;
	unsigned long long res,rn;
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
		res=GetResult(n,nc,operations,OperationsCount,MaxPressCount,rn);
		fscanf(ft,"%d",&RightResult);
		printf("\n		MY RESULT = %lld; REQUIRED RESULT = %d",res,RightResult);
		printf("\n================================================================\n");
		free(n);
		free(operations);
	}
	fclose(f);
	fclose(ft);
	return 0;
}