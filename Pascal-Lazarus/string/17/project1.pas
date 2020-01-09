{17. Задано непустий текст довжиною до 255 символів. Виконати над кожним
словом тексту наступні дії. Всі повторні входження першого символа слова
замінити словом “ТАК”. Якщо повторних входжень немає, то перший символ слова
замінити словом “НІ”. Гарантується, що після всіх замін довжина рядка не буде
перевищувати 255 символів.}
program z1;
var s,k,n:string; i,m:byte; p:boolean;
  begin
  i:=1; p:=false; k:='';
  read(s);  s:=s+' ';
  while i<length (s) do
  begin
      while s[i]<> ' ' do begin k:=k+ s[i]; i:=i+1;    end;
      m:=2;
      while m< length(k) do
      if k[1]=k[m] then begin delete(k,m,1); insert('yes',k,m); m:=m+3; p:=true; end
      else m:=m+1;
      if p<> true then begin
      delete(k,1,1); insert('no',k,1); end;
      n:=n+k+' ' ; k:='';i:=i+1; p:=false;

  end;      write(n);
readln;  readln;
end.
