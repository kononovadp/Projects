{8.	Задано непустий текст довжиною до 255 символів. Виконати над кожним
словом тексту наступні дії. Якщо перший символ слова зустрічається в ньому не
менш ніж тричі, то вилучити частину слова, яка розташована між другим та третім
входженням цього символа.}
program z1;
uses crt;
var s:string; i,p,n,m:byte; ch:char;
  begin
    readln(s); s:=s+' ';

    p:=1; i:=1;
  while i<length(s) do
   begin  n:=0;
    while s[i]<>' ' do begin
    if s[i]=s[p] then n:=n+1;
    i:=i+1;
    end;
    writeln(n);

    if n>= 3 then
    begin
     ch:=s[p]; m:=0;
     while m<3 do
       begin
         if s[p]=ch then  m:=m+1;
         if (m=2) and (s[p]<>ch) then begin delete(s,p,1); i:=i-1;p:=p-1; end;
         p:=p+1;
       end;
    end;

    p:=i+1; i:=i+1;
   end;
  write(s); readln;
  end.


