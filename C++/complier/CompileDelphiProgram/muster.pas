program basexample;
Uses Math;
var
	i,PowerBase,MaxPowerBase,int1,int2,int3:integer;
	FloatNumber,result,limit,float1,float2:float;
	ResultIsBiggerThanLimit:boolean;
begin
	PowerBase:=0;
	MaxPowerBase:=10;
	FloatNumber:=3.5987;
	int1:=105;
	int2:=56;
	int3:=9;
	float1:=90.76;
	float2:=973.7653;
	result:=int1+float1*((int2-int3)/float2)+float2*0.56-(978/8);
	writeln('result of ariphmetic expression: ',result:0:5);
	limit:=FloatNumber*MaxPowerBase;
	ResultIsBiggerThanLimit:=false;	
	for i:=0 to MaxPowerBase do
	begin
		result:=FloatNumber**PowerBase;
		writeln(FloatNumber:0:3,' in the power of ',PowerBase,' equals ',result:0:3);
		PowerBase:=PowerBase+1;
	end;
	for i:=0 to MaxPowerBase do
		result:=result/2;
	writeln('New result after division by 2 ',MaxPowerBase,' times: ',result:0:3);
	if result=limit then
		writeln('result ',result:0:3,' is equal to the limit ',limit:0:3)
	else
		if result<>limit then		
			writeln('result ',result:0:3,' is NOT EQUAL to the limit ',limit:0:3);
	if result>limit then
	begin
		ResultIsBiggerThanLimit:=true;
		writeln('result ',result:0:3,' > limit ',limit:0:3);
	end
	else
		if result<limit then
		begin
			ResultIsBiggerThanLimit:=true;
			writeln('result ',result:0:3,' < limit ',limit:0:3);
		end;
	writeln('ResultIsBiggerThanLimit: ',ResultIsBiggerThanLimit);
end.