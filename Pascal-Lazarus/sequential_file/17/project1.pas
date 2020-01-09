{17. Перевірити, чи упорядковані компоненти файлу f по зростанню.}
program z1;
var f,f2,h:file of integer; x,x1,x2,a,b:integer; n,k,i,j:byte;
const p: integer=50;
  begin
  //чтение и вывод файла f
  write('file F: '); writeln;
  assign(f,'file-f.dat');reset(f);
  read(f,x1);
  while not (eof(f)) do  begin
     read(f,x2);writeln(x2);
      if x1>x2 then k:=1;
      x1:=x2;
  end;  close(f); if k=0 then writeln ('true') else writeln('false');
   readln;
  //чтение и вывод файла h
  write('file H: '); writeln; k:=0;
  assign(h,'file-h.dat');reset(h);  read(h,x1);
  while not (eof(h)) do  begin
     read(h,x2);writeln(x2);
      if x1>x2 then k:=1;
      x1:=x2;
  end;

  close(h); if k=0 then writeln ('true') else writeln('false');
 readln;
end.
