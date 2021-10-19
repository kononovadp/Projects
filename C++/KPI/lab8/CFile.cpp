#include "CFile.h"
	char* CFile::GetFilename()
	{
		return _filename;
	}
	void CFile::SetFilename(char *filename)
	{
		_filename=filename;
	}
	char* CFile::GetDate()
	{
		return _creation_date;
	}
	ostream& operator<<(ostream& os, CFile &obj)
{
	if(&obj!=NULL)
		os<<"  "<<obj._filename<<' '<<obj._creation_date<< ' '<<obj._size<<endl;
    return os;
}
bool CFile::operator==(CFile obj)
{
	return ((strcmp(obj._filename,_filename)==0)&&
	(strcmp(obj._creation_date,_creation_date)==0)
	&&(obj._size==_size));
}
bool CFile::operator!=(CFile obj)
{
	return!(*this==obj);
}
CFile CFile::operator=(string s)
{
		int t=s.find_first_of(";");
		string name=s.substr(0,t);
		s=s.erase(0,t+1);
		t=s.find_first_of(";");
		string date=s.substr(0,t);
		s=s.erase(0,t+1);
		t=s.find_first_of(";");
		string temp=s.substr(0,t);
		istringstream v1 (temp, istringstream::in);
		v1>>_size;
		s=s.erase(0,t+1);
		//cout<<name<<"|"<<date<<"|"<<filesize<<endl;
		_filename = new char [name.length()+1];
		std::strcpy (_filename, name.c_str());
		_creation_date = new char [date.length()+1];
		std::strcpy (_creation_date, date.c_str());
		return *this;
}