program mytypes;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes
  { you can add units after this };

type TMyInteger = Integer;
type TMyChar = 'a'..'z';
type TMyCars = (VAZ, GAZ, UAZ, MAZ, KAMAZ, BMW, MERSEDES, AUDI);


begin
  Writeln('Integer     : ', Low(Integer), '..', High(Integer));
  Writeln('TMyInteger  : ', Low(TMyInteger), '..', High(TMyInteger));
  Writeln('TMyChar     : ', Low(TMyChar), '..', High(TMyChar));
  Writeln('TMyCars     : ', Low(TMyCars), '..', High(TMyCars));

  Readln;
end.
