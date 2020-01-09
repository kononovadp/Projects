{14.Задано непустий текст довжиною до 255 символів. Знайти в кожному слові
тексту найдовшу групу знаків. Надрукувати номер кожного слова та знайдену групу знаків.}
program z1;
var s,k,m,max:string; i,n,p:byte;  x:set of char; a:array[1..50] of string;
  begin
    for i:=49 to 57 do x:=x+[chr(i)];//цифры
    for i:=65 to 90 do x:=x+[chr(i)];//большие буквы
    for i:=97 to 122 do x:=x+[chr(i)];//маленькие буквы

    readln(s); s:=s+' ';
p:=0; n:=0; i:=1; k:='';
while i<length (s) do
  begin
  while s[i]<>' ' do begin k:=k+s[i]; i:=i+1; end; //выделяем отдельное слово в строку k
   n:=n+1; max:='';
  for p:= 1 to length(k) do begin
  if not (k[p] in x) then m:=m+k[p]
                     else
                         begin if length(m)>length(max) then  max:=m;
                                m:='';
                         end;
  end;
 writeln(n,' ',k,' ',max); m:=''; k:=''; i:=i+1; end;readln;
end.
{for i:=1 to length(s) do
if s[i]=' ' then n:= n+1; for i:=1 to n do write(i); readln;

i:=1; p:=0; k:=0;
while i<length(s) do
begin
p:=p+1;
write(s[p]); i:=i+1; end; readln;
 end. }
{while s[i]<>' ' do p:=p+1; writeln(s[p]; readln; }


    {for i:=49 to 57 do x:=x+[chr(i)];//цифры
    for i:=65 to 90 do y:=y+[chr(i)];//большие буквы
    for i:=97 to 122 do z:=z+[chr(i)];//маленькие буквы

    if copy(s,i,3) = 'one' then k:=1 ;
    if (s[i+1] in z) and not (s[i] in z) then n:=n+1;//цифры
    if (s[i+1] in l) and not (s[i] in l) then m:=m+1; //буквы
    i:=i+1;//переходим к следующему символу
    end;
   if n>m then writeln('there are numbers more') else writeln('there are letters more');
   if k=1 then writeln('Y') else writeln('n');    readln;
end.}
