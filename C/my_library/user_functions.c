#include <time.h>
int strtoint(char *s)
{
	int number=0;
	int i,ten=1;
	short sign_minus=0;
	if (s[0]=='-')
	{
		sign_minus=1;
		for (i=0; i<strlen(s)-1; i++)
			s[i]=s[i+1];
		s[strlen(s)-1]=0;
	}
	for(i=1; i<strlen(s); i++)
		ten*=10;
	for(i=0; i<strlen(s); i++)
	{
		number+=ten*(s[i]-48);
		ten/=10;
	}
	if (sign_minus==1)
		number=0-number;
	return number;
}
float strtofloat(char *s)
{
	int i,j,temp_num,point_position=0;
	char temp_str[15]="";
	float ten,number=0;
	short sign_minus=0;	
	for(i=0; i<strlen(s); i++)
		if(s[i]=='.')
			point_position=i;
	if (point_position==0)
		return strtoint(s);
	if (s[0]=='-')
	{
		sign_minus=1;
		point_position--;
		for (i=0; i<strlen(s)-1; i++)
			s[i]=s[i+1];		
		s[strlen(s)-1]=0;
	}
	for(i=0; i<point_position; i++)
		temp_str[i]=s[i];
	number=strtoint(temp_str);
	temp_str[0]=0;	
	for(i=0; i<strlen(s); i++)
		temp_str[i]=s[i+point_position+1];
	temp_num=strtoint(temp_str);
	for(i=0,ten=1; i<strlen(temp_str); i++)
		ten*=10;
	number=number + (temp_num / ten);
	if (sign_minus==1)
		number=0-number;
	return number;
}
char *timetostr(int n)
{
	char res[500],temp[500];
	if(n<60)
	{
		
		_itoa(n,res,10);
		strcat(res," sec.");
		return res;
	}
	else
		if(n<3600)
		{
			_itoa(n/60,res,10);
			strcat(res," min.");
			if(n%60>0)
			{
				strcat(res," ");
				_itoa(n%60,temp,10);
				strcat(res,temp);
				strcat(res," sec.");
			}
			return res;
		}
		else
		{
			_itoa(n/3600,res,10);
			strcat(res," hr.");
			if(n%3600==0)
				return res;
			else
				if(n%3600<60)
				{
					strcat(res," ");
					_itoa(n%3600,temp,10);
					strcat(res,temp);
					strcat(res," sec.");
					return res;
				}
				else
				{
					n=n%3600;
					strcat(res," ");
					_itoa(n/60,temp,10);
					strcat(res,temp);
					strcat(res," min.");
					if(n%60==0)
						return res;
					else
					{
						strcat(res," ");
						_itoa(n%60,temp,10);
						strcat(res,temp);
						strcat(res," sec.");
						return res;
					}
				}
		}
}
