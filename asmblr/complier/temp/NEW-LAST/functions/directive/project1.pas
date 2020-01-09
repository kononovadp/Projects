program z1;
var i:integer; s:string; temp3:text;
  ds,cs,de,ce,e:boolean;
begin
  assign(temp3,'temp3.txt'); reset(temp3);
  while not eof(temp3) do begin
  readln(temp3,s);
  if s='data segment' then ds:=true;
  if s='data ends' then de:=true;
  if s='code segment' then cs:=true;
  if s='code ends' then ce:=true;
  if s='end ' then e:=true;
  end;
  if ds=false then writeln('Data segment does not exist!');
  if de=false then writeln('No data ends directive!');
  if cs=false then writeln('Code segment does not exist!');
  if ce=false then writeln('No code ends directive!');
  if e=false then writeln('No end directive!');
  if (ds=true) and(de=true) and(cs=true) and(ce=true) and(e=true)
  then writeln('All directives are right');
  close(temp3); //erase(temp3);
  readln;
end.

