{7.Задано непустий текст довжиною до 255 символів. Кожен символ тексту може
бути малою латинською літерою, цифрою або одним із знаків “+”, “–“, “*”. Необхідно:
а) з’ясувати, чи зустрічається в даному тексті група літер “one”;
б) з’ясувати, чого більше в заданому тексті: груп знаків чи груп цифр.}
program z1;
var s:string; i,n,m,k:byte;  z,l:set of char;
  begin
    readln(s); s:=s+' ';
    for i:=0 to 9 do z:=z+[chr(i+48)];
    for i:=97 to 122 do l:=l+[chr(i)];

    k:=0;
    n:=0; m:=0; i:=1;
    if s[1] in z then n:=n+1;
    if s[1] in l then m:=m+1;

    while i<length(s) do
    begin
    if copy(s,i,3) = 'one' then k:=1 ;
    if (s[i+1] in z) and not (s[i] in z) then n:=n+1;//цифры
    if (s[i+1] in l) and not (s[i] in l) then m:=m+1; //буквы
    i:=i+1;//переходим к следующему символу
    end;
   if n>m then writeln('there are numbers more') else writeln('there are letters more');
   if k=1 then writeln('Y') else writeln('n');    readln;
end.
