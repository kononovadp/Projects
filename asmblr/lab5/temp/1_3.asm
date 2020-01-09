code segment
assume cs:code
mov dh,1
mov dl,1
mov bh,0
mov al,0020h
mov cx,1
mov bl,219
m1:
mov ah,2
inc dl
int 10h
mov ah,9
inc al
int 10h
cmp al,00FFh
jne m1
;----------
mov dh,0
mov dl,0
mov bh,0
mov al,0h
mov cx,1
mov bl,19
mov si,1
m2:
mov ah,2
inc dl
int 10h
mov ah,9
add bl,100
int 10h
inc si
cmp si,10
jne m2

mov ah,1
int 21h
code ends
end