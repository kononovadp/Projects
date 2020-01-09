code segment
assume cs:code
MOV  AH,9             ;функция записи с атрибутами
MOV  BH,0       ;страница 1
MOV  CX,1       ;вывести один раз
m1:
MOV  AL,0057h   ;символ в AL
MOV  BL,110     ;атрибуты в BL
inc cx
;cmp cx,10
INT  10H
;jne m1
loop m1
mov ah,1
int 21h
code ends
end