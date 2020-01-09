program h1;
uses sysutils;
var i:real;
f:text;
function hxd(n:real):string;
var i,c,w,k:integer; s,sr:string; ch:char;
begin
for i:=1 to 4 do begin
  c:=trunc(n) mod 16;
  n:=trunc(n) div 16;
  sr:=inttostr(c);
  if sr = '10' then sr:='A'; if sr = '11' then sr:='B'; if sr = '12' then sr:='C';
  if sr = '13' then sr:='D'; if sr = '14' then sr:='E'; if sr = '15' then sr:='F';
  s:=s+sr;
end;
n:= length(s) div 2;
for i:= 1 to trunc(n) do begin
ch:= s[i];
s[i]:= s[length(s)-i+1];
s[length(s)-i+1] := ch;
end;
hxd:=s;
end;
begin
readln(i);
writeln(hxd(i));
readln;
end.

{while s[i]<>'.' do begin c:=c+s[i]; inc(i); end;
delete(c,1,1); delete(s,1,length(c)); delete(s,1,1);
i:=strtoint(c); j:=strtoint(s);
writeln(hxd(i),'.',hxd(j));
write(f,c,'  ',s); }
