{7. Сформувати файли f1 i f2. Формулу для f2 узяти з наступного варіантy.
Переписати зі збереженням поряку перехід компонентів файлу f1 у файл f2, а
компоненти файлу f2 - у файл  f1, використовуючи проміжний фийл h. Формула № 11.}
program z1;
uses crt;
var f,f2,h:file of integer; n,x,k:integer; i:byte;
  begin
    n:=10; x:=0; k:=1;
    assign(f,'file-f.dat');rewrite(f);
    assign(f2,'file-f2.dat');rewrite(f2);
    assign(h,'file-h.dat');rewrite(h);
  for i:=1 to n do begin
    x:=i+(x+(x*k)); //for real: x:=i+(x+exp(ln(2)*i))
    write(f,x); end;
    close(f);  i:=0; x:=0;
  for i:=1 to n do begin
    x:=x+(1 div k*(k+1)*(k+2)); //for real: x:=i+(x+exp(ln(2)*i))
    write(f2,x); end;
    close(f2);
    close(h);
    end.
