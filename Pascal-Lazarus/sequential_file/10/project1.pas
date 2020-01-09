{10. Одержати у файлі g компоненти файлу f типу integer, що являються точними квадратами.}
program z1;
var f,g:file of integer; x,k:integer; n:byte;
  begin
  assign(g,'file-g.dat');rewrite(g);
  assign(f,'file-f.dat');reset(f); k:=0;
  while not (eof(f)) do  begin
     read(f,x);
     if sqrt(x)=round(sqrt(x)) then write(g,x);
     end; close(f); close(g);
  assign(f,'file-f.dat');reset(f);//вывод исходного файла f
     while not (eof(f)) do  begin
     read(f,x); writeln(x); end;
     close(f); readln;

  assign(f,'file-g.dat');reset(g);//вывод файла g с парными числами
     while not (eof(g)) do  begin
     read(g,x); writeln(x); end;
     close(g); readln;
     end.
