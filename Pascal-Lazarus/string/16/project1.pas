{16. Задано непустий текст довжиною до 255 символів. З’ясувати, чи є кожне слово
тексту правильно записаним ідентифікатором. Підрахувати кількість правильних та
неправильних ідентифікаторів.}
program z1;
var s:string; i,n,m,k,p:byte; y,x:set of char; a:array[1..20] of string; pr:boolean;
  begin
  for i:=49 to 57 do y:=y+[chr(i)];//цифры
    for i:=65 to 90 do x:=x+[chr(i)];//большие буквы
    for i:=97 to 122 do x:=x+[chr(i)];//маленькие буквы
    y:=x+['_']+y;
  p:=0;
   i:=0;
writeln('enter number of identifiers');
read(n);
writeln('write strings');
for i:=0 to n do readln(a[i]);
writeln('OK');
for i:=1 to n do
begin
pr:=true;
if not(a[i][1] in x) then pr:=false
else
  for k:=2 to length(a[i]) do if not(a[1][k] in y) then pr:=false;
  if pr then p:=p+1;
  //writeln (a[i],' ',p);
end;
write('correct identifiers: ',p,'  incorrect identifiers: ',n-p);

readln;
end.
