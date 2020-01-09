{11.	Задано непустий текст довжиною до 255 символів. Виконати над кожним
словом тексту наступні дії. Якщо кількість символів слова є кратною трьом, то з
кожної трійки символів заданого слова вилучити перший символ; інакше слово не
змінювати.}
program z1;
var s:string; i,n,m:byte;
  begin
    readln(s);s:=s+' ';
    i:=1;
  while i < length(s) do begin
    n:=0;
    while s[i] <>' '  do begin n:=n+1; i:=i+1;  end;
     if n mod 3=0 then
   begin
    n:=n div 3;
   for m:=1 to n do
  begin  delete(s,i-1-2*m ,1); i:=i-1; end;
   end;
    i:=i+1;

  end;
    writeln(s);
    readln; end.
