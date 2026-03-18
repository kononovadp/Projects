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
//ф-я ищет в таблице результат деления путем умножения
//c - cache; max - size; rn - RequiredNumber
int GetDivRes(int *c,unsigned long long max,unsigned long long rn,unsigned long long *op1,unsigned long long *op2)
{
	unsigned long long i;
	for(i=1; i<max; i++)
		if(c[i]>0 && c[rn*i]>0)
		{
			*op1=i;
			*op2=rn*i;
			return c[i]+c[rn*i]+2;
		}
	return 0;
}
//ф-я ищет в таблице результат отнимания путем сложения
//c - cache; max - size; rn - RequiredNumber
int GetMinusRes(int *c,unsigned long long max,unsigned long long rn,unsigned long long *op1,unsigned long long *op2)
{
	unsigned long long i;
	for(i=1; i<max; i++)
		if(c[i]>0 && c[rn+i]>0)
		{
			*op1=i;
			*op2=rn+i;
			return c[i]+c[rn+i]+2;
		}
	return 0;
}
/*ф-я выполняет операции отнимания или деления за минимальное количество 
шагов (похожа на основную следующую ф-ю)
kn - массив чисел на клавиатуре;
kc - кол-во доступных чисел на клавиатуре;
op - массив символов арифметических операций;
oc - кол-во операций;
cpc - текущее кол-во нажатий;
min - текущее минимальное кол-во нажатий;
rn - число, которое нужно набрать;
max - максимум для операций деления и отнимания;
c - все предыдущие результаты для избежания полного перебора.
Переменные, содержащие данные о том, как был получен результат:
k - числа, которые можно набрать без арифметических операций;
oprnds - все числа, с помощью которых получен результат;
oprs - операции, с помощью которых получен результат;
opc - кол-во операций, с помощью которых получен результат.*/
int DivAndMinus(int *kn,int kc,char *op,int oc,int cpc,int mpc,unsigned long long rn,unsigned long long max,int *c,int *k,unsigned long long *oprnds,char *oprs,int *opc)
{	
	unsigned long long op1,op2,op3,op4;
	int i,res=0,min=mpc;
	char charop;
	//если результат для данного числа уже был получен, то возвращаем его
	if(c[rn]>0)
		return cpc=cpc+c[rn]+1;
	//если предыдущий результат равен -1 или текущее кол-во нажатий
	//превышает текущий минимум, то возвращаем -1
	if(c[rn]==-1 || cpc>mpc)
		return -1;
	
	for(i=0; i<oc; i++)
	{
		res=0;
		if(op[i]=='/')
			res=GetDivRes(c,max/rn,rn,&op1,&op2);
		else
			if(op[i]=='-')
				res=GetMinusRes(c,max-rn,rn,&op3,&op4);
		if(res>0)
		{
			res=res+cpc;
			if(res<min)
			{
				min=res;
				charop=op[i];
				if(op[i]=='-')
				{
					op1=op3;
					op2=op4;
				}
			}
		}
	}	
	//если минимум не поменялся, значит число нельзя набрать
	if(min==mpc)
		return c[rn]=-1;
	//иначе сохраняем "путь" к нему и записываем результат в кэш
	if(k[op2]>0 && k[op1]>0)
	{
		*opc=1;
		oprnds[0]=op2;
		oprnds[1]=op1;
		oprs[0]=charop;		
	}
	else
	{
		oprnds[*opc+1]=op1;
		oprs[*opc]=charop;
		*opc=*opc+1;
	}
	return c[rn]=min;
}
/*основная рекурсивная ф-я пересчета. Список переменных:
kn - массив чисел на клавиатуре; kc - кол-во доступных чисел на клавиатуре;
op - массив символов арифметических операций; oc - кол-во операций;
cpc - текущее кол-во нажатий; min - текущее минимальное кол-во нажатий;
rn - число, которое нужно набрать;
max - максимум для операций деления и отнимания; *c - все предыдущие 
результаты для ускорения работы и избежания полного перебора.
Переменные, содержащие данные о том, как был получен результат:
k - все числа, которые можно получить только с помощью клавиатуры; oprnds - все числа, с помощью которых получен результат; oprs - символы арифметических операций; opc - кол-во операций.*/
int calc(int *kn,int kc,char *op,int oc,int cpc,int min,unsigned long long rn,unsigned long long max,int *c,int *k,unsigned long long *oprnds,char *oprs,int *opc)
{
	unsigned long long i,res=0,op1,op2;
	int prevmin=min;
	char j,charop;
	//если результат для данного числа уже был получен, то возвращаем его
	if(c[rn]>0)
		return cpc+c[rn]+1;
	//если предыдущий результат равен -1 или текущее кол-во нажатий
	//превышает текущий минимум, то возвращаем -1
	if(c[rn]==-1 || cpc>min)
		return -1;
	
	for(i=rn-1; i>0; i--)
	//если число уже было получено
		if(c[i]>0)
			for(j=0; j<oc; j++)
			{
				//для результатов операций + и * вызываем эту же функцию
				if(op[j]=='+')
					res=calc(kn,kc,op,oc,cpc+c[i]+1,min,rn-i,max,c,k,oprnds,oprs,opc);
				else
					if(op[j]=='*' && rn%i==0)
						res=calc(kn,kc,op,oc,cpc+c[i]+1,min,rn/i,max,c,k,oprnds,oprs,opc);
					else
					//результаты деления и отнимания получаем с помощью
					//другой похожей нерекурсивной ф-и
						if(op[j]=='-' && rn+i<max)
							res=DivAndMinus(kn,kc,op,oc,cpc+c[i]+1,min,rn+i,max,c,k,oprnds,oprs,opc);
						else
							if(op[j]=='/' && rn*i<max)
								res=DivAndMinus(kn,kc,op,oc,cpc+c[i]+1,min,rn*i,max,c,k,oprnds,oprs,opc);
				if(res>0 && res<min)
				{
					min=res;
					//сохранение "пути" к результату
					op1=i;
					charop=op[j];
					if(op[j]=='+')
						op2=rn-i;
					else
						if(op[j]=='*')
							op2=rn/i;
						else
							if(op[j]=='-')
								op2=rn+i;
							else
								if(op[j]=='/')
									op2=rn*i;	
				}
			}
	//если минимум не поменялся, значит число нельзя набрать
	if(min==prevmin)
		return c[rn]=-1;
	//иначе сохраняем "путь" к нему и записываем результат в кэш
	if(k[op1]>0 && k[op2]>0)
	{
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
	return c[rn]=min;
}
int GetResult(int *ds,int dc,char *op,int oc,int mpc,unsigned long long rn)
{
	unsigned long long i,*oprnds,max=rn+1;
	int *k,*n,res,opc=0;
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
		oprnds=(unsigned long long*)malloc(mpc*sizeof(unsigned long long));
		oprs=(char*)malloc(mpc*sizeof(char));
		if(rn<ds[0])
			res=DivAndMinus(ds,dc,op,oc,0,mpc+1,rn,max,n,k,oprnds,oprs,&opc);
		else
			res=calc(ds,dc,op,oc,0,mpc+1,rn,max,n,k,oprnds,oprs,&opc);
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
	int i,j,nc,OperationsCount,MaxPressCount,*n,RightResult,TasksCount=0;
	unsigned long long res,rn;
	char *operations;
	FILE *f=fopen("tests-input.txt","r");
	FILE *ft=fopen("correct-output.txt","r");
	FILE *mr=fopen("MyResults.txt","w");
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
		fprintf(mr,"%d\n",res);
		fscanf(ft,"%d",&RightResult);
		printf("\n		MY RESULT = %lld; REQUIRED RESULT = %d",res,RightResult);
		printf("\n================================================================\n");
		free(n);
		free(operations);
	}
	fclose(f);
	fclose(ft);
	fclose(mr);
	printf("File MyResults.txt created");
	return 0;
}