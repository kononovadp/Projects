code segment
mov ah,0
mov al,12
int 10h
mov ah,5
mov al,0
int 10h
mov ah,4Ch
mov ah,1
int 21h
code ends
end