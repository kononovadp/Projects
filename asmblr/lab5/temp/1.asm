code segment
assume cs:code
   MOV  AH,14             ;функция записи с атрибутами
   MOV  BH,0             ;страница 1
   MOV  AL,0020h   ;символ в AL
   MOV  BL,194;110           ;атрибуты в BL
   MOV  CX,1             ;вывести один раз
   m1:
   INT 10H ;вывести на экран
   inc al ;перейти на следующий символ
   cmp al,00FFh ;если код символа меньше 255, 
   jne m1 ;то вывести следующий символ
   mov ah,1 ;ожидание ввода
   int 21h
code ends
end