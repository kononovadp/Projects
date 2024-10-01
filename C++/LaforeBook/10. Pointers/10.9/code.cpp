//9. Допустим, что нам нужно сохранить 100 целых чисел так, чтобы иметь к ним легкий доступ. Допустим, что при этом у нас есть проблема: память нашего компьютера так фрагментирована, что может хранить массив, наибольшее количество элементов в котором равно десяти (такие проблемы действительно появляются, хотя обычно это происходит с объектами, занимающими большое количество памяти). Вы можете решить эту проблему, определив 10 разных массивов по 10 элементов в каждом и массив из 10 указателей на эти массивы. Массивы будут иметь имена a0, a1, a2 и т. д. Адрес каждого массива будет сохранен в массиве указателей типа int*, который называется ар. Вы сможете получить доступ к отдельному целому используя выражение ap[j][к], где j является номером элемента массива указателей, а к — номером элемента в массиве, на который этот указатель указывает. Это похоже на двумерный массив, но в действительности является группой одномерных массивов. Заполните группу массивов тестовыми данными (скажем, номерами 0, 10, 20 и т. д.), а затем выведите их, чтобы убедиться, что все работает правильно.
#include "../../accessories.h"
int* FillArray()
{
	int* NewArray=new int[10];
	for(int i=0; i<10; i++)
	{
		NewArray[i]=GetRandomInt(10,1000);
		cout<<setw(5)<<*(NewArray+i);
	}
	cout<<endl;
	return NewArray;
}
int main(void)
{
	InitFloatingPointAndRandomNumbers();
	int i,j;	
	int *a1=FillArray();
	int *a2=FillArray();
	int *a3=FillArray();
	int *a4=FillArray();
	int *a5=FillArray();
	int *a6=FillArray();
	int *a7=FillArray();
	int *a8=FillArray();
	int *a9=FillArray();
	int *a10=FillArray();
	int **ap=new int*[10];
	ap[0]=a1;
	ap[1]=a2;
	ap[2]=a3;
	ap[3]=a4;
	ap[4]=a5;
	ap[5]=a6;
	ap[6]=a7;
	ap[7]=a8;
	ap[8]=a9;
	ap[9]=a10;
	cout<<"------------------------------------------------------------\n";
	for(i=0; i<10; i++)
	{
		for(j=0; j<10; j++)
			cout<<setw(5)<<*(*(ap+i)+j); //cout<<setw(5)<<ap[i][j];
		cout<<endl;
	}
	delete[]a1;
	delete[]a2;
	delete[]a3;
	delete[]a4;
	delete[]a5;
	delete[]a6;
	delete[]a7;
	delete[]a8;
	delete[]a9;
	delete[]a10;
	delete[]ap;
	return 0;
}
