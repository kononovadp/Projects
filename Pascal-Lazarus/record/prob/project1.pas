program z1;
uses crt;

var x,y,z:integer; f:text;

begin
assign(f,'s.txt');//связь с файлом
reset(f); ///подготовка файла к чтению

 while not (eof(f)) do
  begin
    read(f,x,y); z:=y+x; writeln(z);
  end;
  close(f);//завершение работы с файлом
   writeln(y);
readln;



END.
