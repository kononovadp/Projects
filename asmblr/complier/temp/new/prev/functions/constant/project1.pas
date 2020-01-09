program z1;
var i:byte; p:string;

function constant(s:string):boolean;
var h1,d1,b1:set of char;
    h,d,b,t:boolean;
    k:integer; ch:char;
begin
h:=false; d:=false; b:=false; t:=false;
for i:= 48 to 57 do h1:=h1+[chr(i)]; i:=0;
for i:= 97 to 102 do h1:=h1+[chr(i)]; i:=0;
for i:= 48 to 57 do d1:=d1+[chr(i)]; i:=0;
for i:= 48 to 49 do b1:=b1+[chr(i)]; i:=0;
if s[length(s)]='h' then h:=true;
if s[length(s)]='b' then b:=true;
if (s[length(s)]='d') or (s[length(s)] in d1) then d:=true;
if (s[1]=chr(39)) and (s[length(s)]=chr(39)) then t:=true;
if (h=false) and (d=false) and (b=false) and (t=false)
then begin writeln('Incorrect constant'); exit; end;
if h=true then begin
for i:=0 to length(s)-1 do begin
ch:=s[i]; if not (ch in h1) then k:=pos(ch,s); end;
if k>0 then writeln('Incorrect hexadecimal constant');
if k=0 then exit;
end; i:=0; k:=0;
if d=true then begin
for i:=0 to length(s)-1 do begin
ch:=s[i]; if not (ch in d1) then k:=pos(ch,s); end;
if k>0 then writeln('Incorrect decimal constant ');
if k=0 then exit;
end; i:=0; k:=0;
if b=true then begin
for i:=0 to length(s)-1 do begin
ch:=s[i]; if not (ch in b1) then k:=pos(ch,s); end;
if k>0 then writeln('Incorrect binary constant ');
if k=0 then exit;
end;
if t=true then exit;
constant:=false;
end;
begin
readln(p);
constant(p);
readln;
end.

