#include "accessories.h"
int MaxCountOfBuildings=9678673;
bool* GetRandomArrayOfBooleans(int size,double PercentageOfTrueValues)
{
	bool t,*RandomArray=(bool*)calloc(size,sizeof(char));
	int i,j,CountOfTrueValues=size*PercentageOfTrueValues/100;
	cout<<CountOfTrueValues<<endl;
	for(i=0; i<CountOfTrueValues; i++)
		RandomArray[i]=true;
	for(i=0; i<size; i++)
	{
		j=rand()%size;
		t=RandomArray[i];
		RandomArray[i]=RandomArray[j];
		RandomArray[j]=t;
	}
	return RandomArray;
}
void GenerateRandomDataset(int CountOfBuildings, char* FileName)
{
	SYSTEMTIME StartTime,EndTime;
	GetSystemTime(&StartTime);
	int i,j,k,length,TotalCountOfBuildings=0;
	char ch,**address=(char**)calloc(4,sizeof(char*));
	double PercentageOfIncompleteConstructions=GetRandomDouble(10,25);
	double PercentageOfFutureConstructions=GetRandomDouble(3,5);
	bool* ProblematicConstructions,*FutureConstructions;
	char** materials=new char*[10],**conditions=new char*[5];
	char* temp,*RandomNumber=(char*)calloc(20,sizeof(char));
	cout<<"Count of buildings: "<<CountOfBuildings<<endl;
	cout<<"Percentage of incomplete constructions: "<<PercentageOfIncompleteConstructions;
	cout<<"; count: ";
	ProblematicConstructions=GetRandomArrayOfBooleans(CountOfBuildings,PercentageOfIncompleteConstructions);
	cout<<"Percentage of future constructions: "<<PercentageOfFutureConstructions;
	cout<<"; count: ";
	FutureConstructions=GetRandomArrayOfBooleans(CountOfBuildings,PercentageOfFutureConstructions);
	cout<<"Generating random data...";
	for(i=0; i<4; i++)
		address[i]=(char*)calloc(100,sizeof(char));
    ifstream InputFile("addresses.csv", ios::binary);
    ofstream OutputFile(FileName);
	for(i=0; i<10; i++)
	{
		materials[i]=(char*)calloc(30,sizeof(char));
		InputFile.get(ch);
		for(j=0; ch!=';'; j++)
		{
			materials[i][j]=ch;
			InputFile.get(ch);
		}
	}
	InputFile.get(ch);
	InputFile.get(ch);
	for(i=0; i<5; i++)
	{
		conditions[i]=(char*)calloc(30,sizeof(char));
		InputFile.get(ch);
		for(j=0; ch!=';'; j++)
		{
			conditions[i][j]=ch;
			InputFile.get(ch);
		}
	}	
	InputFile.get(ch);
	InputFile.get(ch);
	InputFile.get(ch);
	while(ch!=13)
	{
		OutputFile.put(ch);
		InputFile.get(ch);
	}
	OutputFile.put('\n');
	while(TotalCountOfBuildings<CountOfBuildings && InputFile.get(ch))
	{
		if(ch==13 || ch=='\n')
			continue;
		for(i=0; i<3; i++)
		{			
			for(j=0; ch!=';'; j++)
			{
				address[i][j]=ch;
				InputFile.get(ch);
			}
			InputFile.get(ch);
		}
		for(; ch!=13 && TotalCountOfBuildings<CountOfBuildings; TotalCountOfBuildings++)
		{
			for(i=0; ch!=',' && ch!=';' && ch!=13 && ch!='\n'; i++)
			{
				address[3][i]=ch;
				InputFile.get(ch);
			}
			for(i=0; i<4; i++)
				OutputFile<<address[i]<<";";
			if(FutureConstructions[TotalCountOfBuildings])
				itoa(GetRandomInt(2025,2030),RandomNumber,10);
			else
				itoa(GetRandomInt(1965,2024),RandomNumber,10);
			OutputFile<<RandomNumber<<";";
			for(i=0,length=GetRandomInt(1,10); i<length-1; i++)
				OutputFile<<materials[i]<<",";
			OutputFile<<materials[i]<<";";
			for(i=0; i<10; i++)
			{
				j=rand()%10;
				temp=materials[i];
				materials[i]=materials[j];
				materials[j]=temp;
			}
			for(i=0; i<4; i++)
				RandomNumber[i]=0;
			itoa(GetRandomInt(1,100),RandomNumber,10);
			OutputFile<<RandomNumber<<";";
			stringstream stream;
			stream<<fixed<<setprecision(2)<<GetRandomDouble(2.4,3.5);			
			OutputFile<<stream.str()<<";";
			if(FutureConstructions[TotalCountOfBuildings])
			{
				if(GetRandomInt(0,10)<5)
					OutputFile<<conditions[1]<<";";
				else
					OutputFile<<conditions[2]<<";";
			}
			else			
				if(ProblematicConstructions[TotalCountOfBuildings])
				{
					if(GetRandomInt(0,10)<5)
						OutputFile<<conditions[4]<<";";
					else
						OutputFile<<conditions[3]<<";";
				}
				else
					OutputFile<<conditions[0]<<";";
			OutputFile.put('\n');
			for(i=0,length=strlen(address[3]); i<length; i++)
				address[3][i]=0;
			InputFile.get(ch);			 
		}
		for(i=0; i<3; i++)
			for(j=0,length=length=strlen(address[i]); j<length; j++)
				address[i][j]=0;
	}
	InputFile.close();
    OutputFile.close();
	for(i=0; i<4; i++)
		delete[] address[i];
	for(i=0; i<10; i++)
		delete[] materials[i];
	for(i=0; i<5; i++)
		delete[] conditions[i];
	delete[] address;
	delete[] conditions;
	delete[] materials;
	delete[] ProblematicConstructions;
	delete[] FutureConstructions;
	delete[] RandomNumber;
	GetSystemTime(&EndTime);
	EndTime=GetTimeDifference(EndTime,StartTime);
	cout<<" Total count of generated buildings: "<<TotalCountOfBuildings<<endl;
	cout<<"The file "<<FileName<<" was created. ";
	cout<<"Time: "<<setw(2)<<EndTime.wMinute<<" minutes "<<EndTime.wSecond<<" seconds\n";
	for(i=0; i<90; i++)
		cout<<'-';
	cout<<endl;
}
int main(void)
{
	// system("CHCP 1251 > nul");
    // SetConsoleCP(CP_UTF8);
    // SetConsoleOutputCP(CP_UTF8);
	InitFloatingPointAndRandomNumbers();
	int ArraySize=125000;
	char i,*FileName=(char*)calloc(11,sizeof(char));
	char* number=(char*)calloc(3,sizeof(char));
	strcpy(FileName,"Dataset_");	
	for(i=0; i<7; i++,ArraySize*=2)
	{
		itoa(i+1,number,10);
		strcat(FileName,number);
		strcat(FileName,".csv");
		GenerateRandomDataset(ArraySize,FileName);
		strcpy(FileName,"Dataset_");
	}
	delete[] FileName;
	delete[] number;
	return 0;
}
