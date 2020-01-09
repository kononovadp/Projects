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
x dt 0
y dt 0
current_gy dw 190
current_gx dw 10 
color db 10
color_g db 13  
max_x dw 320
max_y dw 200
scalemax_x dw 8
scalemin_x dw -8
scalemax_y dw 4
scalemin_y dw -4
kx dt 0
ky dt 0
scalex dw 20
scaley dw 25
sd dt 1
LineLengthx dw ?
LineLengthY dw ?
gradq_x dw 0
gradq_y dw 0
temp dt 0
hundert dw 100
.code
line_x proc
mov dx,max_x
sub dx,currentx
sub dx, currentx
mov linelengthx,dx
mov ax,max_y
mov bl,2
div bl
cbw 
mov currenty,ax
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
pop cx
loop L1
ret
line_x endp

line_y proc
LineLength = 180
mov dx,10
mov currentY,dx
mov cx,LineLength 
L2:
push cx
mov ah,0Ch  
mov al,color 
mov bh,0 
mov cx,160
mov dx,currenty
int 10h
inc currenty 
pop cx
loop L2
ret
line_y endp

scale_x proc
LineLength = 10
mov dx,95
mov currentY,dx
mov cx,LineLength 
L3:
push cx
mov ah,0Ch  
mov al,color 
mov bh,0 
mov cx,gradq_x
mov dx,currenty
int 10h
inc currenty 
pop cx
loop L3
ret
scale_x endp

scale_y proc
LineLength = 10
;mov gradq_y,10
mov dx,155;95
mov currentY,dx
mov cx,LineLength 
L4:
push cx
mov ah,0Ch  
mov al,color 
mov bh,0 
mov cx,currenty;gradq_y
mov dx,gradq_y;currenty
int 10h
inc currenty 
pop cx
loop L4
ret
scale_y endp

;функция x=y
xeqy proc
LineLength = 180
mov ax,scalemin_x
mov x,ax;10;70
mov current_gx,0;190
mov dx,current_gx;current_gy
mov cx,current_gy;LineLength 
L5:
push cx
mov ah,0Ch  
mov al,color_g 
mov bh,0 
mov cx,current_gx
mov dx,current_gy
int 10h
inc current_gx
add x,kx
fld x
fsin
fstp temp
fld x
fcos
fstp y
fld temp
fmult y
fstp y
fld y
fmult scaley
frndint
fstp current_gy
fild hundert
fisub current_gy
fstp current_gy


;dec current_gy 
pop cx
loop L5
ret
xeqy endp
start:
mov ax,@data
mov ds,ax
;mov ah,0Fh
;int 10h
;mov saveMode,al
mov ah,0 
mov al,Mode_19 
int 10h
call line_x
call line_y
finit
fild scalemax_x
fisub scalemin_x
fstp kx
fld kx
fidiv max_x
fstp kx


fild scalemax_y
fisub scalemin_y
fstp ky
fld ky
fidiv max_y
fstp ky

;fild sd
;fdiv kx
;frndint
;fbstp scalex
m2:
mov si,scalex
add gradq_x,si
call scale_x
cmp gradq_x,320
jne m2
m3:
mov si,scaley
add gradq_y,si
call scale_y
cmp gradq_y,200
jne m3
call xeqy
;====================
mov ah,0
int 16h
mov ah,0 
mov al,saveMode 
int 10h
mov ax,4c00h
int 21h
end start