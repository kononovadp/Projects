program perem;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

{ Объявляем константы }
const X1 = 100;
      X2 = 50;
      SIM = 'Z';

{ Объявляем переменные }
var x       : byte;
    Simbol  : Char;

begin
  WriteLn('X1 = ', X1, ', X2 = ', X2);
  WriteLn('X1 + X2 = ', X1 + X2);
  Write('X = ');
  ReadLn(x);
  WriteLn('X1 + X2 + X = ', X1 + X2 + x);
  Write('Simbol = ');
  ReadLn(Simbol);
  WriteLn('Simbol + SIM = ', Simbol + SIM);
  ReadLn;
end.
