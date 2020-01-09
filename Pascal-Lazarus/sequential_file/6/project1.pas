{6. Записати у файл f зі збереженням порядку проходження  компоненти файлу F,
значення яких не перевищують 1000. Формула № 11.}
program z1;
var f,b:file of integer; x:integer; k,n:byte;
  begin
  assign(f,'file-f.dat');reset(f); k:=0;
  while not (eof(f)) do  begin
     read(f,x);writeln(x);
     end; close(f); readln;
     end.
