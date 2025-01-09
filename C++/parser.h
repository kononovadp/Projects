#include "accessories.h"
void parse();
namespace ParserClasses
{	
	class ProgramObject
	{
		char* type;
		public: ProgramObject();
		ProgramObject(char* NewType);
		virtual void display();
	};
	class ProgramName: public ProgramObject
	{
		char* name;
		public: ProgramName(char* NewType,char* NewProgramName);
	};
	class comment: public ProgramObject
	{
		char* text;
		public: comment(char* NewType,char* NewComment);
		void display();
	};
	class variable: public ProgramObject
	{
		char* DataType,*name,*value;
		variable(char* NewType,char* NewDataType,char* NewName,char* NewValue);
		void display();
	};
}