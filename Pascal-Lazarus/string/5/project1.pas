{5.Задано непустий текст довжиною до 255 символів. Виконати над кожним
словом тексту наступні дії. Якщо в слові певний символ зустрічається більш ніж
чотири рази, то вилучити зі слова три перші входження цього символа, якщо ж
символ зустрічається більше, ніж вісім разів, то вилучити три останні його
входження.}
program z1;
var s,b:string; i,n,p,f:byte;ch:char;
  begin
    readln(s); s:=s+' ';

    readln(ch);
    n:=0; i:=1; p:=1;
    while i<length(s) do
    begin
    while s[i]<>' ' do begin  //движение до пробела
    if s[i] = ch then n:=n+1; //подсчет символов
    i:=i+1;//переходим к следующему символу
    end;  writeln('*');
    f:=0;//счетчик пройденных нужных символов
      if (n>=4) and (n<8) then
         while p<i do
         if (s[p]=ch)
         then
            if f<3
            then begin   delete(s,p,1) ; f:=f+1;
              i:=i-1;//сдвигаем указатель на пробел после удаления символа
            end  else p:=p+1
            else  p:=p+1;

        if n>=8 then begin
          n:=n-3;//сколько нужно оставить символов
          while p<i do
         if (s[p]=ch)
         then
            if f>=n  // f - количество пройденных нужных символов
            then begin   delete(s,p,1) ; f:=f+1;
              i:=i-1;//сдвигаем указатель на пробел после удаления символа
            end
            else begin p:=p+1; f:=f+1; end
        else p:=p+1;
         end;
      end;
    writeln(s); readln;;
    end.
{if n >4 then begin  //действия при четном n

         delete(s,n,3);
              i:=i-1;//сдвигаем указатель на пробел после удаления символа
              write(s); readln; end; end; end; end.
            end
         else p:=p+1;  //завершение работы при четном n
        write(s); readln; end; end.
      //действия при нечетном n
      else
         begin
         while p<i do
         if (s[p]=ch)
         then
             begin   insert(ch,s,p);
              p:=p+2;//переходим на два имвола после вставки
              i:=i+1;//сдвигаем указатель на пробел после удаления символа
            end
         else p:=p+1  //завершение работы при четном n

      end;
    write(n:5);
    i:=i+1;  n:=0;
     end;
   writeln; write(s); readln;
    readln;
  end.}
