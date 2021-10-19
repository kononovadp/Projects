using System;
using System.IO;
namespace CreateFile
{
    class Program
    {
		static void Main(string[] args)
		{
			StreamWriter oda=new StreamWriter("numbers.txt");
			Random rnd=new Random();
			int i,j;
			for(i=0; i<20; i++)
				oda.Write("{0} ",rnd.Next(10));
			oda.Write("\r\n\r\n");
			for(i=0; i<12; i++)
			{
				for(j=0; j<12; j++)
					oda.Write("{0} ",rnd.Next(5));
				oda.WriteLine();
			}
			oda.Close();
			Console.Write("File numbers.txt with random numbers created.");
        }
    }
}