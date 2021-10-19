#include "TreeNode.h"
	void CTreeNode::Display()
	{
		cout<<endl<<"Train number "<<m_TrainNumber<<" Destination "<<m_Destination
		<<" Departure time "<<m_DepartureTime;
	}
	int CTreeNode::GetTrainNumber()
	{
		if (m_TrainNumber!=NULL)
			return m_TrainNumber;
	}
	string CTreeNode::GetStationName()
	{
		if (m_Destination!="")
			return m_Destination;
	}
	void CTreeNode::SetTrainNumber(int n)
	{
		m_TrainNumber=n;
	}