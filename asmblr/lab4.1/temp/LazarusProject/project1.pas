Program lab4(input,output);
var
 i : word;
 x :array [1..2000] of byte;
 y :array [1..1000] of word;
{$L bigshow.obj}
{$F+}
Procedure BigShow(var p1;p2:word);external;
{$f-}
 begin {Main program}
 for i:=1 to 300 do
 begin
 x[i]:=i;
 y[i]:=i;
 end;
 for i:=1 to 30 do
 begin
 writeln('x= ');
 BigShow(x,301-i);
 writeln('y= ');
 BigShow(y,301-i);
 readln;
 end;
 end.
