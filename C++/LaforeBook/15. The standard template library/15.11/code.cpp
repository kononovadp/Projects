//11. Алгоритм copy_backward() используется для обхода проблемы, описанной в упражнении 8 (имеется в виду сдвиг последовательности влево, а не вправо при перекрытии последовательностей). Напишите программу, использующую и copy_backward(), и copy() для осуществления сдвига любой последовательности в любом направлении, независимо от перекрытия.
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
		//copy(arr.begin()+StartPos+(EndPos-StartPos),arr.begin()+EndPos+(EndPos-StartPos),arr.begin()+CopyPos);
		copy_backward(arr.begin()+StartPos+(EndPos-StartPos),arr.begin()+EndPos+(EndPos-StartPos),arr.begin()+CopyPos+(EndPos-StartPos));
		cout<<"OVERLAPS!!!\n";
	}
	else		
		if(CopyPos<StartPos)
		{
			copy(arr.begin()+CopyPos,arr.begin()+CopyPos+(EndPos-StartPos),inserter(arr,arr.begin()+CopyPos+(EndPos-StartPos)));
			//copy(arr.begin()+StartPos+(EndPos-StartPos),arr.begin()+EndPos+(EndPos-StartPos),arr.begin()+CopyPos);
			copy_backward(arr.begin()+StartPos+(EndPos-StartPos),arr.begin()+EndPos+(EndPos-StartPos),arr.begin()+CopyPos+(EndPos-StartPos));
			cout<<"COPY POSITION IS BEHIND THE START POSITION!!!\n";
		}
		else
			copy(arr.begin()+StartPos,arr.begin()+EndPos,inserter(arr,arr.begin()+CopyPos));
}
int main(void)
{
	int i,CopyPos,CountOfItemsToCopy=3,ArrSize=10;
	int StartPos=0,EndPos=StartPos+CountOfItemsToCopy;
	/*//StartPos=0,EndPos=StartPos+CountOfItemsToCopy,CopyPos=1;
	StartPos=ArrSize-CountOfItemsToCopy,EndPos=ArrSize,CopyPos=StartPos-1;	
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
