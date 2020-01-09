{8. Одержати у файлі  g  компоненти файлу f типу  integer, які являються парними числами.}
program z1;
uses crt;
var f:file of integer; n,x,k:integer; i:byte;
  begin
    n:=10; x:=0; k:=1;
    assign(f,'file-f.dat');rewrite(f);
    for i:=1 to n do begin
    x:=i+(x+(x*k)); //for real: x:=i+(x+exp(ln(2)*i))
    write(f,x)
    end;
    close(f);
    end.
