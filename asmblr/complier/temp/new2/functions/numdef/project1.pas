var p:string;
function numdef(s:string):byte;
var s5:set of char; i:byte;
begin
for i:= 48 to 57 do s5:=s5+[chr(i)];
if s[length(s)]='b' then numdef:=2;
if s[length(s)] in s5 then numdef:=10;
if s[length(s)]='d' then numdef:=11;
if s[length(s)]='h' then numdef:=16; end;
begin
readln(p); writeln(numdef(p));
readln;
end.


















{uses sysutils;
var f,f2:text; s,c,p:string; i:byte;
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
assign(f,'1.asm'); reset(f); assign(f2,'2.asm'); rewrite(f2);
while not eof(f) do begin
readln(f,s); i:=0;
delete(s,1,1);
while s[i]<>' ' do begin c:=c+s[i]; inc(i); end;
delete(c,1,1); p:=hextodec(c);
writeln(f2,p,'  ',s); c:='';
end;
readln;
close(f); close(f2);
end.          }

{var p:string;
function dollardef(s:string):integer;
var c:string; i,j,n,k:integer;
begin
if (s[1]='6') and (s[3]='|') then delete(s,1,4);
s:=s+' '; n:=0;
for j:=1 to length(s) do if s[j]=' ' then inc(n);
j:=0; k:=0;
for i:=1 to n do begin
while s[j]<>' ' do begin c:=c+s[j]; inc(j); end; j:=0;
delete(c,1,1); delete (s,1,length(c)); delete(s,1,1);
if length(c)=1 then c:=c+'*';
k:=k+(length(c) div 2); c:=''; end;
def:=k; end;
begin
p:= '66| 81 0E 0012 R 00009fff';
writeln(dollardef(p));
readln;
end.}



{uses sysutils;
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
end.}

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
