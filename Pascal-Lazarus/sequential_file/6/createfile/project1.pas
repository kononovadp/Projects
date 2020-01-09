{6. Записати у файл f зі збереженням порядку проходження  компоненти файлу F,
значення яких не перевищують 1000.}
program z1;
uses crt;
var f:file of integer; n,x,k:integer; i:byte;
  begin
    n:=10; x:=0; k:=1;
    assign(f,'file-f.dat');rewrite(f);
    for i:=1 to n do begin
    x:=i+(x+(x*k)); //for real: x:=i+(x+exp(ln(2)*i))
    if x<=1000 then
    write(f,x)
    end;
    close(f);
    end.
