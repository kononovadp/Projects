program bintohex;
uses sysutils;
var p:string;
  function hxd(n:integer):string;
  var i,c,w,k:integer; s,sr:string; ch:char;
  begin
  for i:=1 to 4 do begin
    c:=n mod 16;
    n:=n div 16;
    sr:=inttostr(c);
    if sr = '10' then sr:='A'; if sr = '11' then sr:='B'; if sr = '12' then sr:='C';
    if sr = '13' then sr:='D'; if sr = '14' then sr:='E'; if sr = '15' then sr:='F';
    s:=s+sr;
  end;
  n:= length(s) div 2;
  for i:= 1 to n do begin
  ch:= s[i];
  s[i]:= s[length(s)-i+1];
  s[length(s)-i+1] := ch;
  end;
  hxd:=s;
  end;
function bintohex(s:string):string;
var n,i,k,b,r,j:integer;
begin
k:= length(s)-1; i:=1; b:=0;
while i<>length(s)+1 do begin
n:=strtoint(s[i]); inc(i);
r:=1; for j:=1 to k do r:=r*2; k:=k-1;
b:=b+(r*n);
end;
bintohex:=inttostr(b); bintohex:=hxd(b);
end;
begin
readln(p); writeln(bintohex(p));
readln;
end.
{uses sysutils;
var s:string; n,i,k,b,r,j:integer;
begin
readln(s);
k:= length(s)-1; i:=1;
while i<>length(s)+1 do begin
n:=strtoint(s[i]); inc(i);
r:=1; for j:=1 to k do r:=r*2; k:=k-1;
b:=b+(r*n); end;  writeln(b);
readln;
end.}
