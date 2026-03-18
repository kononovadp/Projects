/*Розробити функцію, яка визначає кількість надпростих чисел в натуральному ряді. Функція приймає на вхід натуральне число не більше 1000. Надпростим називається число, якщо воно є простим та число, яке отримане з нього записом цифр у зворотному порядку, теж є простим.*/
class program
{
	private static int GetRandomNumber(int min, int max)
	{
		return (int) ((Math.random() * (max - min)) + min);
	}
	private static int RevertNumber(int n)
	{
		int result=0;
		while(n>0)
		{
			result=result*10+n%10;
			n/=10;
		}
		return result;
	}
	private static char IsNumberPrime(int n)
	{
		for(int i=2; i<=n/2; i++)
			if(n%i==0)
				return 0;
		return 1;
	}
	private static int GetCountOfSuperPrimeNumbers(int[] numbers, int count)
	{
		int CountOfSuperPrimeNumbers=0;
		for(int i=0; i<count; i++)
		{
			if(IsNumberPrime(numbers[i])==1 && IsNumberPrime(RevertNumber(numbers[i]))==1)
			{
				CountOfSuperPrimeNumbers++;
				System.out.print(CountOfSuperPrimeNumbers+". The number "+numbers[i]+" is super prime\n");
			}
		}
		return CountOfSuperPrimeNumbers;
	}
	public static void main(String args [])
	{
		int ArraySize=1000;
		int[] arr = new int[ArraySize];
		for(int i=0; i<ArraySize; i++)
			arr[i]=GetRandomNumber(2,1000);
		int CountOfSuperPrimeNumbers=GetCountOfSuperPrimeNumbers(arr,ArraySize);
		System.out.print("----------------------------------------------------------\nCount of super prime numbers: "+CountOfSuperPrimeNumbers);
    }
}