uses sysutils;
var s:string; n,i,k,b,r,j:integer;
begin
readln(s);
k:= length(s)-1; i:=1;
while i<>length(s)+1 do begin
n:=strtoint(s[i]); inc(i);
r:=1; for j:=1 to k do r:=r*2; k:=k-1;
b:=b+(r*n); end;  writeln(b);
readln;
end.
