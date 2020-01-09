{9. Задано непустий текст довжиною до 255 символів. Кожен символ тексту може
бути малою латинською літерою, цифрою або одним із знаків “+”, “–“, “*”.
Необхідно:
а) знайти кількість таких груп літер, які починаються та закінчуються на одну й
ту ж літеру;
б) знайти найдовшу групу цифр (якщо найбільшу довжину мають декілька груп, то
взяти першу з них).}
program z1;
var k,s:string; i,n,m,p,g:byte;  z,y:set of char;
  begin
    readln(s); s:=s+' ';
    for i:=0 to 9 do z:=z+[chr(i+48)];//группа цифр
    for i:=97 to 122 do y:=y+[chr(i)];//группа букв
    g:=0; m:=0;  i:=1;
  while i < length(s) do begin
     k:='';
     //группа букв
    while (s[i] in y)  do begin k:=s[i]+k; i:=i+1;  end;
    n:=length(k);
    if k<>'' then    if k[1]=k[n] then g:=g+1;
    //группа цифр
    n:=0;
    while (s[i] in z)  do begin i:=i+1; n :=n+1;end;
    if n>m then m:= n;

    //группа символов
    if i<> length(s) then
        while not(s[i] in z) and  not(s[i] in y) do i:=i+1;
    end;
    writeln('num   ', m,',  letters:',g);
    readln; end.
