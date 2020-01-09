program sim;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

var chi : Char;

begin
  Writeln('Char (code) : ',  Ord(Low(Char)), '..',
           Ord(High(Char)), #13#10);
  for chi := #0 to #255 do
    Write(chi);
  Readln;
end.
