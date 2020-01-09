{Задано непустий текст довжиною до 255 символів. Виконати над кожним словом
тексту наступні дії. Якщо слово не містить у собі символа “*”, то залишити цей
текст без змін. Інакше кожну з малих латинських літер, що передують першому
входженню символа “*”, замінити на цифру “3”.}
program z1;
var s,b:string; i,n,p,f:byte;ch:char;
  begin
    readln(s); s:=s+' ';

    ch:='*';
    n:=0; i:=1; p:=1;
    while i<length(s) do
    begin
    while s[i]<>' ' do begin  //движение до пробела
    if s[i] = ch then n:=n+1; //подсчет символов
    i:=i+1;//переходим к следующему символу
    end;
    f:=1;
      if n >0 then   //были найдены *
         while p<i do
          begin
          if (s[p]>'a') and (s[p]<'z') and (f=1) then s[p]:='3';
         if (s[p]=ch) then f:=0;
         p:=p+1
           end ;
     write(n:5);
    i:=i+1;  n:=0;
     end;
   writeln; write(s); readln;
    readln;
  end.


