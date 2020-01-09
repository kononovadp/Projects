#include <stdio.h>
#include <malloc.h>
/*5. 6867/7=981 - 7 нажатий вместо 9;
7. 1111-122-2=987 - 11 нажатий вместо 12;
9. 1111-122-2=987 - 11 нажатий вместо 20;
10. моя программа набирает число 987 за 17 нажатий, но вручную мне этот результат получить не удалось (можно выйти на предложенный более худший результат, раскомментировав определенный блок кода).
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
//ф-я проверяет, можно ли число набрать без арифметических действий
//n - numbers; nc - NumbersCount; rn - RequiredNumber
long long int CheckNumber(int *n,int nc,long long int rn)
{
	int i,j,mod,dg=GetDigitsCount(rn); //dg - DigitsCount
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
long long int GetMaxForDivAndMinus(long long int rn) //rn - RequiredNumber
{
	long long int max=1;	
	while(rn>1)
	{		
		max*=10;
		rn/=10;
	}
	return max*10;
}
//ф-я пытается отыскать в таблице результат деления путем умножения
//c - cache; s - size; rn - RequiredNumber
long long int GetDivRes(long long int *c,long long int s,long long int rn)
{
	long long int i=1;
	for(i=1; rn*i<s+1; i++)
		if(c[i]>0 && c[rn*i]>0)
			return c[i]+c[rn*i]+2;
	return 0;
}
//ф-я пытается отыскать в таблице результат отнимания путем сложения
//c - cache; s - size; rn - RequiredNumber
long long int GetMinusRes(long long int *c,long long int s,long long int rn)
{
	long long int i;
	for(i=1; rn+i<s+1; i++)
		if(c[i]>0 && c[rn+i]>0)
			return c[i]+c[rn+i]+2;
	return 0;
}
//ф-я выполняет операции отнимания или деления за минимальное количество 
//шагов (похожа на основную следующую ф-ю)
/*kn - массив чисел на клавиатуре; kc - кол-во доступных чисел на клавиатуре;
*op - массив символов арифметических операций; oc - кол-во операций;
cpc - текущее кол-во нажатий; min - текущее минимальное кол-во нажатий;
rn - число, которое нужно набрать;
max - максимум для операций деления и отнимания; *c - все предыдущие 
результаты для ускорения работы и избежания полного перебора*/
long long int DivAndMinus(int *kn,int kc,char *op,int oc,int cpc,int min,long long int rn,long long max,long long int *c)
{
	long long int i,res;
	long long int divres=0;
	long long int minusres=0;
	int j,prevmin=min;
	if(c[rn]==-1 || cpc>min)
		return -1;
	if(c[rn]>0)
	{
		if(cpc==0)
			cpc=c[rn];
		else
			cpc=cpc+c[rn]+1;
		return cpc;
	}
	if(rn<kn[0])
		rn=max;
	for(i=0; i<oc; i++)
		if(op[i]=='/')
			divres=GetDivRes(c,max,rn);
		else
			if(op[i]=='-')
				minusres=GetMinusRes(c,max,rn);
	for(i=0; i<rn; i++)
		if(c[i]>0)
			for(j=0; j<oc; j++)
			{
				res=min;
				if(op[j]=='/' && i>0 && rn*i<=max && c[rn*i]>0)
					res=divres+cpc;
				else
					if(op[j]=='-' && rn+i<=max && c[rn+i]>0)
						res=minusres+cpc;
					//раскомментирование этой части приведет к получению
					//более худшего, но наверное правильного результата в
					//10-м примере (так и не понял почему)
					/*else
						if(op[j]=='+' && i<rn)
							res=DivAndMinus(kn,kc,op,oc,cpc+c[i]+1,min,rn-i,max,c);
						else
							if(op[j]=='*' && i>1  && i<rn && rn%i==0)
								res=DivAndMinus(kn,kc,op,oc,cpc+c[i]+1,min,rn/i,max,c);*/
				if(res>0 && res<min)
					min=res;
			}
	if(min==prevmin)
		return c[rn]=-1;
	c[rn]=min;	
	return min;
}
/*основная рекурсивная ф-я пересчета. Список переменных:
*kn - массив чисел на клавиатуре; kc - кол-во доступных чисел на клавиатуре;
*op - массив символов арифметических операций; oc - кол-во операций;
cpc - текущее кол-во нажатий; min - текущее минимальное кол-во нажатий;
rn - число, которое нужно набрать;
max - максимум для операций деления и отнимания; *c - все предыдущие 
результаты для ускорения работы и избежания полного перебора*/
long long int calc(int *kn,int kc,char *op,int oc,int cpc,int min,long long int rn,long long max,long long int *c)
{
	long long int i,res;
	int j,prevmin=min;
	//если предыдущий результат равен -1 или текущее кол-во нажатий
	//превышает текущий минимум, то возвращаем -1
	if(c[rn]==-1 || cpc>min)
		return -1;
	//если результат для данного числа уже был получен, то возвращает его
	if(c[rn]>0)
	{
		//если вызываем ф-ю первый раз, то знак "равно" не добавляем
		if(cpc==0)
			cpc=c[rn];
		else
			cpc=cpc+c[rn]+1;
		return cpc;
	}
	//предусматривает случай, когда нужно набрать число, которое меньше 
	//наименьшего на клавиатуре (например, с помощью клавиш 5, 6, 7, 8, 9
	// и операций + и / нужно получить 1)
	if(rn<kn[0])
		rn=max;
	//почему-то приходится шагать в обратном порядке (так и не понял почему)
	for(i=rn-1; i>0; i--)
		//если число можно набрать на клавиатуре либо оно уже было получено
		if(c[i]>0)
			for(j=0; j<oc; j++)
			{
				res=min;
				//для результатов операций + и * вызываем эту же функцию
				if(op[j]=='+' && i<rn)
					res=calc(kn,kc,op,oc,cpc+c[i]+1,min,rn-i,max,c);
				else
					if(op[j]=='*' && i>1  && i<rn && rn%i==0)
						res=calc(kn,kc,op,oc,cpc+c[i]+1,min,rn/i,max,c);
					else
						//результаты деления и отнимания получаем с помощью
						//другой похожей нерекурсивной ф-и
						if(op[j]=='/' && i>1 && rn*i<=max)
							res=DivAndMinus(kn,kc,op,oc,cpc+c[i]+1,min,rn*i,max,c);
						else
							if(op[j]=='-' && rn+i<=max)
								res=DivAndMinus(kn,kc,op,oc,cpc+c[i]+1,min,rn+i,max,c);
				if(res>0 && res<min)
					min=res;
			}
	//если минимум для данного числа не поменялся, в кэш записываем -1
	if(min==prevmin)
		return c[rn]=-1;		
	return c[rn]=min;
}
long long int GetResult(int *kn,int kc,char *op,int oc,int mpc,long long int rn)
{
	long long int i,res,*c,max=rn;
	//если есть операции деления или отнимания, нужен разумный предел,
	//так как выполняем обратные действия
	for(int i=0; i<kc; i++)
		if(op[i]=='/' || op[i]=='-')
		{
			max=GetMaxForDivAndMinus(max);
			break;
		}
	//выделяем память, сначала заполняем все нулями, а затем пытаемся
	//набрать все эти числа без использования арифметических операций
	c=(long long int*)calloc(max+1,sizeof(long long int));
	for(i=0; i<=max; i++)
		c[i]=CheckNumber(kn,kc,i);
	res=calc(kn,kc,op,oc,0,mpc+1,rn,max,c);
	free(c);	
	return res;
}
int main(void)
{
	int i,j,nc,OperationsCount,MaxPressCount,*n,RightResult,TasksCount=0;
	long long int res,rn;
	char *operations;
	FILE *f=fopen("tests-input.txt","r");
	FILE *ft=fopen("correct-output.txt","r");
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
		printf("\n		MY RESULT = %lld; RIGHT RESULT = %d",res,RightResult);
		printf("\n=====================================================\n");
		free(n);
		free(operations);
	}
	fclose(f);
	fclose(ft);
	return 0;
}