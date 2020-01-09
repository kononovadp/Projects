uses sysutils;
var p:string;
function hextodec(s:string):string;
var r,b:int64; i,j,k,n:byte; s6:set of char;
label l1;
begin
for i:= 65 to 70 do s6:=s6+[chr(i)];  i:=0;
k:=length(s)-1; i:=1; b:=0;
while i<>length(s)+1 do begin
if s[i] in s6 then begin
case s[i] of
'A':n:=10; 'B':n:=11; 'C':n:=12;
'D':n:=13; 'E':n:=14; 'F':n:=15; end; goto l1;
end; n:=strtoint(s[i]);
l1:inc(i); r:=1;
for j:=1 to k do r:=r*16; k:=k-1;
b:=b+(r*n); end;
hextodec:=inttostr(b); end;
begin
readln(p); writeln(hextodec(p));
readln;
end.
