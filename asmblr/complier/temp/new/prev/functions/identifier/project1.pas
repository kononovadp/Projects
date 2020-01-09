program z1;
var i:byte; p:string;
function identifier(s:string):boolean;
var a:set of char; b:boolean;
il,ic: boolean; //ic - содержимое, il - длина
begin
il:=false; ic:=false;
for i:= 48 to 57 do a:=a+[chr(i)]; i:=0;
for i:= 65 to 90 do a:=a+[chr(i)]; i:=0;
if length(s)>8 then il:=true;
for i:=1 to length(s) do if not (s[i] in a) then ic:=true;
if il=true then writeln('Incorrect length of identifier!');
if ic=true then writeln('Undefined symbols of identifier!');
if (il=true) or (ic=true) then identifier:=false else identifier:=true;
end;
  begin
  p:='datA';
  identifier(p);
  readln;
end.
