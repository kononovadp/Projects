uses sysutils;
var p:string;
function immdef(k:string):string;
var n:integer;
begin
if (k[length(k)]='b') or (k[length(k)]='d')
or (k[length(k)]='h') then delete(k,length(k),1);
n:=strtoint(k);
if n<255 then immdef:='8' else immdef:='16';
end;
begin
readln(p); writeln(immdef(p)); readln;
end.

{var s5:set of char; p:string; i:byte;
function numdef(s:string):byte;
begin
for i:= 48 to 57 do s5:=s5+[chr(i)];
if s[length(s)]='h' then numdef:=16;
if s[length(s)]='b' then numdef:=2;
if (s[length(s)]='d') or (s[length(s)] in s5) then numdef:=10;
end;
begin
readln(p); writeln(numdef(p));
readln; end.}

{var s,s1:string;
function reg(s,s1:string):byte;
begin
writeln(s); writeln(s1);
case s of
'al':reg:=8; 'ax':reg:=16; 'eax':reg:=32;
'cl':reg:=8; 'cx':reg:=16; 'ecx':reg:=32;
'dl':reg:=8; 'dx':reg:=16; 'edx':reg:=32;
'bl':reg:=8; 'bx':reg:=16; 'ebx':reg:=32;
'ah':reg:=8; 'sp':reg:=16; 'esp':reg:=32;
'ch':reg:=8; 'bp':reg:=16; 'ebp':reg:=32;
'dh':reg:=8; 'si':reg:=16; 'esi':reg:=32;
'bh':reg:=8; 'di':reg:=16; 'edi':reg:=32;
end; end;
begin
s:='cmp'; s1:='bh'; //readln(p); writeln(reg(p));
readln;
end.}

{var s,k,c:string; i:byte; s5:set of char; b:boolean;
  begin
for i:= 65 to 122 do s5:=s5+[chr(i)]; i:=0;
for i:= 48 to 57 do s5:=s5+[chr(i)];  i:=0;
s5:=s5+[':']; b:=false;
s:='m5:mov bx,ax';
while s[i] <>' ' do begin c:=c+s[i]; inc(i); end;
delete(c,1,1); delete(s,1,length(c));
for i:=1 to length(c) do if pos(':',c)<>0 then b:=true; i:=0;
if b=true then while c[i]<>':' do begin k:=k+c[i]; inc(i); end;
writeln(c,'   ',k);
readln;
end.}
