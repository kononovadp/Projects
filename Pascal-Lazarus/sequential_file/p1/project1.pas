{1. Видалити та перейменувати файл}
program z1;
var f:file of integer;
  ch: char;
  st:string;
  begin
    write('enter name of file  ');
    readln(st);
    assign(f,st); rewrite(f);
    writeln('enter d to delete file');
    writeln('enter p to rename file');
    writeln('enter e to exit');
    readln(ch);
    case ch of
    'd','D':begin erase(f); writeln('file was deleted'); readln; exit; end;
    'p','P': begin write('enter a name    ');
      readln(st);
      rename(f,st); assign(f,st); rewrite(f); writeln('file was renamed to ',st); readln; exit; end;
    'e','E':exit;
    end;
  end.

