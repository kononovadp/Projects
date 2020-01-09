{10. Текстовий файл  f містить відомості про студентів курсу у наступному вигляді:
     прізвище  ім’я   по батькові. Записати ці відомості до файлу g за зразком:
     ім’я   по батькові   прізвище.}
program z1;
var f,g:text; s,prisv,impob:string; k,i,l,n:byte; ch:char;
  begin
    assign(f,'file-f.txt');reset(f); //prisv:='';
  while not (eof(f)) do begin
     readln(f,s);prisv:=s; impob:=s;
     for i:=1 to length(prisv) do
     if prisv[i]=' ' then delete(prisv,i+1,length(prisv)-i);
     for i:=1 to length(impob) do
     if (impob[i]=' ') then delete(impob,1,i);
     write(impob,' ',prisv);writeln;
  end;
      readln;
      end.
