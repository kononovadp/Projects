/*�������� ���������, ������� ������ ������� �� ������������ ������ ����� ������ �� ����� �����. ��� ������� ������� ��������� ������ ��������, �������� �� �� ������. ���� ������ - �����, ��������� ������ �������� �������� �� ���������� ����� � ��������. ��������, ����� � � � ����� ����� ����� 3. ������������� � ��������� �������, ������� ��������� ������ � �������� ��������� � ���������� ��� ���������� ����� � ��������, ���� �� �������� ������ � -1 � ��������� ������.*/
#include <stdio.h>
#include <ctype.h>
int letter_number_in_alphabet(char ch)
{
	if (isalpha(ch))
	{
		if (isupper(ch))
			return ch-'A'+1;
		else
			return ch-'a'+1;
	}
	else
		return -1;
}
int main(void)
{
	char ch;
	int number_in_alphabet;
	printf("Input: ");
	while(scanf("%c",&ch)!=EOF && (ch!='\n'))
	{
		printf("%c - ��� ",ch);
		number_in_alphabet=letter_number_in_alphabet(ch);
		if (number_in_alphabet>-1)
			printf("����� ��� ������� %d � ��������\n",number_in_alphabet);
		else
			printf("�� ����� ��� ����� �� ����������� ��������\n");
	}
	return 0;
}