program ariphm;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

var x, y  : integer;

begin
  Write('x = ');
  ReadLn(x);
  Write('y = ');
  ReadLn(y);
  WriteLn('x + y = ', x + y);
  WriteLn('x - y = ', x - y);
  WriteLn('x * y = ', x * y);
  if y <> 0 then
  WriteLn('x / y = ', x / y:5:5)
  else
  WriteLn('Error: Division by ZERO!!!');
  ReadLn;
end.
