/*10. Матрица — это двумерный массив. Создайте класс matrix, который предоставляет те же меры безопасности, как и класс из упражнения 7, то есть осуществляет проверку индексов массива на вхождение их в границы массива. Полем класса matrix будет массив 10 на 10. Конструктор должен позволять программисту определить реальный размер массива (допустим, сделать его меньше, чем 10 на 10). Методам, предназначенным для доступа к членам матрицы, теперь нужны два индекса: по одному для каждой размерности массива. Вот фрагмент функции main(), которая работает с таким классом:
matrix m1(3, 4); //описываем матрицу
int temp = 12345; //описываем целое
ml.putel(7, 4, temp); //помещаем значение temp в матрицу
temp = m1.getel(7, 4); //получаем значение из матрицы.*/
#include <iostream>
using namespace std;
class matrix
{
	int rows,columns;
	int** arr;
	public:
	matrix(int r,int c):rows(r),columns(c)
	{
		int i,**a=new int*[r];
		for(i=0; i<r; i++)
			a[i]=new int[c];
		arr=a;
	}
	void putel(int r,int c,int val)
	{
		if(r<rows && c<columns)
			arr[r][c]=val;
	}
	int getel(int r,int c)
	{
		if(r<rows && c<columns)
			return arr[r][c];
	}
	~matrix()
	{
		for(int i=0; i<rows; i++)
			free(arr[i]);
		free(arr);
	}
};
int main(void)
{
	matrix m1(3, 4); //описываем матрицу
	int temp = 12345; //описываем целое
	m1.putel(7, 4, temp); //помещаем значение temp в матрицу
	temp = m1.getel(7, 4); //получаем значение из матрицы
	return 0;
}
