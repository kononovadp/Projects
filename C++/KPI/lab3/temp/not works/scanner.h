struct SCAN_INFO
{
	char manufacturer[127];// изготовитель
	int year;	 // год изготовления
	char model[128];// наименование модели
	float price;// цена
	int x_size;// горизонтальный размер области сканирования
	int y_size;// вертикальный размер области сканирования
	int optr; // оптическое разрешение
};
char *equsize(char s[],char t[]);