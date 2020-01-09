{9. Одержати у файлі g компоненти файлу f типу integer, які поділяються на 3 і
не поділяються на 7.}
program z1;
var f,g:file of integer; x:integer; k,n:byte;
  begin
  assign(g,'file-g.dat');rewrite(g);
  assign(f,'file-f.dat');reset(f); k:=0;
  while not (eof(f)) do  begin
     read(f,x);
     if (x mod 3=0) and (x mod 7<>0) then write(g,x)
       end; close(f); close(g); {else begin write('there are no suitable numbers');}
  assign(f,'file-f.dat');reset(f);//вывод исходного файла f
     while not (eof(f)) do  begin
     read(f,x); writeln(x); end;
     close(f); readln;

  assign(f,'file-g.dat');reset(g);//вывод файла g
     while not (eof(g)) do  begin
     read(g,x); writeln(x); end;
     close(g); readln;
     end.
