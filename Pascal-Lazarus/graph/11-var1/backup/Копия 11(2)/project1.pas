PROGRAM lab7;
USES CRT,Graph;
CONST
M : ARRAY [1.. 3] OF STRING = ('Просмотр в 2-D','Просмотр в3D', 'Выход' );

VAR
	I, A,gd,gm : INTEGER;
	C : CHAR;



procedure Zastavka;
begin
clrscr;
 writeln('          Сведения о программе: ');
 writeln;
 writeln('Программа позволяет: ');
 writeln;
 writeln('построить изображение буквы Ж ');
 writeln;
 writeln('на плоскости и в пространстве. ');
 writeln;
 writeln('Создана студентом... ');
 writeln;writeln;
 writeln;
 writeln(' Для продолжения нажмите ENTER ');
 readln;
end;

procedure d2;
begin
clrscr;
gd:=detect; InitGraph(gd,gm,'c:\lazarus\fpc\2.6.4\units\i386-win32\graph\');
setlinestyle(0,0,3); setfillstyle(1,15);
moveto(120,120);
lineto(380,380); lineto(390,380); lineto(130,120); lineto(120,120);
floodfill(130,121,15);
moveto(120,380);
lineto(380,120); lineto(390,120);lineto(130,380); lineto(120,380);
floodfill(130,375,15);  floodfill(380,125,15);
bar(250,120,260,380);
readln;
closegraph;
end;


procedure d3;
var dx,dy:integer;
begin
dx:=25;dy:=15;
clrscr;
gd:=detect; InitGraph(gd,gm,'C:\FPC\2.6.4\units\i386-win32\graph');
setlinestyle(0,0,3); setfillstyle(1,15);
moveto(200,120);
lineto(380,380); lineto(390,380); lineto(210,120); lineto(200,120);
floodfill(210,121,15);

moveto(200,380);
lineto(380,120); lineto(390,120);lineto(210,380); lineto(200,380);
floodfill(210,375,15);  floodfill(380,125,15);

bar(288,120,296,380);

moveto(200,120); linerel(-dx,dy); lineto(380-dx,380+dy); linerel(dx,-dy);
moveto(390,380);linerel(-dx,dy); linerel(-10,0);

moveto(380,120); linerel(-dx,dy); lineto(200-dx,380+dy); linerel(dx,-dy);
moveto(210,380);linerel(-dx,dy); linerel(-10,0);

moveto(288,120); linerel(-dx,dy); lineto(288-dx,380+dy); linerel(dx,-dy);
moveto(296,380);linerel(-dx,dy); linerel(-8,0);

readln;
closegraph;
end;

procedure menu;
        BEGIN
	A :=1;
        repeat
        TEXTBACKGROUND ( 1 );
	 CLRSCR;
	GOTOXY ( 20, 5 );
	TEXTCOLOR ( 14 );
	WRITELN ('--Выберите вариант построения изображения-- ');
	GOTOXY ( 2, 23 );
	WRITE ('   ',CHR ( 24 ) , CHR(25));
	WRITE (' -  ENTER. ESC' );
	TEXTCOLOR ( WHITE );
      	FOR I := 1 TO 3 Do
		BEGIN
		IF A = I THEN
    				TEXTBACKGROUND ( 3 )

				ELSE
				TEXTBACKGROUND ( 4 );
		GOTOXY (30, 9 + 2*I );
		WRITELN ( M [ I ]);
		END;
	C := READKEY;
	IF C = #0 THEN C := READKEY;
	CASE C OF
			#80 :
				BEGIN
				INC ( A );

				IF A > 3 THEN A := 1;
				END;

			#72 :	BEGIN
				DEC ( A );
				IF A < 1 THEN A :=3;
				END;

			#13 : 	BEGIN  clrscr;
				CASE A OF
                                	1 :d2  ;

					2 : d3 ;

					3: Halt;
				END; {#13}
	END; {case}
	END;

UNTIL C = #27;
end {menu};





begin
     zastavka;
     menu;
END.

