data segment
CONST db 1101b
CONST1 db 125
CONST2 db 85h
CONST3 db 'Hello'
CONST4 dw 1010b
CONST5 dw 2015d
CONST6 dw 98h
CONST7 dd 1011b
CONST8 dd 1010
CONST9 dd 1000h
data ends
code segment
assume ds:data,cs:code
m1: cli
inc bh
inc cx
inc esi
dec CONST2
dec CONST9
dec CONST[si]
dec CONST1[si+15]
dec CONST2[di+125]
dec CONST3[di+186]
dec CONST4[bx+20]
dec CONST5[bx+15557]
dec CONST6[esi+65446]
dec CONST7[edi+82]
dec CONST8[ebx+23]
dec CONST9[esi+126]
adc bh,cl
adc bx,dx
adc ecx,ebx
cmp bh,CONST
cmp bl,CONST1[bx]
cmp cl,CONST2[bx+85]
cmp dh,CONST3[bx+di+63218]
cmp dx,CONST4[esi]
cmp bx,CONST5[edi+28]
cmp cx,CONST6[bp+97]
cmp esi,CONST7[ebp+125]
cmp edx,CONST8[edi+215]
cmp ecx,CONST9[ebp+52316]
jb m2
xor bh,CONST
xor bl,CONST1
xor cl,CONST2
xor dh,CONST3
xor dx,CONST4
xor bx,CONST5
xor cx,CONST6
xor esi,CONST7
xor edx,CONST8
xor ecx,CONST9
m2: sal cl,1010b
sal cx,232
sal ebx,79h
or CONST1,11111111b ;8-8
or CONST5,65407 ;16-16
or CONST8,9fffh ;32-32
or CONST5,127 ;16-8
or CONST8,7fh ;32-8
jb m1
cli
code ends
end