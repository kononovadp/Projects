Dat Segment			
Greet DB 'Hello Word', 13,10,'$' 
DB 41, 42, 43, 44, 45	
x dw 0  
y dw 0
z dw 0
masc db 9	
mes1 db 'First string: Hello, World',13,10,'$'
mes2 db 'Second string: Hello, Assembler',13,10,'$'
col db 0h
sym db 0h
sym2 db 0h	
Dat Ends			
Code Segment			
Assume cs:Code, ds:Dat
mouse proc far
push ds
push cs
pop ds
mov ax,0b800h
mov es,ax
mov ax,seg greet
mov ds,ax
mov ax,0003h
int 33h
mov x,cx
mov y,dx
mov z,bx
mov ax,x
mov bl,8
div bl
mov x,al
mov y,dx
mov ax,y
mov bl,8
div bl
mov y,al
mov ah,2
mov dl,x
mov dh,y
int 10h
cmp z,1000b
je lkm
cmp z,10b
je rkm
;левая кнопка мыши
lkm:
mov ah,8
mov bh,0
int 10h
mov col,ah
pop ds
ret
;правая кнопка мыши
rkm:
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
pop ds
ret
mouse endp

Start: 
Assume cs:Code, ds:Dat
mov ax, Dat	        
mov ds, ax
;--------вывод на экран символа NUL разными цветами--------
mov dh,0 ;строка
mov dl,-1 ;столбец
mov bh,0 ;страница
mov al,0h
mov cx,1
mov bl,0b
mov si,0
mov ah,0
mov al,3
int 10h
mov al,0h
m2:
mov ah,2
inc dl
int 10h
mov ah,9
add bl,10000b
int 10h
inc si
cmp si,16
jne m2
;--------вывод текста на экран--------
;первая строка
mov dh,1
mov dl,0
mov ah,2
int 10h
mov ah,9
mov dx,offset mes1
int 21h
;вторая строка
mov dh,2
mov dl,0
mov ah,2
int 10h
mov ah,9
mov dx,offset mes2
int 21h
mov ah,2
mov dh,0
mov dl,0
int 10h
;--------работа с мышью--------
mov ax,0000h
int 33h
mov ax,0001h
int 33h
mov	ax,000ch	
mov	cx,1010b
mov	dx,offset mouse
push cs
pop es
int	33h
mov ah,1
int 21h
mov ah, 4ch		 
int 21h		
Code Ends
End Start