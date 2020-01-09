.model compact
.data
.stack
db 255
data1 segment
mes1 db 'First string: Hello, World',13,10,'$'
mes2 db 'Second string: Hello, Assembler',13,10,'$'
col dw 0h
sym db 0h
sym2 db 0h
data1 ends
.code
code1:
mov ax,data1
mov ds,ax
;--------вывод на экран символа NUL разными цветами--------
mov dh,0 ;номер строки
mov dl,-1 ;номер столбца
mov bh,0 ;номер страницы
mov al,55h;0h ;выводимый символ
mov cx,1 ;количество выводимых символов
mov bl,0b;19 ;атрибуты (цвет и фон)
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
add bl,10000b;150 ;изменить атрибут символа
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
mov ah,2
mov dh,0
mov dl,0
int 10h
mov ah,1
int 21h
;--------работа с клавиатурой--------
keyboard:
mov ah,0
int 16h
mov sym,ah
cmp sym,4Dh
je right
cmp sym,4Bh
je left
cmp sym,48h
je up
cmp sym,50h
je down
cmp sym,39h
je backspace
cmp sym,1Ch
je ent
cmp sym,01h
je exit
right:
mov ah,2
inc dl
int 10h
cmp sym,4Dh
je keyboard
left:
mov ah,2
dec dl
int 10h
cmp sym,4Bh
je keyboard
up:
mov ah,2
dec dh
int 10h
cmp sym,48h
je keyboard
down:
mov ah,2
inc dh
int 10h
cmp sym,50h
je keyboard
backspace:
mov ah,8
mov bh,0
int 10h
mov col,ah
cmp sym,39h
je keyboard
ent:
mov ah,8
mov bh,0
int 10h
mov sym2,al
mov ah,9
mov al,sym2
mov bl,col
mov cl,4
shr bl,cl
mov bh,0
mov cx,1
int 10h
jmp keyboard
exit:
int 20h
end code1