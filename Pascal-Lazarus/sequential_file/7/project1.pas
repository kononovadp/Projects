{7. Сформувати файли f1 i f2. Формулу для f2 узяти з наступного варіантy.
Переписати зі збереженням поряку перехід компонентів файлу f1 у файл f2, а
компоненти файлу f2 - у файл  f1, використовуючи проміжний фийл h. Формула № 11.}
program z1;
var f,f2,h:file of integer; x:integer; n:byte;
  begin
  //запись из файла f в файл h
  assign(f,'file-f.dat');reset(f);
  assign(h,'file-h.dat');rewrite(h);
  while not (eof(f)) do  begin
     read(f,x);write(h,x);
     end;   close(f);  close(h);
  //запись из файла f2 в файл f
  assign(f2,'file-f2.dat');reset(f2);
  assign(f,'file-f.dat');rewrite(f);
  while not (eof(f2)) do  begin
     read(f2,x);write(f,x);
     end;   close(f); close(f2);
  //запись из файла h в файл f2
  assign(h,'file-h.dat');reset(h);
  assign(f2,'file-f2.dat');rewrite(f2);
  while not (eof(h)) do  begin
     read(h,x);write(f2,x);
     end;   close(f2);  close(h);
  //чтение и вывод файла f
  assign(f,'file-f.dat');reset(f);
  while not (eof(f)) do  begin
     read(f,x);writeln(x); end; close(f); readln;
  //чтение и вывод файла f2
  assign(f2,'file-f2.dat');reset(f2);
  while not (eof(f2)) do  begin
     read(f2,x);writeln(x); end; close(f2); readln;
end.
