#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;
class CTreeNode
{
public:
	CTreeNode(){};
	CTreeNode(int tn,string dest,string depart)
	{
		m_TrainNumber=tn;
		m_Destination=dest;
		m_DepartureTime=depart;
	};
	void Display();
	int GetTrainNumber();
	string GetStationName();
	void SetTrainNumber(int n);
protected:
	int m_TrainNumber;
	string m_Destination;
	string m_DepartureTime;
};