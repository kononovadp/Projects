/* Написать функцию int substr(const char *string1, const char *string2) , 
которая возвращает индекс элемента в строке string1, с которого начинается 
подстрока, равная string2. */
#include <iostream> 
#include "mystring.h"
using namespace std;
int main()
{	char s1[] = "abcdefghf"; char s2[] = "gh"; 
	int n=substr(s1,s2);
	cout<<"string 1= "<<s1<<endl;
	cout<<"string 2= "<<s2<<endl;
	cout<<n;
    cin.get();
}