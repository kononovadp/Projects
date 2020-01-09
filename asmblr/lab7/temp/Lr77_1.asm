model small
.stack 100h 
.386


Mode_6 = 6 ; 640 X 200, 2 colors 
Mode_13 = 0Dh ; 320 X 200, 16 colors 
Mode_14 = 0Eh ; 640 X 200, 16 colors 
Mode_15 = 0Fh ; 640 X 350, 2 colors 
Mode_16 = 10h ; 640 X 350, 16 colors
Mode_17 = 11h ; 640 X 480, 2 colors 
Mode_18 = 12h ; 640 X 480, 16 colors 
Mode_19 = 13h ; 320 X 200, 256 colors
Mode_6A = 6Ah ; 800 X 600, 16 colors 

.data
SaveMode db ?
currentX dw 10 
currentY dw 10 
current_gy dw 190
current_gx dw 10 
color db 10
color_g db 13  
max_x dw 320
max_y dw 200
LineLengthx dw ?
LineLengthY dw ?

.code
start:




main proc
 mov ax,@data
 mov ds,ax


mov ah,0Fh
int 10h
mov saveMode,al


mov ah,0 
mov al,Mode_19 
int 10h

call l_x
call l_y
call l_xy

mov ah,0
int 16h


mov ah,0 
mov al,saveMode 
int 10h

mov ax,4c00h
int 21h
main endp

l_x proc
mov dx,max_x
sub dx,currentx
sub dx, currentx
mov linelengthx,dx

mov ax,max_y
mov bl,2
div bl
cbw 
mov currenty,ax
;LineLengthx = 100
mov dx,currentY
mov cx,LineLengthx 
L1:
push cx
mov ah,0Ch  
mov al,color 
mov bh,0 
mov cx,currentX
int 10h
inc currentx
;inc color 
pop cx
loop L1
ret
l_x endp

l_y proc
LineLength = 180
mov dx,10
mov currentY,dx
mov cx,LineLength 
L2:
push cx
mov ah,0Ch  
mov al,color 
mov bh,0 
mov cx,10  ;currentX
mov dx,currenty
int 10h
;inc currentx
;inc color
inc currenty 
pop cx
loop L2
ret
l_y endp

l_xy proc
LineLength = 180
mov dx,current_gy
mov cx,LineLength 
L3:
push cx
mov ah,0Ch  
mov al,color_g 
mov bh,0 
mov cx,current_gx
mov dx,current_gy
int 10h
inc current_gx
;inc color
dec current_gy 
pop cx
loop L3
ret
l_xy endp


call main

end start

 