import java.util.*;
import java.io.File;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
class translate
{	
	public static void main(String args [])throws IOException
	{		
		HashMap<String,String> dictionary=new HashMap<>();
		dictionary.put("Я","I");
		dictionary.put("вчора","yesterday");
		dictionary.put("був","was");
		dictionary.put("у","in");
		dictionary.put("місті","city");
		System.out.println(dictionary.get("був"));
	}
}