/*�������� ���������, ������� ������� ������ �� 26 ��������� � �������� � ���� 26 �������� ���� ����������� ��������. ����� ������������� ����� ����������� ����� �������.*/
 #include <stdio.h>
 #define size 26
 int main(void)
 {
	 int i=0;
	 char a[size],ch;
	 for (ch='a'; ch<='z'; i++,ch++)
		 a[i]=ch;
	 for(i=0; i<size; i++)
		 printf("%c",a[i]);
	 getchar();
	 return 0;
 }