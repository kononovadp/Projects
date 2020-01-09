{13. Знайти усі прості числа із діапазону від 2 до 2000. }
program Prostye_chisla;
var
n,i,j,s,m,h:integer; f:text;
begin
n:=2000;
assign(f,'numbers.txt'); rewrite(f);
for i:=2 to n do begin
s:=0; h:=round(sqrt(i));
for j:=2 to h do
    if i mod j=0 then begin s:=s+1; break; end;

if s=0 then begin m:=m+1; Writeln(f,i); end;
end;
Write(m,' numbers found. They were written in file numbers.txt');
close(f); readln;
end.

{program z1;
var m,n,i,p,l:integer; k:boolean; mn:array[2..2000] of integer;
begin
readln(n); k:=false;
for i:= 2 to n-1 do if n mod i = 0 then k:=true;
if k = false then writeln('the entered number is simple') else
writeln('the entered number is not simple');
readln;
end. }
