;data segment
;data1 segment
;col db 10h
;data1 ends
;data ends
code segment
assume cs:code;,ds:data
;mov ax,code
;mov cs,ax
;mov ax,data1
;mov ds,ax

mov ax,12
int 10h
;--------вывод на экран символа NUL разными цветами--------
mov dh,0 ;номер строки
mov dl,-1 ;номер столбца
mov bh,0 ;номер страницы
mov al,0h ;выводимый символ
mov cx,1 ;количество выводимых символов
mov bl,19 ;атрибуты (цвет и фон)
mov si,0 ;счетчик
mov ah,0
mov al,3
int 10h
mov al,0h
m2:
mov ah,2 ;графический режим
inc dl ;подвинуть курсор
int 10h ;вывод на экран
mov ah,9 ;установить другой режим
add bl,150 ;изменить атрибут символа
int 10h ;вывести символ на экран
inc si ;увеличить счетчик
cmp si,16 ;сравнить счетчик с 16
jne m2 ;если он меньше 16, то повторить цикл снова
;--------вывод разных символов ASCI--------
mov dh,1 ;номер строки
mov dl,-1 ;номер столбца
mov bh,0 ;номер страницы
mov al,0020h ;код символа
mov cx,1 ;количество выводимых символов
mov bl,219 ;атрибут цвета и фона символа
m1:
mov ah,2 ;установить видеорежим
inc dl ;подвинут курсор
int 10h ;вывести курсор на экран
mov ah,9 ;перейти в другой видеорежим
inc al ;перейти к следующему символу
int 10h ;вывести символ на экран
cmp al,00ffh ;сравнить код символа с 255
jne m1 ;если код меньше 255, то повторить цикл
;--------работа с мышью--------
xor ax,ax
int 33h
mov ax,0001H
int 33h
mov ax,0Ch
mov cx,00101h
push es
push cs
pop es
lea dx,prm
int 33h
pop es
pop ds
;--------ожидание ввода и завершение программы--------
mov ah,1
int 21h
;--------действие мыши--------
prm proc far
push ds
push es
mov ax, 0B800h
mov es,ax
mov ah,2
inc dl
int 10h
pop es
pop ds
ret
prm endp
code ends
end