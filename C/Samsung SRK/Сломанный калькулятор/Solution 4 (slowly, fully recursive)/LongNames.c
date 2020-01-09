#include <stdio.h>
#include <malloc.h>
//ф-я получает кол-во цифр в числе
int GetDigitsCount(unsigned long long number)
{
	int i=0;
	while(number>0)
	{
		number/=10;
		i++;
	}
	return i;
}
//ф-я проверяет, можно ли число набрать без арифметических действий
int CheckNumber(int *digits,int NumbersCount,unsigned long long RequiredNumber)
{
	int i,j,mod,DigitsCount=GetDigitsCount(RequiredNumber);
	char found=1;
	if(RequiredNumber==0)
	{
		for(i=0; i<NumbersCount; i++)
			if(digits[i]==0)
				return 1;
		return -1;
	}
	for(i=0; i<DigitsCount && found==1; i++)
	{
		found=0;
		mod=RequiredNumber%10;
		RequiredNumber/=10;
		for(j=0; j<NumbersCount && found==0; j++)
			if(digits[j]==mod)
				found=1;
	}
	if(found==1)
		return DigitsCount;
	return 0;
}
//ф-я возвращает максимальный предел для операций деления и умножения
unsigned long long GetMaxForDivisionAndSubtraction(unsigned long long RequiredNumber)
{
	unsigned long long max=1;	
	while(RequiredNumber>1)
	{		
		max*=10;
		RequiredNumber/=10;
	}
	return max*10;
}
/*Основная рекурсивная ф-я пересчета. Список переменных:
operations - массив символов арифметических операций;
OperationsCount - кол-во операций;
MaximumPressesCount - максимальное кол-во нажатий;
RequiredNumber - число, которое нужно набрать;
MaxForDivisionAndSubtraction - максимум для операций деления и отнимания;
cache - кэш, который хранит минимальное кол-во нажатий для получения каждого числа;
cache2 - кэш, который хранит текущее кол-во нажатий для получения каждого числа;
PlusMult и MinusDiv - определяют, нужно ли запускать определенный цикл вычислений.
Переменные для сохранения арифметического выражения (пути к результату):
operands - массив, который хранит пару операндов для получения каждого числа;
OperationsForResult - массив символов операций для получения каждого числа.*/
int calc(char *operations,int OperationsCount,int MaximumPressesCount,unsigned long long RequiredNumber,long long MaxForDivisionAndSubtraction,int *cache,int *cache2,char PlusMult,char MinusDiv,unsigned long long **operands,char *OperationsForResult)
{
	int result,j,MininmalPressesCount=MaximumPressesCount;
	unsigned long long i,operand1,operand2;
	//если результат для данного числа уже был получен, то возвращаем его
	if(cache[RequiredNumber]>0)
		return cache[RequiredNumber];
	//если предыдущий результат равен -1 или текущее кол-во нажатий
	//превышает максимум, то возвращаем -1
	if(cache[RequiredNumber]==-1 || cache2[RequiredNumber]>=MaximumPressesCount)
		return -1;
	cache[RequiredNumber]=-1; //чтобы повторно не вызывать ф-ю для этого же числа
	if(PlusMult==1) //если есть операция сложения или умножения
		for(i=RequiredNumber-1; i>0; i--)
			//если число можно набрать на клавиатуре либо оно уже было получено
			if(cache[i]>0)
			{
				cache2[RequiredNumber]=cache2[RequiredNumber]+cache[i]+1;
				result=cache2[RequiredNumber];
				for(j=0; j<OperationsCount; j++)
				{
					if(operations[j]=='+')
						result=cache2[RequiredNumber]+calc(operations,OperationsCount,MaximumPressesCount,RequiredNumber-i,MaxForDivisionAndSubtraction,cache,cache2,PlusMult,MinusDiv,operands,OperationsForResult);
					else
						if(operations[j]=='*' && RequiredNumber%i==0)
							result=cache2[RequiredNumber]+calc(operations,OperationsCount,MaximumPressesCount,RequiredNumber/i,MaxForDivisionAndSubtraction,cache,cache2,PlusMult,MinusDiv,operands,OperationsForResult);
					if(result>cache2[RequiredNumber] && result<MininmalPressesCount)
					{
						MininmalPressesCount=result;
						//сохранение "пути" к результату
						operand1=i;
						OperationsForResult[RequiredNumber]=operations[j];
						if(operations[j]=='+')
							operand2=RequiredNumber-i;
						else
							operand2=RequiredNumber/i;						
					}
				}
				cache2[RequiredNumber]=cache2[RequiredNumber]-cache[i]-1;
			}
	if(MinusDiv==1) //если есть операция отнимания или деления
		for(i=RequiredNumber+1; i<MaxForDivisionAndSubtraction; i++)
			//если число можно набрать на клавиатуре либо оно уже было получено
			if(cache[i]>0)
			{
				cache2[RequiredNumber]=cache2[RequiredNumber]+cache[i]+1;
				result=cache2[RequiredNumber];
				for(j=0; j<OperationsCount; j++)
				{
					if(operations[j]=='-')
						result=cache2[RequiredNumber]+calc(operations,OperationsCount,MaximumPressesCount,i-RequiredNumber,MaxForDivisionAndSubtraction,cache,cache2,PlusMult,MinusDiv,operands,OperationsForResult);
					else
						if(operations[j]=='/' && i%RequiredNumber==0)
							result=cache2[RequiredNumber]+calc(operations,OperationsCount,MaximumPressesCount,i/RequiredNumber,MaxForDivisionAndSubtraction,cache,cache2,PlusMult,MinusDiv,operands,OperationsForResult);
					if(result>cache2[RequiredNumber] && result<MininmalPressesCount)
					{
						MininmalPressesCount=result;
						//сохранение "пути" к результату
						operand1=i;
						OperationsForResult[RequiredNumber]=operations[j];
						if(operations[j]=='-')
							operand2=i-RequiredNumber;
						else
							operand2=i/RequiredNumber;
					}
				}
				cache2[RequiredNumber]=cache2[RequiredNumber]-cache[i]-1;
			}
	//если минимум не поменялся, значит число нельзя набрать
	if(MininmalPressesCount==MaximumPressesCount)
		return cache[RequiredNumber]=-1;
	//иначе сохраняем "путь" к нему и записываем результат в кэш
	operands[RequiredNumber]=(unsigned long long*)calloc(2,sizeof(unsigned long long));
	operands[RequiredNumber][0]=operand1;
	operands[RequiredNumber][1]=operand2;
	return cache[RequiredNumber]=MininmalPressesCount;
}
/*определение приоритета выражения перед выводом на экран
operands - все операнды; operations - символы операций;
NumbersWithDigits - числа, которые можно получить только с помощью заданного набора цифр;
RequiredNumber - число, арифметическое выражение которого нужно вывести*/
void ChoosePriority(unsigned long long **operands,char *operations,int *NumbersWithDigits,unsigned long long RequiredNumber,char *result)
{
	if(NumbersWithDigits[operands[RequiredNumber][0]]==0)
		ChoosePriority(operands,operations,NumbersWithDigits,operands[RequiredNumber][0],result);
	if(NumbersWithDigits[operands[RequiredNumber][1]]==0)
		ChoosePriority(operands,operations,NumbersWithDigits,operands[RequiredNumber][1],result);
	if(operations[RequiredNumber]=='*' || operations[RequiredNumber]=='/')
		*result=1;
}
/*вывод выражения на экран
operands - все операнды, operations - текущая операция;
NumbersWithDigits - числа, которые можно получить только с помощью заданного набора цифр;
RequiredNumber - число, арифметическое выражение которого нужно вывести*/
void ShowExpression(unsigned long long **operands,char *operations,int *NumbersWithDigits,unsigned long long RequiredNumber)
{
	unsigned long long t;
	char priority=0;
	//если второй операнд "составной", выясняем, использовались ли для его получения
	//операции умножения или деления. Если использовались, выводим сначала его.
	if(NumbersWithDigits[operands[RequiredNumber][1]]==0)
	{
		ChoosePriority(operands,operations,NumbersWithDigits,operands[RequiredNumber][1],&priority);
		if(priority==1)
		{
			t=operands[RequiredNumber][1];
			operands[RequiredNumber][1]=operands[RequiredNumber][0];
			operands[RequiredNumber][0]=t;
		}
	}
	if(NumbersWithDigits[operands[RequiredNumber][0]]==0)
		ShowExpression(operands,operations,NumbersWithDigits,operands[RequiredNumber][0]);
	else
		printf("%lld",operands[RequiredNumber][0]);
	putchar(operations[RequiredNumber]);
	if(NumbersWithDigits[operands[RequiredNumber][1]]==0)
		ShowExpression(operands,operations,NumbersWithDigits,operands[RequiredNumber][1]);
	else
		printf("%lld",operands[RequiredNumber][1]);
}
int GetResult(int *digits,int DigitsCount,char *operations,int OperationsCount,int MaximumPressesCount,unsigned long long RequiredNumber)
{
	int *NumbersWithDigits,j,*cache,*cache2,result,OperationsCountForResult=0;
	unsigned long long i,**operands,MaxForDivisionAndSubtraction=RequiredNumber+1;
	char *OperationsForResult,PlusMult=0,MinusDiv=0;
	for(j=0; j<OperationsCount; j++)
		if(operations[j]=='-' || operations[j]=='/')
			MinusDiv=1;
		else
			if(operations[j]=='+' || operations[j]=='*')
				PlusMult=1;
	//если есть операции деления или отнимания, нужен разумный предел,
	//так как выполняем обратные действия
	if(MinusDiv==1)
		MaxForDivisionAndSubtraction=GetMaxForDivisionAndSubtraction(RequiredNumber)+1;
	//формируем список чисел, которые можно набрать, не выполняя 
	//арифметические действия
	cache=(int*)calloc(MaxForDivisionAndSubtraction,sizeof(int));
	cache2=(int*)calloc(MaxForDivisionAndSubtraction,sizeof(int));
	NumbersWithDigits=(int*)calloc(MaxForDivisionAndSubtraction,sizeof(int));	
	for(i=0; i<MaxForDivisionAndSubtraction; i++)
	{
		cache[i]=CheckNumber(digits,DigitsCount,i);
		NumbersWithDigits[i]=cache[i];
	}
	if(cache[RequiredNumber]>0)
	{
		printf("\n%lld",RequiredNumber);
		result=cache[RequiredNumber];
	}
	else
	{
		operands=(unsigned long long**)calloc(MaxForDivisionAndSubtraction,sizeof(unsigned long long*));
		OperationsForResult=(char*)calloc(MaxForDivisionAndSubtraction,sizeof(char));
		for(i=1; i<=RequiredNumber; i++)
			if(cache[i]==0)
				cache[i]=calc(operations,OperationsCount,MaximumPressesCount,i,MaxForDivisionAndSubtraction,cache,cache2,PlusMult,MinusDiv,operands,OperationsForResult);
		result=cache[RequiredNumber];
		//если результат получен, прибавляем знак "равно"
		if(result>0)
			result++;
		if(result==MaximumPressesCount)
			result=-1;		
		if(result>0)
		{
			putchar('\n');
			ShowExpression(operands,OperationsForResult,NumbersWithDigits,RequiredNumber);
			printf("=%lld",RequiredNumber);			
		}
		for(i=0; i<MaxForDivisionAndSubtraction; i++)
			if(operands[i]!=NULL)
				free(operands[i]);
		free(operands);
		free(OperationsForResult);
	}
	free(cache);
	free(NumbersWithDigits);		
	return result;
}
int main(void)
{
	int i,j,DigitsCount,OperationsCount,MaximumPressesCount,RightResult,result,*digits,TasksCount=0;
	unsigned long long RequiredNumber;
	char *operations;
	FILE *InputFile=fopen("tests-input.txt","r");
	FILE *OutputFile=fopen("MyResults.txt","r");
	fscanf(InputFile,"%d",&TasksCount);
	for(j=0; j<TasksCount; j++)
	{
		fscanf(InputFile,"%d",&DigitsCount);
		digits=(int*)malloc(DigitsCount*sizeof(int));
		for(i=0; i<DigitsCount; i++)
			fscanf(InputFile,"%d ",&digits[i]);
		fscanf(InputFile,"%d",&OperationsCount);
		operations=(char*)malloc(OperationsCount*sizeof(char));
		for(i=0; i<OperationsCount; i++)
			fscanf(InputFile," %c",&operations[i]);
		fscanf(InputFile,"%d",&MaximumPressesCount);
		fscanf(InputFile," %lld",&RequiredNumber);
		printf("%d. DigitsCount = %d: ",j+1,DigitsCount);
		for(i=0; i<DigitsCount; i++)
			printf("%d ",digits[i]);
		printf("OperationsCount = %d ",OperationsCount);
		for(i=0; i<OperationsCount; i++)
			printf("%c ",operations[i]);
		printf("\nMaxPressCount = %d; RequiredNumber = %lld; ",MaximumPressesCount,RequiredNumber);
		result=GetResult(digits,DigitsCount,operations,OperationsCount,MaximumPressesCount+1,RequiredNumber);
		fscanf(OutputFile,"%d",&RightResult);
		printf("\n		MY RESULT = %d; REQUIRED RESULT = %d",result,RightResult);
		printf("\n================================================================\n");
		free(digits);
		free(operations);
	}
	fclose(InputFile);
	fclose(OutputFile);
	return 0;
}
