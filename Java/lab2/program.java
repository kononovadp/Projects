import java.util.*;
import java.io.File;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
class register
{
	public static class student
	{
		String name,surname,PhoneNumber,street,HouseNumber;
		int year,DoorNumber;
		student()
		{
			name="";
			surname="";
			PhoneNumber="";
			street="";
			year=0;
			DoorNumber=0;
		}
	}
	static student[]students;
	static Set<Character> letters,numbers;
	public static String GetField(String line,int MaxSemicolonIndex,Set CharactersKit1,Set CharactersKit2)
	{
		int i,FieldLength,SemicolonIndex=line.indexOf(';');
		if(SemicolonIndex==-1 || SemicolonIndex>MaxSemicolonIndex)
		{
			System.out.print("Incorrect file!");
			return null;
		}
		String field=line.substring(0,SemicolonIndex);
		for(i=0,FieldLength=field.length(); i<FieldLength; i++)
			if(CharactersKit1.contains(field.charAt(i))==false)
			{
				System.out.println("Incorrect field: "+field+"\n");
				return "-1";
			}
			else
				if(CharactersKit2!=null && CharactersKit2.contains(field.charAt(i))==false)
					return "-1";
		return field;
	}
	public static student GetEntity(String line)
	{		
		student NewStudent=new student();
		String surname=GetField(line,20,letters,null);
		if(surname==null)
			return null;		
		else
			if(surname=="-1")
				return NewStudent;
		line=line.substring(line.indexOf(';')+1,line.length());
		String name=GetField(line,20,letters,null);
		if(name==null)
			return null;
		else
			if(name=="-1")
				return NewStudent;			
		line=line.substring(line.indexOf(';')+1,line.length());
		String year=GetField(line,4,numbers,null);
		line=line.substring(line.indexOf(';')+1,line.length());
		String PhoneNumber=GetField(line,10,numbers,null);
		if(PhoneNumber==null)
			return null;
		else
			if(PhoneNumber=="-1")
				return NewStudent;		
		line=line.substring(line.indexOf(';')+1,line.length());
		String street=GetField(line,30,letters,numbers);
		if(street==null)
			return null;
		else
			if(street=="-1")
				return NewStudent;		
		line=line.substring(line.indexOf(';')+1,line.length());
		String HouseNumber=GetField(line,20,numbers,null);
		if(HouseNumber==null)
			return null;
		else
			if(HouseNumber=="-1")
				return NewStudent;			
		line=line.substring(line.indexOf(';')+1,line.length());
		int FieldLength=line.length();
		if(FieldLength>5)
			return null;
		for(int i=0; i<FieldLength; i++)
			if(numbers.contains(line.charAt(i))==false)
				return NewStudent;
		NewStudent.surname=surname;
		NewStudent.name=name;
		NewStudent.year=Integer.valueOf(year);
		NewStudent.PhoneNumber=PhoneNumber;
		NewStudent.street=street;
		NewStudent.HouseNumber=HouseNumber;
		NewStudent.DoorNumber=Integer.valueOf(line);
		return NewStudent;
	}
	public static void main(String args [])throws IOException
	{
		students=new student[1000];
		letters = new HashSet<Character>();
		letters.addAll(Arrays.asList(new Character[]{'А','Б','В','Г','Ґ','Д','Е','Є','Ж','З','И','І','Ї','Й','К','Л','М','Н','О','П','Р','С','Т','У','Ф','Х','Ц','Ч','Ш','Щ','Ь','Ю','Я','а','б','в','г','ґ','д','е','є','ж','з','и','і','ї','й','к','л','м','н','о','п','р','с','т','у','ф','х','ц','ч','ш','щ','ь','ю','я','Ё','ё','Ъ','ъ','Ы','ы','Э','э','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ','-','\'','’'}));
		numbers = new HashSet<Character>();
		numbers.addAll(Arrays.asList(new Character[]{'0','1','2','3','4','5','6','7','8','9'}));
		BufferedReader file = new BufferedReader(new InputStreamReader(new FileInputStream(new File("Студенти.csv")),"Windows-1251"));
		String line;
		student NewStudent;
		int LinesCount=0,StudentsCount=0;
		while((line=file.readLine())!=null)
		{
			LinesCount++;
			NewStudent=GetEntity(line);
			if(NewStudent==null)
				break;
			else
				if(NewStudent.surname.length()==0)
				{
					System.out.println("Line "+LinesCount+" is incorrect!");
					break;
				}
				else
				{					
					students[StudentsCount]=NewStudent;
					StudentsCount++;
				}
		}
		file.close();
	}
}