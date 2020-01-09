{14. Записати у файл  g зі збереженням порядку проходження ті компоненти файлу f
типу integer, слідом за якими лежить компонента, кратна 5.}
program z1;
var f,f2,h:file of integer; x,x1,x2:integer; n:byte;
const p: integer=50;
  begin
  //запись из файла f в файл h
  assign(f,'file-f.dat');reset(f);
  assign(h,'file-h.dat');rewrite(h); read(f,x1);
  while not (eof(f)) do  begin
     read(f,x2); if x2 mod 5=0 then write(h,x1);
     x1:=x2;
     end;
close(f); close(h);
  //чтение и вывод файла f
  write('file F: '); writeln;
  assign(f,'file-f.dat');reset(f);
  while not (eof(f)) do  begin
     read(f,x);writeln(x); end; close(f); readln;
  //чтение и вывод файла h
  write('file H: '); writeln;
  assign(h,'file-h.dat');reset(h);
  while not (eof(h)) do  begin
     read(h,x);writeln(x); end; close(h); readln;
end.
