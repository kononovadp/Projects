{10. Текстовий файл  f містить відомості про студентів курсу у наступному вигляді:
     прізвище  ім’я   по батькові. Записати ці відомості до файлу g за зразком:
     ім’я   по батькові   прізвище.
11. Вхідні  дані такі  ж, як у варіанті 10. Записати відомості до файлу g за зразком:
Прізвище  І.П. }
program z1;
var f,g:text; s,fam,im,ot,s5:string; k,i,l,n:byte; ch:char;
  begin
    assign(f,'text.txt');reset(f); fam:='';
  //while not (eof(f)) do begin
      readln(f,s);   fam:=s;//begin
  for i:=1 to length(fam) do if s[i]=' ' then delete(fam,i,length(fam)-i+1); //end;
     im:=s;
  for k:=1 to length(im) do if im[k]=' ' then

   begin {delete(im,k+2,length(im)-k+1);} insert('.',im,k+2);end;
  ot:=im;
   while ot[l]<>'.' do begin delete(ot,l,1);l:=l-1; end;
   s5:=ot;
   for n:=1 to length(s5) do if s5[n]='.' then delete(s5,n+1,length(s5)-n-2);
   writeln(s); {writeln(fam); writeln(im);writeln(ot);} writeln(s5);
   //end;
   close(f); //close(g);

      readln;
      end.
