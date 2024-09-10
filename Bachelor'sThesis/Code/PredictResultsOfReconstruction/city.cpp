#include "headers/model.h"
city::city(string NewClassName,string NewId,int NewIndex,int NewLineNumber,int NewColumnNumber,double NewSimulationTime,char NewDelayDistribution,double NewMeanDelayOrMinDelay,double NewMaxDelayOrDeviation,double reliability,int CountOfBreakdowns,int NewCountOfConstructions,object** NewCars):object(NewClassName,NewId,NewIndex,NewLineNumber,NewColumnNumber,NewSimulationTime,NewDelayDistribution,NewMeanDelayOrMinDelay,NewMaxDelayOrDeviation,reliability,CountOfBreakdowns)
{
	CountOfConstructions=NewCountOfConstructions;
	CountOfFinishedConstructions=0;
	cars=NewCars;
	stuff=0.0;
	UsedStuff=0.0;
	PercentageOfUsedStuff=0.0;
	percent=0.0;	
}
void city::UpdateDataOnScreen()
{/*
LOCATION| STATE | BLDGS |USED STUFF ($ BNS.)|LOCATION| STATE | BLDGS |USED STUFF ($ BNS.)|
        |PROC. 1|123/123|123.00/123.00 100% |        |PROC. 1|123/123|123.00/123.00 100% |
*/
	if(percent==0.0)
	{
		//if(GetIndex()%2==0)
			ChangeOutputOnScreenString(GetLineNumber(),GetColumnNumber(),AddSpacesToString(GetId(),8)+"|"+AddSpacesToString(GetState(),7)+"|"+AddSpacesToString(to_string(CountOfFinishedConstructions)+"/"+to_string(CountOfConstructions),7)+"|"+AddSpacesToString(ConvertDoubleToString(UsedStuff,2)+"/"+ConvertDoubleToString(stuff,2)+" "+ConvertDoubleToString(PercentageOfUsedStuff,0),19)+"|");
		/*else
			ChangeOutputOnScreenString(GetLineNumber(),45,GetId()+"|"+AddSpacesToString(GetState(),7)+"|"+AddSpacesToString(to_string(CountOfFinishedConstructions)+"/"+to_string(CountOfConstructions),7)+"|"+AddSpacesToString(ConvertDoubleToString(UsedStuff,2)+"/"+ConvertDoubleToString(stuff,2)+" "+ConvertDoubleToString(PercentageOfUsedStuff,0),19)+"\n");*/
	}

}