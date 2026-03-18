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
cpc - текущее кол-во нажатий;
mpc - текущее минимальное кол-во нажатий;
rn - число, которое нужно набрать;
max - максимум для операций деления и отнимания;
*c - все предыдущие результаты для ускорения работы и избежания полного перебора.
Переменные, содержащие данные о том, как был получен результат:
oprnds - все числа, с помощью которых получен результат;
oprs - символы арифметических операций;*/
int calc(char *op,int oc,int cpc,int mpc,unsigned long long rn,unsigned long long max,int *c,unsigned long long **oprnds,char *oprs)
{	
	unsigned long long i,op1,op2;
	int res=0,j,min=mpc;
	//если результат для данного числа уже был получен, то возвращает его
	if(c[rn]>0)
		return cpc+c[rn]+1;
	//если предыдущий результат равен -1 или текущее кол-во нажатий
	//превышает текущий минимум, то возвращаем -1
	if(c[rn]==-1 || cpc>mpc)
		return -1;
	for(i=rn-1; i>0; i--)	
		if(c[i]>0) //если число уже было получено
			for(j=0; j<oc; j++)
			{
				if(op[j]=='+')
					res=calc(op,oc,cpc+c[i]+1,mpc,rn-i,max,c,oprnds,oprs);
				else
					if(op[j]=='*' && rn%i==0)
						//макс. кол-во нажатий mpc-cpc-c[i] выбрано случайно
						res=calc(op,oc,cpc+c[i]+1,mpc-cpc-c[i],rn/i,max,c,oprnds,oprs);
				if(res>0 && res<min)
				{
					min=res;
					//сохранение "пути" к результату
					op1=i;
					oprs[rn]=op[j];
					if(op[j]=='+')
						op2=rn-i;
					else
						op2=rn/i;
				}
			}
	for(i=max-1; i>0; i--)
		if(c[i]>0)
			for(j=0; j<oc; j++)
			{
				if(op[j]=='-' && i+rn<max)
					//макс. кол-во нажатий mpc-cpc-c[i] выбрано случайно
					res=calc(op,oc,cpc+c[i]+1,mpc-cpc-c[i],i+rn,max,c,oprnds,oprs);
				else
					if(op[j]=='/' && i*rn<max)
						//макс. кол-во нажатий mpc-cpc-c[i] выбрано случайно
						res=calc(op,oc,cpc+c[i]+1,mpc-cpc-c[i],i*rn,max,c,oprnds,oprs);
				if(res>0 && res<min)
				{
					min=res;
					//сохранение "пути" к результату
					op2=i;
					oprs[rn]=op[j];
					if(op[j]=='-')
						op1=i+rn;
					else
						if(op[j]=='/')
							op1=i*rn;
				}
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
	int *k,*n,res;
	char *oprs;
	//если есть операции деления или отнимания, нужен разумный предел,
	//так как выполняем обратные действия
	for(i=0; i<oc; i++)
		if(op[i]=='-' || op[i]=='/')
		{
			max=GetMaxForDivAndMinus(rn)+1;
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
		res=calc(op,oc,0,mpc,rn,max,n,oprnds,oprs);
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
	free(n);
	free(k);
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
		res=GetResult(n,nc,operations,OperationsCount,MaxPressCount+1,rn);
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