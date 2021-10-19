/*1) Дан одномерный массив А длиной М<=20. Найти:
- первый максимальный элемент и поменять его местами с первым элементом массива;
- первый максимальный элемент и поменять его местами с аналогичным последним максимальным элементом.
2) Дана действительная квадратная матрица порядка N=12.
- найти произведение элементов, расположенных на побочной диагонали и выше ее.*/
using System;
namespace lab4
{
    class Program
    {
		static void Main(string[] args)
		{
			int[]arr=new int[20];
			int[][]matrix=new int[12][];
			int i,j,temp,FirstMaxIndex,LastMaxIndex;
			ulong product;
			Random rnd=new Random();
			for(i=0,FirstMaxIndex=0; i<20; i++)
			{
				arr[i]=rnd.Next(10);
				Console.Write("{0} ",arr[i]);
				if(arr[i]>arr[FirstMaxIndex])
					FirstMaxIndex=i;
			}
			Console.WriteLine("\nThe first maximum element {0} is under index {1}",arr[FirstMaxIndex],FirstMaxIndex);
			temp=arr[0];
			arr[0]=arr[FirstMaxIndex];
			arr[FirstMaxIndex]=temp;
			Console.WriteLine("The first element of array was replaced with the first maximum element:");
			for(i=0; i<20; i++)
				Console.Write("{0} ",arr[i]);
			for(i=0,LastMaxIndex=0; i<20; i++)
				if(arr[i]==arr[0])
					LastMaxIndex=i;
			Console.WriteLine("\nThe last maximum element {0} is under index {1}",arr[LastMaxIndex],LastMaxIndex);
			temp=arr[0];
			arr[0]=arr[LastMaxIndex];
			arr[LastMaxIndex]=temp;
			Console.WriteLine("\nSquare matrix 12x12 of random numbers:");
			for(i=0; i<12; i++)
			{
				matrix[i]=new int[12];
				for(j=0; j<12; j++)
				{
					matrix[i][j]=rnd.Next(10);
					Console.Write("{0} ",matrix[i][j]);
				}
				Console.Write("\n");
			}
			Console.WriteLine("Numbers of the secondary diagonal and above it:");
			for(i=0,temp=12,product=1; i<12; i++,temp--)
			{
				for(j=0; j<temp; j++)
				{
					Console.Write("{0} ",matrix[i][j]);
					if(matrix[i][j]!=0)
						product*=(ulong)matrix[i][j];						
				}
				Console.Write('\n');
			}
			Console.WriteLine("\nProduct of numbers in the secondary diagonal is {0}\n",product);
        }
    }
}