struct SCAN_INFO
{
	char manufacturer[127];// ������������
	int year;	 // ��� ������������
	char model[128];// ������������ ������
	float price;// ����
	int x_size;// �������������� ������ ������� ������������
	int y_size;// ������������ ������ ������� ������������
	int optr; // ���������� ����������
};
char *equsize(char s[],char t[]);