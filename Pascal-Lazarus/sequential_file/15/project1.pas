{15. Записати у файл g зі збереженням порядку проходження компоненти файлу f типу
integer, перед якими знаходяться компоненти, кратні 3.}
program z1;
var f,f2,h:file of integer; x:integer; n:byte;
const p: integer=50;
  begin
  //запись из файла f в файл h
  assign(f,'file-f.dat');reset(f);
  assign(h,'file-h.dat');rewrite(h);
  while not (eof(f)) do  begin
  read(f,x); if x mod 3<>0 then write(h,x);
  {if (FilePos(f)+1) mod 3=0 then begin filePos(f)-1; write(h,x);  end; }
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
