/*1) Дан одномерный массив А длиной М<=20. Найти:
- первый максимальный элемент и поменять его местами с первым элементом массива;
- первый максимальный элемент и поменять его местами с аналогичным последним максимальным элементом.
2) Дана действительная квадратная матрица порядка N=12.
- найти произведение элементов, расположенных на побочной диагонали и выше ее.*/
using System;
using System.IO;
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
			StreamReader sr=new StreamReader("numbers.txt");
			StreamWriter sw=new StreamWriter("results.txt");
			string line=sr.ReadLine();
			string[]numbers=line.Split(' ');
			sw.WriteLine("Array from the file numbers.txt:");
			for(i=0,FirstMaxIndex=0; i<20; i++)
			{
				arr[i]=Int32.Parse(numbers[i]);
				sw.Write("{0} ",arr[i]);
				if(arr[i]>arr[FirstMaxIndex])
					FirstMaxIndex=i;
			}
			sr.ReadLine();			
			sw.WriteLine("\r\nThe first maximum element {0} is under index {1}",arr[FirstMaxIndex],FirstMaxIndex);
			temp=arr[0];
			arr[0]=arr[FirstMaxIndex];
			arr[FirstMaxIndex]=temp;
			sw.WriteLine("The first element of array was replaced with the first maximum element:");
			for(i=0; i<20; i++)
				sw.Write("{0} ",arr[i]);
			for(i=0,LastMaxIndex=0; i<20; i++)
				if(arr[i]==arr[0])
					LastMaxIndex=i;
			sw.WriteLine("\r\nThe last maximum element {0} is under index {1}",arr[LastMaxIndex],LastMaxIndex);
			temp=arr[0];
			arr[0]=arr[LastMaxIndex];
			arr[LastMaxIndex]=temp;
			sw.WriteLine("\r\nSquare matrix 12x12 of from the file numbers.txt:");
			for(i=0; i<12; i++)
			{
				matrix[i]=new int[12];
				line=sr.ReadLine();
				numbers=line.Split(' ');
				for(j=0; j<12; j++)
				{
					matrix[i][j]=Int32.Parse(numbers[j]);
					sw.Write("{0} ",matrix[i][j]);
				}
				sw.Write("\r\n");
			}
			sr.Close();
			sw.WriteLine("Numbers of the secondary diagonal and above it:");
			for(i=0,temp=12,product=1; i<12; i++,temp--)
			{
				for(j=0; j<temp; j++)
				{
					sw.Write("{0} ",matrix[i][j]);
					if(matrix[i][j]!=0)
						product*=(ulong)matrix[i][j];						
				}
				sw.Write("\r\n");
			}
			sw.WriteLine("\r\nProduct of numbers in the secondary diagonal is {0}\r\n",product);
			sw.Close();
			Console.Write("The file results.txt created.");
        }
    }
}