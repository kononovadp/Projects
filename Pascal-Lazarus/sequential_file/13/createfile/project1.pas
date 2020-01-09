{7. Сформувати файли f1 i f2. Формулу для f2 узяти з наступного варіантy.
Переписати зі збереженням поряку перехід компонентів файлу f1 у файл f2, а
компоненти файлу f2 - у файл  f1, використовуючи проміжний фийл h. Формула № 11.}
program z1;
uses crt;
var f,f2,h:file of real; x,k:real; n,i:byte;
  begin
    n:=10; x:=0; k:=1;
    assign(f,'file-f.dat');rewrite(f);

  for i:=1 to n do begin
    x:=(i-0.1)/(i*i*i+abs(sin(2*i)/cos(2*i))); //for real: x:=i+(x+exp(ln(2)*i))
    write(f,x); end;
    close(f);
    end.
