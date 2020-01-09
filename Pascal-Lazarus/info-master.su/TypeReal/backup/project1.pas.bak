program interval;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type TMyInt = -100..100;
type TMyChar = 'a'..'z';
type TMyCharCode = #97..#122;

begin
  Writeln('TMyInt : ', Low(TMyInt), '..', High(TMyInt));
  Writeln('TMyChar : ', Low(TMyChar), '..', High(TMyChar));
  Writeln('TMyCharCode : ', Low(TMyCharCode), '..', High(TMyCharCode));
  ReadLn;
end.
