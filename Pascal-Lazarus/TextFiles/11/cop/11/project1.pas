{10. Текстовий файл  f містить відомості про студентів курсу у наступному вигляді:
     прізвище  ім’я   по батькові. Записати ці відомості до файлу g за зразком:
     ім’я   по батькові   прізвище.
11. Вхідні  дані такі  ж, як у варіанті 10. Записати відомості до файлу g за зразком:
Прізвище  І.П. }
program z1;
var f,g:text; s,s2,s3:string; k,i,l,n:byte; ch:char; letters:set of char;
  begin
    for ch:='A' to 'Z' do letters:=letters+[ch];
    assign(f,'file-f.txt');reset(f);
    assign(g,'file-g.txt');rewrite(g);
  while not (eof(f)) do begin
      readln(f,s);
      for i:=1 to length(s) do begin
      if (s[i] = ' ') and (s[i+1] in letters) then s2:=s2+s[i+1];
      if s[i] = ' ' then delete(s,i,length(s)-i+1);
      s3:=s+' '+s2;
      writeln('S=',s,'  S2=',s2,'  s3=',s3); readln;end;
      for k:=1 to length(s3) do begin
      if s3[k]=' ' then begin insert('.',s3,k+2); insert('.',s3,k+4);end;
      end;
      writeln(g,s3); s2:='';
  end;
      close(f); close(g);
  assign(g,'file-g.txt');reset(g);
  while not (eof(g)) do begin
      readln(g,s); writeln(s);
      end;
  close(g); readln;
      end.
