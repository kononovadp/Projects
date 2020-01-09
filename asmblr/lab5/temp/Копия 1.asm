code segment
   MOV  AH,9             ;функция записи с атрибутами
   MOV  AL,0057h   ;символ в AL
   MOV  BL,110           ;атрибуты в BL
   MOV  BH,0             ;страница 1
   MOV  CX,16             ;вывести один раз
   INT  10H
   mov ah,1
   int 21h
code ends
end