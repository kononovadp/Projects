/*Создать Console-приложение:
Реализовать методы и свойства по вариантам (номер варианта соответствует номеру списка группы. Если номер в списке - 16, берем вариант 1, 17 – 2 и т.д.). Для всех вариантов обязательными методами есть Read, ReadLine, ReadKey, Write(). Вариант 8: Beep, BackgroundColor*/
using System;
namespace lab2
{
    class Program
    {
		static int GetColor(int ColorsCount)
		{
			int res,parsedResult;
			string str;
			Console.Write("Type a number of the color and press enter: ");
			str=Console.ReadLine();
			int.TryParse(str,out parsedResult);
			while(parsedResult==0)
			{
				Console.Write("type digits only: ");
				str=Console.ReadLine();
				int.TryParse(str,out parsedResult);
			}
			res=Convert.ToInt32(str);
			while(res>ColorsCount || res<0)
			{
				Console.Write("enter correct number between 1 and {0}: ",ColorsCount);
				res=Convert.ToInt32(Console.ReadLine());
			}
			return res;
		}
		static void Main(string[] args)
		{
			int ToneNumber;
			ConsoleKeyInfo ch;
			ConsoleColor[]colors=(ConsoleColor[])ConsoleColor.GetValues(typeof(ConsoleColor));
			var color=Console.BackgroundColor;
			var CurrentColor=color;
			int i,CountOfColors=ConsoleColor.GetNames(typeof(ConsoleColor)).Length;
			do
			{
				Console.Write("\n1. Change text color;\n2. Change background color;\n3. Restore all default colors;\n4. Play beep;\n5. Exit;\nYour choice: ");
				ch=Console.ReadKey();
				while(ch.KeyChar-'0'<1 || ch.KeyChar-'0'>5)
				{
					Console.Write("\npress correct key: ");
					ch=Console.ReadKey();
				}
				switch(ch.KeyChar)
				{
					case '1':
					CurrentColor=Console.ForegroundColor;
					for(i=0; i<CountOfColors; i++)
					{
						if(CurrentColor==colors[i])
							continue;
						Console.ForegroundColor=colors[i];
						Console.Write("\n{0}. The text color is {1};",i,colors[i]);
					}
					Console.ForegroundColor=CurrentColor;
					Console.WriteLine("\n{0}. Not to change the text color",i);
					i=GetColor(CountOfColors);
					if(i<CountOfColors)
						Console.ForegroundColor=colors[i];
					break;
					case '2':
					CurrentColor=Console.BackgroundColor;
					for(i=0; i<CountOfColors; i++)
					{
						if(CurrentColor==colors[i])
							continue;
						Console.BackgroundColor=colors[i];
						Console.Write("\n{0}. The background color is {1};",i,colors[i]);
					}
					Console.BackgroundColor=CurrentColor;
					Console.WriteLine("\n{0}. Not to change the text color",i);
					i=GetColor(CountOfColors);
					if(i<CountOfColors)
						Console.BackgroundColor=colors[i];
					break;
					case '3':
					Console.BackgroundColor=ConsoleColor.Black; 
					Console.ForegroundColor=ConsoleColor.Gray;
					break;
					case '4':
					Console.Write("\n");
					do
					{
						Console.Write("1. Do; 2. Re; 3. Mi; 4. Fa; 5. Sol; 6. La; 7. Si.\nEnter a number of the note or 8 to turn to the main menu: ");
						ToneNumber=Console.Read();
						while(Console.In.Peek()!=-1)
							Console.In.Read();
						while(ToneNumber!='1' && ToneNumber!='2' && ToneNumber!='3' && ToneNumber!='4' && ToneNumber!='5' && ToneNumber!='6' && ToneNumber!='7' && ToneNumber!='8')
						{
							Console.Write("enter correct number between 1 and 8: ");
							ToneNumber=Console.Read();
							while(Console.In.Peek()!=-1)
								Console.In.Read();
						}
						switch(ToneNumber)
						{
							case '1': Console.Beep(1047,100); break;
							case '2': Console.Beep(1175,100); break;
							case '3': Console.Beep(1319,100); break;
							case '4': Console.Beep(1480,100); break;
							case '5': Console.Beep(1661,100); break;
							case '6': Console.Beep(1865,100); break;
							case '7': Console.Beep(1976,100); break;
						}
					}while(ToneNumber!='8');					
					break;
				};
			}while(ch.KeyChar!='5');
        }
    }
}