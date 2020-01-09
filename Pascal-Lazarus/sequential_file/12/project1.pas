{12. Сформувати файли  f i g. Формулу для формування файлу у     взяти з
наступного варианту. Записати у   файл h спочатку компонента файлу  f, а
потім - компоненти файлу g зі збереженням порядку. Формули № 11,12.}
program z1;
var f,f2,h:file of integer; x:integer; n:byte;
  begin
  //запись из файла f в файл h
  assign(f,'file-f.dat');reset(f);
  assign(f2,'file-f2.dat');reset(f2);
  assign(h,'file-h.dat');rewrite(h);
  while not (eof(f)) do  begin
     read(f,x);write(h,x);
     end;
  while not (eof(f2)) do  begin
     read(f2,x);write(h,x);
     end;
  close(f); close(f2);  close(h);
  //чтение и вывод файла f
  write('file F: '); writeln;
  assign(f,'file-f.dat');reset(f);
  while not (eof(f)) do  begin
     read(f,x);writeln(x); end; close(f); readln;
  //чтение и вывод файла f2
  write('file F2: '); writeln;
  assign(f2,'file-f2.dat');reset(f2);
  while not (eof(f2)) do  begin
     read(f2,x);writeln(x); end; close(f2); readln;
  //чтение и вывод файла h
  write('file H: '); writeln;
  assign(h,'file-h.dat');reset(h);
  while not (eof(h)) do  begin
     read(h,x);writeln(x); end; close(h); readln;
end.
