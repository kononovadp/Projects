.model compact
.386
.data
.stack
db 255
data1 segment
mes1 db 'First string: Hello, World',13,10,'$'
mes2 db 'Second string: Hello, Assembler',13,10,'$'
data1 ends
.code
code1:
mov ax,data1
mov ds,ax
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

;--------вывод текста на экран--------
;первая строка
mov dh,1 ;номер строки
mov dl,0 ;номер столбца
mov ah,2
int 10h ;подвинуть курсор на следующую строку
mov ah,9
mov dx,offset mes1
int 21h
;вторая строка
mov dh,2 ;номер строки
mov dl,0 ;номер столбца
mov ah,2
int 10h ;подвинуть курсор на следующую строку
mov ah,9
mov dx,offset mes2
int 21h
;--------работа с мышью--------
xor ax,ax
int 33h
mov ax,1
int 33h
mov ax,0Ch
mov cx,1001b
push es
push cs
pop es
lea dx,prm
int 33h
pop es
;--------ожидание ввода--------
mov ah,1
int 21h
;--------действие мыши--------
prm proc far
push ds
push es
pusha
mov ax, 0B800h
mov es,ax
pop es
mov ax, data1
mov ds,ax
pop ds
;действия мыши
mov ah,2 ;выбрать 2-ю функцию
mov dl,cx;inc dl ;передвинуть курсор
mov dh,dx
int 10h ;вывести курсор
popa
pop es
pop ds
retf
prm endp
end code1