{13. Додатково дане число Р. Переписати послідовно компоненти файлу f у
файл g, зупинившись після першого компонента, що менше Р.}
program z1;
var f,f2,h:file of real; x:real; n:byte;
const p=0.1;
  begin
  //запись из файла f в файл h
  assign(f,'file-f.dat');reset(f);
  assign(h,'file-h.dat');rewrite(h);

  repeat
     read(f,x); write(h,x);
  until  (eof(f)) or (x<p);
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
