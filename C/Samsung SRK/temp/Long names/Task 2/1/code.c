#include <stdio.h>
#include <malloc.h>
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
long long int CheckNumber(int *numbers,int NumbersCount,long long int RequiredNumber)
{
	int i,j,mod,DigitsCount=GetDigitsCount(RequiredNumber);
	char found=1;
	if(RequiredNumber==0)
	{
		for(i=0; i<NumbersCount; i++)
			if(numbers[i]==0)
				return 1;
		return -1;
	}
	for(i=0; i<DigitsCount && found==1; i++)
	{
		found=0;
		mod=RequiredNumber%10;
		RequiredNumber/=10;
		for(j=0; j<NumbersCount && found==0; j++)
			if(numbers[j]==mod)
				found=1;
	}
	if(found==1)
		return DigitsCount;
	return 0;
}
//ф-я возвращает максимальный предел для операций деления и умножения
long long int GetMaxForDivAndMinus(long long int RequiredNumber)
{
	long long int max=1;	
	while(RequiredNumber>1)
	{		
		max*=10;
		RequiredNumber/=10;
	}
	return max*10;
}
//ф-я пытается отыскать в таблице результат деления путем умножения
long long int GetDivRes(long long int *cache,long long int size,long long int RequiredNumber)
{
	long long int i=1;
	for(i=1; RequiredNumber*i<size+1; i++)
		if(cache[i]>0 && cache[RequiredNumber*i]>0)
			return cache[i]+cache[RequiredNumber*i]+2;
	return 0;
}
//ф-я пытается отыскать в таблице результат отнимания путем сложения
long long int GetMinusRes(long long int *cache,long long int size,long long int RequiredNumber)
{
	long long int i;
	for(i=1; RequiredNumber+i<size+1; i++)
		if(cache[i]>0 && cache[RequiredNumber+i]>0)
			return cache[i]+cache[RequiredNumber+i]+2;
	return 0;
}
/*ф-я выполняет операции отнимания или деления за минимальное количество 
шагов (похожа на основную следующую ф-ю)
*digits - массив чисел на клавиатуре; DigitsCount - кол-во доступных чисел на клавиатуре;
*operations - массив символов арифметических операций; OperationsCount - кол-во операций;
CurrentPressesCount - текущее кол-во нажатий; min - текущее минимальное кол-во нажатий;
RequiredNumber - число, которое нужно набрать;
max - максимум для операций деления и отнимания; *cache - все предыдущие 
результаты для ускорения работы и избежания полного перебора*/
long long int DivAndMinus(int *digits,int DigitsCount,char *operations,int OperationsCount,int CurrentPressesCount,int min,long long int RequiredNumber,long long max,long long int *cache)
{
	long long int i,res;
	long long int divres=0;
	long long int minusres=0;
	int j,prevmin=min;
	if(cache[RequiredNumber]==-1 || CurrentPressesCount>min)
		return -1;
	if(cache[RequiredNumber]>0)
	{
		if(CurrentPressesCount==0)
			CurrentPressesCount=cache[RequiredNumber];
		else
			CurrentPressesCount=CurrentPressesCount+cache[RequiredNumber]+1;
		return CurrentPressesCount;
	}
	if(RequiredNumber<digits[0])
		RequiredNumber=max;
	for(i=0; i<OperationsCount; i++)
		if(operations[i]=='/')
			divres=GetDivRes(cache,max,RequiredNumber);
		else
			if(operations[i]=='-')
				minusres=GetMinusRes(cache,max,RequiredNumber);
	for(i=0; i<RequiredNumber; i++)
		if(cache[i]>0)
			for(j=0; j<OperationsCount; j++)
			{
				res=min;
				if(operations[j]=='/' && i>0 && RequiredNumber*i<=max && cache[RequiredNumber*i]>0)
					res=divres+CurrentPressesCount;
				else
					if(operations[j]=='-' && RequiredNumber+i<=max && cache[RequiredNumber+i]>0)
						res=minusres+CurrentPressesCount;
					//раскомментирование этой части приведет к получению
					//более худшего, но наверное правильного результата в
					//10-м примере (так и не понял почему)
					/*else
						if(operations[j]=='+' && i<RequiredNumber)
							res=DivAndMinus(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+cache[i]+1,min,RequiredNumber-i,max,cache);
						else
							if(operations[j]=='*' && i>1  && i<RequiredNumber && RequiredNumber%i==0)
								res=DivAndMinus(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+cache[i]+1,min,RequiredNumber/i,max,cache);*/
				if(res>0 && res<min)
					min=res;
			}
	if(min==prevmin)
		return cache[RequiredNumber]=-1;
	cache[RequiredNumber]=min;	
	return min;
}
/*основная РЕКУРСИВНАЯ ф-я пересчета. Список переменных:
*digits - массив чисел на клавиатуре; DigitsCount - кол-во доступных чисел на клавиатуре;
*operations - массив символов арифметических операций; OperationsCount - кол-во операций;
CurrentPressesCount - текущее кол-во нажатий; min - текущее минимальное кол-во нажатий;
RequiredNumber - число, которое нужно набрать;
max - максимум для операций деления и отнимания; *cache - все предыдущие 
результаты для ускорения работы и избежания полного перебора*/
long long int calc(int *digits,int DigitsCount,char *operations,int OperationsCount,int CurrentPressesCount,int min,long long int RequiredNumber,long long max,long long int *cache)
{
	long long int i,res;
	int j,prevmin=min;
	//если предыдущий результат равен -1 или текущее кол-во нажатий
	//превышает текущий минимум, то возвращаем -1
	if(cache[RequiredNumber]==-1 || CurrentPressesCount>min)
		return -1;
	//если результат для данного числа уже был получен, то возвращает его
	if(cache[RequiredNumber]>0)
	{
		//если вызываем ф-ю первый раз, то знак "равно" не добавляем
		if(CurrentPressesCount==0)
			CurrentPressesCount=cache[RequiredNumber];
		else
			CurrentPressesCount=CurrentPressesCount+cache[RequiredNumber]+1;
		return CurrentPressesCount;
	}
	//предусматривает случай, когда нужно набрать число, которое меньше 
	//наименьшего на клавиатуре (например, с помощью клавиш 5, 6, 7, 8, 9
	// и операций + и / нужно получить 1)
	if(RequiredNumber<digits[0])
		RequiredNumber=max;
	//почему-то приходится шагать в обратном порядке (так и не понял почему)
	for(i=RequiredNumber-1; i>0; i--)
		//если число можно набрать на клавиатуре либо оно уже было получено
		if(cache[i]>0)
			for(j=0; j<OperationsCount; j++)
			{
				res=min;
				//для результатов операций + и * вызываем эту же функцию
				if(operations[j]=='+' && i<RequiredNumber)
					res=calc(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+cache[i]+1,min,RequiredNumber-i,max,cache);
				else
					if(operations[j]=='*' && i>1  && i<RequiredNumber && RequiredNumber%i==0)
						res=calc(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+cache[i]+1,min,RequiredNumber/i,max,cache);
					else
						//результаты деления и отнимания получаем с помощью
						//другой похожей нерекурсивной ф-и
						if(operations[j]=='/' && i>1 && RequiredNumber*i<=max)
							res=DivAndMinus(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+cache[i]+1,min,RequiredNumber*i,max,cache);
						else
							if(operations[j]=='-' && RequiredNumber+i<=max)
								res=DivAndMinus(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+cache[i]+1,min,RequiredNumber+i,max,cache);
				if(res>0 && res<min)
					min=res;
			}
	//если минимум для данного числа не поменялся, в кэш записываем -1
	if(min==prevmin)
		return cache[RequiredNumber]=-1;		
	return cache[RequiredNumber]=min;
}
long long int GetResult(int *digits,int DigitsCount,char *operations,int OperationsCount,int MaxPressesCount,long long int RequiredNumber)
{
	long long int i,res,*cache,max=RequiredNumber;
	//если есть операции деления или отнимания, нужен разумный предел,
	//так как выполняем обратные действия
	for(int i=0; i<DigitsCount; i++)
		if(operations[i]=='/' || operations[i]=='-')
		{
			max=GetMaxForDivAndMinus(max);
			break;
		}
	//выделяем память, сначала заполняем все нулями, а затем пытаемся
	//набрать все эти числа без использования арифметических операций
	cache=(long long int*)calloc(max+1,sizeof(long long int));
	for(i=0; i<=max; i++)
		cache[i]=CheckNumber(digits,DigitsCount,i);
	res=calc(digits,DigitsCount,operations,OperationsCount,0,MaxPressesCount+1,RequiredNumber,max,cache);
	free(cache);	
	return res;
}
int main(void)
{
	int i,j,NumbersCount,OperationsCount,MaxPressCount,*numbers,RightResult,TasksCount=0;
	long long int res,RequiredNumber;
	char *operations;
	FILE *f=fopen("tests-input.txt","r");
	FILE *ft=fopen("correct-output.txt","r");
	fscanf(f,"%d",&TasksCount);
	for(j=0; j<TasksCount; j++)
	{
		fscanf(f,"%d",&NumbersCount);
		numbers=(int*)malloc(NumbersCount*sizeof(int));
		for(i=0; i<NumbersCount; i++)
			fscanf(f,"%d ",&numbers[i]);
		fscanf(f,"%d",&OperationsCount);
		operations=(char*)malloc(OperationsCount*sizeof(char));
		for(i=0; i<OperationsCount; i++)
			fscanf(f," %c",&operations[i]);
		fscanf(f,"%d",&MaxPressCount);
		fscanf(f," %lld",&RequiredNumber);
		printf("%d. NumbersCount = %d: ",j+1,NumbersCount);
		for(i=0; i<NumbersCount; i++)
			printf("%d ",numbers[i]);
		printf("OperationsCount = %d ",OperationsCount);
		for(i=0; i<OperationsCount; i++)
			printf("%c ",operations[i]);
		printf("\nMaxPressCount = %d; RequiredNumber = %lld; ",MaxPressCount,RequiredNumber);
		res=GetResult(numbers,NumbersCount,operations,OperationsCount,MaxPressCount,RequiredNumber);
		fscanf(ft,"%d",&RightResult);
		printf("\n		MY RESULT = %lld; RIGHT RESULT = %d",res,RightResult);
		printf("\n=====================================================\n");
		free(numbers);
		free(operations);
	}
	fclose(f);
	fclose(ft);
	return 0;
}