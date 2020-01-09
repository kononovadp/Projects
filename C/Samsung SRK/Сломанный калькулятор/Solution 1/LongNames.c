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
//ф-я пытается отыскать в таблице результат деления путем умножения
int GetDivisionResult(int *cache,unsigned long long max,unsigned long long RequiredNumber,unsigned long long *operand1,unsigned long long *operand2)
{
	unsigned long long i;
	for(i=1; i<max; i++)
		if(cache[i]>0 && cache[RequiredNumber*i]>0)
		{
			*operand1=i;
			*operand2=RequiredNumber*i;
			return cache[i]+cache[RequiredNumber*i]+2;
		}
	return 0;
}
//ф-я пытается отыскать в таблице результат отнимания путем сложения
int GetSubtractionResult(int *cache,unsigned long long max,unsigned long long RequiredNumber,unsigned long long *operand1,unsigned long long *operand2)
{
	unsigned long long i;
	for(i=1; i<max; i++)
		if(cache[i]>0 && cache[RequiredNumber+i]>0)
		{
			*operand1=i;
			*operand2=RequiredNumber+i;
			return cache[i]+cache[RequiredNumber+i]+2;
		}
	return 0;
}
/*ф-я выполняет операции отнимания или деления за минимальное количество 
шагов (похожа на основную следующую ф-ю)
digits - массив чисел на клавиатуре;
DigitsCount - кол-во доступных чисел на клавиатуре;
operations - массив символов арифметических операций;
OperationsCount - кол-во операций;
CurrentPressesCount - текущее кол-во нажатий;
MininmalPressesCount - текущее минимальное кол-во нажатий;
RequiredNumber - число, которое нужно набрать;
MaxForDivAndMinus - максимум для операций деления и отнимания;
cache - все предыдущие результаты избежания полного перебора.
Переменные, содержащие данные о том, как был получен результат:
KeyboardNumbers - числа, которые можно набрать без арифметических операций;
operands - числа, с помощью которых получен результат;
OperationsForResult - операции, с помощью которых получен результат;
OperationsCountForResult - кол-во операций, с помощью которых получен результат.*/
int DivisionAndSubtraction(int *digits,int DigitsCount,char *operations,int OperationsCount,int CurrentPressesCount,int MininmalPressesCount,unsigned long long RequiredNumber,unsigned long long MaxForDivisionAndSubtraction,int *cache,int *NumbersWithDigits,unsigned long long *operands,char *OperationsForResult,int *OperationsCountForResult)
{	
	int i,result=0,PreviousMininmalPressesCount=MininmalPressesCount;
	unsigned long long operand1,operand2,operand3,operand4;
	char operation;	
	//если результат для данного числа уже был получен, то возвращаем его
	if(cache[RequiredNumber]>0)
		return CurrentPressesCount+cache[RequiredNumber]+1;
	//если предыдущий результат равен -1 или текущее кол-во нажатий
	//превышает текущий минимум, то возвращаем -1
	if(cache[RequiredNumber]==-1 || CurrentPressesCount>MininmalPressesCount)
		return -1;
	for(i=0; i<OperationsCount; i++)
	{
		result=0;
		if(operations[i]=='/')
			result=GetDivisionResult(cache,MaxForDivisionAndSubtraction/RequiredNumber,RequiredNumber,&operand1,&operand2);
		else
			if(operations[i]=='-')
				result=GetSubtractionResult(cache,MaxForDivisionAndSubtraction-RequiredNumber,RequiredNumber,&operand3,&operand4);
		if(result>0)
		{
			result=result+CurrentPressesCount;
			if(result<MininmalPressesCount)
			{
				MininmalPressesCount=result;
				operation=operations[i];
				if(operations[i]=='-')
				{
					operand1=operand3;
					operand2=operand4;
				}
			}
		}
	}
		
	if(MininmalPressesCount==PreviousMininmalPressesCount)
		return cache[RequiredNumber]=-1;
	//сохранение чисел, с помощью которых получен результат
	if(NumbersWithDigits[operand2]>0 && NumbersWithDigits[operand1]>0)
	{
		operands[0]=operand2;
		operands[1]=operand1;
		OperationsForResult[0]=operation;
		*OperationsCountForResult=1;
	}
	else
	{
		operands[*OperationsCountForResult+1]=operand1;
		OperationsForResult[*OperationsCountForResult]=operation;
		*OperationsCountForResult=*OperationsCountForResult+1;
	}
	return cache[RequiredNumber]=MininmalPressesCount;
}
/*основная рекурсивная ф-я пересчета. Список переменных:
digits - массив чисел на клавиатуре;
DigitsCount - кол-во доступных чисел на клавиатуре;
operations - массив символов арифметических операций;
OperationsCount - кол-во операций;
CurrentPressesCount - текущее кол-во нажатий;
MininmalPressesCount - текущее минимальное кол-во нажатий;
RequiredNumber - число, которое нужно набрать;
MaxForDivisionAndSubtraction - максимум для операций деления и отнимания;
*cache - все предыдущие результаты для избежания полного перебора;
KeyboardNumbers - числа, которые можно набрать без арифметических операций;
operands - числа, с помощью которых получен результат;
OperationsForResult - операции, с помощью которых получен результат;
OperationsCountForResult - кол-во операций, с помощью которых получен результат*/
int calc(int *digits,int DigitsCount,char *operations,int OperationsCount,int CurrentPressesCount,int MininmalPressesCount,unsigned long long RequiredNumber,long long MaxForDivisionAndSubtraction,int *cache,int *NumbersWithDigits,unsigned long long *operands,char *OperationsForResult,int *OperationsCountForResult)
{
	int result=0,DivideResult,MinusResult,j,operation,PreviousMininmalPressesCount=MininmalPressesCount;
	unsigned long long i,operand1,operand2;	
	//если результат для данного числа уже был получен, то возвращаем его
	if(cache[RequiredNumber]>0)
		return CurrentPressesCount+cache[RequiredNumber]+1;
	//если предыдущий результат равен -1 или текущее кол-во нажатий
	//превышает текущий минимум, то возвращаем -1
	if(cache[RequiredNumber]==-1 || CurrentPressesCount>MininmalPressesCount)
		return -1;
	for(i=RequiredNumber-1; i>0; i--)
		//если число можно набрать на клавиатуре либо оно уже было получено
		if(cache[i]>0)
			for(j=0; j<OperationsCount; j++)
			{
				//для результатов операций + и * вызываем эту же функцию
				if(operations[j]=='+' && i<RequiredNumber)
					result=calc(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+cache[i]+1,MininmalPressesCount,RequiredNumber-i,MaxForDivisionAndSubtraction,cache,NumbersWithDigits,operands,OperationsForResult,OperationsCountForResult);
				else
					if(operations[j]=='*' && RequiredNumber%i==0)
						result=calc(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+cache[i]+1,MininmalPressesCount,RequiredNumber/i,MaxForDivisionAndSubtraction,cache,NumbersWithDigits,operands,OperationsForResult,OperationsCountForResult);
					else
						//результаты деления и отнимания получаем с помощью
						//другой похожей нерекурсивной ф-и
						if(operations[j]=='/' && RequiredNumber*i<MaxForDivisionAndSubtraction)
							result=DivisionAndSubtraction(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+cache[i]+1,MininmalPressesCount,RequiredNumber*i,MaxForDivisionAndSubtraction,cache,NumbersWithDigits,operands,OperationsForResult,OperationsCountForResult);
						else
							if(operations[j]=='-' && RequiredNumber+i<MaxForDivisionAndSubtraction)
								result=DivisionAndSubtraction(digits,DigitsCount,operations,OperationsCount,CurrentPressesCount+cache[i]+1,MininmalPressesCount,RequiredNumber+i,MaxForDivisionAndSubtraction,cache,NumbersWithDigits,operands,OperationsForResult,OperationsCountForResult);
				if(result>0 && result<MininmalPressesCount)
				{
					MininmalPressesCount=result;
					//сохранение "пути" к результату
					operand1=i;
					operation=operations[j];
					if(operations[j]=='+')
						operand2=RequiredNumber-i;
					else
						if(operations[j]=='-')
							operand2=RequiredNumber+i;
						else
							if(operations[j]=='*')
								operand2=RequiredNumber/i;
							else
								operand2=RequiredNumber*i;
				}
			}
	//если минимум для данного числа не поменялся, в кэш записываем -1
	if(MininmalPressesCount==PreviousMininmalPressesCount)
		return cache[RequiredNumber]=-1;
	//сохранение чисел, с помощью которых получен результат
	if(NumbersWithDigits[operand2]>0 && NumbersWithDigits[operand1]>0)
	{
		operands[0]=operand2;
		operands[1]=operand1;
		OperationsForResult[0]=operation;
		*OperationsCountForResult=1;
	}
	else
	{
		operands[*OperationsCountForResult+1]=operand1;
		OperationsForResult[*OperationsCountForResult]=operation;
		*OperationsCountForResult=*OperationsCountForResult+1;
	}
	return cache[RequiredNumber]=MininmalPressesCount;
}
int GetResult(int *digits,int DigitsCount,char *operations,int OperationsCount,int MaximumPressesCount,unsigned long long RequiredNumber)
{
	int *NumbersWithDigits,*cache,result,OperationsCountForResult=0;
	unsigned long long i,*operands,MaxForDivisionAndSubtraction=RequiredNumber+1;
	char *OperationsForResult;
	for(i=0; i<OperationsCount; i++)
		if(operations[i]=='-' || operations[i]=='/')
		{
			MaxForDivisionAndSubtraction=GetMaxForDivisionAndSubtraction(RequiredNumber)+1;
			break;
		}		
	//формируем список чисел, которые можно набрать, не выполняя 
	//арифметические действия
	cache=(int*)calloc(MaxForDivisionAndSubtraction,sizeof(int));
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
		operands=(unsigned long long*)malloc(MaximumPressesCount*sizeof(unsigned long long));
		OperationsForResult=(char*)malloc(MaximumPressesCount*sizeof(char));
		if(RequiredNumber<digits[0])
			result=DivisionAndSubtraction(digits,DigitsCount,operations,OperationsCount,0,MaximumPressesCount+1,RequiredNumber,MaxForDivisionAndSubtraction,cache,NumbersWithDigits,operands,OperationsForResult,&OperationsCountForResult);
		else
			result=calc(digits,DigitsCount,operations,OperationsCount,0,MaximumPressesCount+1,RequiredNumber,MaxForDivisionAndSubtraction,cache,NumbersWithDigits,operands,OperationsForResult,&OperationsCountForResult);
		if(result>0)
		{
			putchar('\n');
			for(i=0; i<OperationsCountForResult; i++)
				printf("%lld%c",operands[i],OperationsForResult[i]);
			printf("%lld=%lld",operands[i],RequiredNumber);
		}
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
	FILE *OutputFile=fopen("MyResults.txt","w");
	FILE *RequiredResultsFile=fopen("correct-output.txt","r");	
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
		result=GetResult(digits,DigitsCount,operations,OperationsCount,MaximumPressesCount,RequiredNumber);
		fprintf(OutputFile,"%d\n",result);
		fscanf(RequiredResultsFile,"%d",&RightResult);
		printf("\n		MY RESULT = %d; REQUIRED RESULT = %d",result,RightResult);
		printf("\n================================================================\n");
		free(digits);
		free(operations);
	}
	fclose(InputFile);
	fclose(OutputFile);
	fclose(RequiredResultsFile);
	printf("File MyResults.txt created");
	return 0;
}