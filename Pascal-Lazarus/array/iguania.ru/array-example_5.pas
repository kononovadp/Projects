program z1;
uses crt;
var a:array[0..10] of real;i,k:byte;n,s,m: real;
begin
randomize;
for i:= 0 to 10 do
a[i]:=random(20)-10;
k:=0;  s:=0;
for i:= 0 to 10 do
if a[i]<0 then  begin K:=k+1; s:=s+a[i] end;
n:=s/k;
writeln('среднее арифметическое  ',n:0:3);
for i:= 0 to 10 do write(a[i]:6:2); readln;
k:=0;
for i:= 0 to 10 do if a[i]<a[k] then k:=i;//ищем минимум
a[k]:=n;
 for i:= 0 to 10 do write(a[i]:6:2); readln;
end.
