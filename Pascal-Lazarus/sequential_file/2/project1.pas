{2. Визначити найбільше зі значень компонентів по модулю з непарними номерами.
Формула № 11.}
program z1;
var f,b:file of integer; x,max:integer; n:byte;
  begin
  assign(f,'file-f.dat');reset(f);
  read(f,x); max:=x;  writeln(x);
  while not (eof(f)) do begin
    read(f,x);writeln(x);
    if abs(x)>max then max:=x;
    end;  writeln('max= ',max);  close(f); readln;
    end.
