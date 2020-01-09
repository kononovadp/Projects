program matr1;
uses crt;
var a:array[1..10] of integer;
i,min,k,S: integer; b:boolean;
begin
 randomize;
 for i:= 1 to 10 do a[i]:=random(20)-10;
 for i:=1 to 5 do a[i*2]:=99;

 min:=a[1];

 for i:=2 to 10 do
   if a[i]<min then min:=a[i];
 writeln('min=', min); readln;


 k:=0;
 for i:= 1 to 10 do
 if a[i]<0 then k:=k+1;
 writeln('kol otr=',k);

 b:=false;
 for i:=1 to 10 do
 if a[i]=0 then begin  b:=true; break; end;
 if b then writeln('есть нули') else writeln('нулей нет');

 S:=0;
 for i:=1 to 10 do s:=s+a[i];
writeln('sum=',s);


 for i:=1 to 10 do write(a[i]:5); readln;

end.
