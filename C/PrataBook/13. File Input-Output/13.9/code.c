/*������������� ��������� � �������� 13.3, ����� ������ ����� ���� ������������� � ������������ � �������� ��� ���������� � ������, ������� � 1. ������������ � ���, ����� ��� ������ ������� ��������� ����� ��������� ���� ���������� � ���� �����, ��� ���� ��������� ��������� ��� ���������� �������.*/
/* addaword.c -- ������������� fprintf(), fscanf() � rewind() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 41

int main(void)
{
    FILE *fp;
    char words[MAX];
	int number=0;
    if ((fp = fopen("wordy.txt", "a+")) == NULL)
    {
        fprintf(stdout, "�� ������� ������� ���� \"wordy.txt\".\n");
        exit(EXIT_FAILURE);
    }
	while(fscanf(fp,"%s",words) == 1)
		number++;
	rewind(fp);
    puts("������� ����� ��� ���������� � ����; ��� ����������");
    puts("������� ������ # � ������ ������.");
    while ((fscanf(stdin,"%40s", words) == 1)  && (words[0] != '#'))
	{
        number++;
		fprintf(fp, "%d.%s\n",number,words);
		
	}
    puts("���������� �����:");
    rewind(fp);           /* ������� � ������ ����� */
    while (fscanf(fp,"%s",words) == 1)
		puts(words);
    puts("������!");
    if (fclose(fp) != 0)
        fprintf(stderr, "������ ��� �������� �����\n");

    return 0;
}
