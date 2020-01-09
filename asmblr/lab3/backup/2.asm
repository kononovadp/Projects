;Шаблон структуры программы с использованием стандартных директив сегментации
;(поддерживает использование более одного сегмента кодов и данных)
Node struc
namex db 4 dup (0ffh)
field1 dw 2 dup (0)
Node ENDS
data segment 
Data1 segment
I_struc db ?
A0 Node <>
A1 Node 2 dup (<>)
A2 Node 4 dup (<>)
A3 Node 8 dup (<>)
Data1 ends
data2 segment
B0 Node <>
B1 Node 2 dup (<>)
B2 Node 4 dup (<>)
B3 Node 8 dup (<>)
data2 ends
data ends
code segment
code1 segment
assume ds:data1,cs:code1 ;установка связи с необходимыми сегментами кодов и данных
mov bx,1 ;пример команды первого сегмента кодов, ее не видно в отладчике
code1 ends
code2 segment
assume ds:data1,cs:code1 ;установка связи с необходимыми сегментами кодов и данных
mov cx,2 ;пример команды второго сегмента кодов, ее не видно в отладчике
code2 ends
code ends
end