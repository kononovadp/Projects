#include <sstream>
using namespace std;
char *equsize(char s[],char t[])
{
	if (strlen(s)<strlen(t))
	{
		int n=strlen(t)-strlen(s); int i;
		for (i=0; i<n; i++)
		strcat(s," ");	
	}
	return(&s[50]);
}