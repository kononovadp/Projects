//8. Алгоритм copy() можно использовать для копирования последовательностей в контейнере. Тем не менее нужно внимательно следить за тем, чтобы целевая последовательность не перекрывала исходную. Напишите программу, позволяющую производить копирование последовательностей внутри контейнера. Допустим, пользователь вводит значения first1, last1 и first2. Осуществляйте в программе проверку того, что последовательность, перекрывающая другую, сдвигается налево, а не направо. (Например, можно сдвигать некоторые данные из позиции 10 в позицию 9, но не в позицию 11.) Так делается потому, что copy() начинает работу с самого крайнего элемента слева.
#include "../../accessories.h"
#include <algorithm>
#include <vector>
#include <iterator> 
void CopyToVector(vector<int>& arr,int StartPos,int EndPos,int CopyPos)
{
	int i;
	if(CopyPos>=StartPos && CopyPos<EndPos)
	{
		copy(arr.begin()+StartPos,arr.begin()+EndPos,inserter(arr,arr.begin()+EndPos));
		copy(arr.begin()+StartPos+(EndPos-StartPos),arr.begin()+EndPos+(EndPos-StartPos),arr.begin()+CopyPos);
		cout<<"OVERLAPS!!!\n";
	}
	else		
		if(CopyPos<StartPos)
		{
			copy(arr.begin()+CopyPos,arr.begin()+CopyPos+(EndPos-StartPos),inserter(arr,arr.begin()+CopyPos+(EndPos-StartPos)));
			copy(arr.begin()+StartPos+(EndPos-StartPos),arr.begin()+EndPos+(EndPos-StartPos),arr.begin()+CopyPos);
			cout<<"COPY POSITION IS BEHIND THE START POSITION!!!\n";
		}
		else
			copy(arr.begin()+StartPos,arr.begin()+EndPos,inserter(arr,arr.begin()+CopyPos));
}
int main(void)
{
	int i,CopyPos,CountOfItemsToCopy=3,ArrSize=10;
	int StartPos=0,EndPos=StartPos+CountOfItemsToCopy;	
	/*StartPos=ArrSize-CountOfItemsToCopy,EndPos=ArrSize,CopyPos=StartPos;
	//StartPos=0,EndPos=CountOfItemsToCopy,CopyPos=3;
	vector<int> arr;
	for(i=0; i<ArrSize; i++)
		arr.push_back(i);
	cout<<"Source array:\n";
	for(i=0; i<arr.size(); i++)
		cout<<setw(3)<<arr[i];
	cout<<"\nStartPos: "<<StartPos<<"; EndPos: "<<EndPos<<"; Items to copy:\n";
	for(i=StartPos; i<EndPos; i++)
		cout<<setw(3)<<arr[i];
	cout<<"\nCopyPos: "<<CopyPos<<endl;
	CopyToVector(arr,StartPos,EndPos,CopyPos);
	cout<<"Array with copied items:\n";
	for(i=0; i<arr.size(); i++)
		cout<<setw(3)<<arr[i];*/
	for(StartPos=0,EndPos=StartPos+CountOfItemsToCopy; EndPos<=ArrSize; StartPos++,EndPos++)
	{		
		vector<int> arr;
		for(i=0; i<ArrSize; i++)
			arr.push_back(i);
		cout<<"Source array:\n";
		for(i=0; i<arr.size(); i++)
			cout<<setw(3)<<arr[i];
		cout<<"\nStartPos: "<<StartPos<<"; EndPos: "<<EndPos<<"; Items to copy:\n";
		for(i=StartPos; i<EndPos; i++)
			cout<<setw(3)<<arr[i];
		for(CopyPos=0; CopyPos<=ArrSize; CopyPos++)
		{
			vector<int> arr;
			for(i=0; i<ArrSize; i++)
				arr.push_back(i);
			cout<<"\nCopyPos: "<<CopyPos<<endl;
			CopyToVector(arr,StartPos,EndPos,CopyPos);
			cout<<"Array with copied items:\n";
			for(i=0; i<arr.size(); i++)
				cout<<setw(3)<<arr[i];
		}
		//cout<<"\nPress a key to continue: ";
		//getche();
		cout<<endl;
		for(i=0; i<91; i++)
			cout<<'-';
	}	
	for(StartPos=ArrSize-CountOfItemsToCopy,EndPos=ArrSize; StartPos>=0; StartPos--,EndPos--)
	{		
		vector<int> arr;
		for(i=0; i<ArrSize; i++)
			arr.push_back(i);
		cout<<"Source array:\n";
		for(i=0; i<arr.size(); i++)
			cout<<setw(3)<<arr[i];
		cout<<"\nStartPos: "<<StartPos<<"; EndPos: "<<EndPos<<"; Items to copy:\n";
		for(i=StartPos; i<EndPos; i++)
			cout<<setw(3)<<arr[i];
		for(CopyPos=ArrSize; CopyPos>=0; CopyPos--)
		{
			vector<int> arr;
			for(i=0; i<ArrSize; i++)
				arr.push_back(i);
			cout<<"\nCopyPos: "<<CopyPos<<endl;
			CopyToVector(arr,StartPos,EndPos,CopyPos);
			cout<<"Array with copied items:\n";
			for(i=0; i<arr.size(); i++)
				cout<<setw(3)<<arr[i];
		}
		//cout<<"\nPress a key to continue: ";
		//getche();
		cout<<endl;
		for(i=0; i<91; i++)
			cout<<'-';
	}
	return 0;
}
