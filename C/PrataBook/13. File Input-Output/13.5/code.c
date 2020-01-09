/*������������� ��������� �� �������� 13.6, ����� ������ �������������� ���������� ��� ������������ ��������� ��������� ������.*/
/* randbin.c -- ������������ ������, �������� ����-����� */
#include <stdio.h>
#include <stdlib.h>
#include "D:\Projects\C\my_library\user_functions.h"
#define ARSIZE 1000
int main(int argc, char *argv[])
{
    double numbers[ARSIZE];
    double value;
    int i;
    long pos;
    FILE *iofile;
    // �������� ������ �������� double
    for(i = 0; i < ARSIZE; i++)
        numbers[i] = 100.0 * i + 1.0 / (i + 1);
    // ������� ������� ����
    if ((iofile = fopen(argv[2], "wb")) == NULL)
    {
        fprintf(stderr, "�� ������� ������� ���� %s ��� ������.\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    // ������ � ���� ������� � �������� �������
    fwrite(numbers, sizeof (double), ARSIZE, iofile);
    fclose(iofile);
    if ((iofile = fopen(argv[2], "rb")) == NULL)
    {
        fprintf(stderr,
                "�� ������� ������� ���� %s ��� ������������� �������.\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    // ������ ��������� ��������� �� �����
	i=strtoint(argv[1]);
    pos = (long) i * sizeof(double); // ���������� ��������
    fseek(iofile, pos, SEEK_SET);    // ������� � ������ �������
    fread(&value, sizeof (double), 1, iofile);
    printf("�� ������� %d ��������� �������� %f.\n", i, value);
    fclose(iofile);
    puts("��������� ���������.");
    return 0;
}
