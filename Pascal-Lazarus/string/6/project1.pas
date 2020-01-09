{6.	Задано непустий текст довжиною до 255 символів. Виконати над кожним
словом тексту наступні дії. Якщо слово не містить у собі символа “+”, то
залишити це слово без змін. Інакше кожну з цифр, яка знаходиться після першого
входження символа “+”, замінити на символ “–“ .}
program z1;
uses crt;
var s:string; i,p,n,m:byte;
  begin
    readln(s); s:=s+' ';

    p:=1; i:=1;
  while i<length(s) do
   begin  n:=0;
    while s[i]<>' ' do begin
    if s[i]='+' then n:=n+1;
    i:=i+1;
    end;
   m:=0;
  if n>0 then
  while p<i do
   begin
     if s[p]='+' then m:=m+1;
     if (s[p]>='0') and (s[p]<='9') and (m=1) then s[p]:='-';
     p:=p+1;
   end
 else p:=i+1;
   i:=i+1;
   end;
  write(s); readln;
  end.


