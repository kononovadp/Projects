data segment
const db 1101b
const1 db 125
const2 db 85h
const3 db 'Hello'
const4 dw 1010b
const5 dw 2015d
const6 dw 98h
const7 dd 1011b
const8 dd 1010
const9 dd 1000h
data ends
code segment
assume ds:data,cs:code
m1: cli
inc bh
inc cx
inc esi
dec const2
dec const9
dec const[si]
dec const1[si+15]
dec const2[di+125]
dec const3[di+186]
dec const4[bx+20]
dec const5[bx+15557]
dec const6[esi+65446]
dec const7[edi+82]
dec const8[ebx+23]
dec const9[esi+126]
adc bh,cl
adc bx,dx
adc ecx,ebx
cmp bh,const
cmp bl,const1[bx]
cmp cl,const2[bx+85]
cmp dh,const3[bx+di+63218]
cmp dx,const4[esi]
cmp bx,const5[edi+28]
cmp cx,const6[bp+97]
cmp esi,const7[ebp+125]
cmp edx,const8[edi+215]
cmp ecx,const9[ebp+52316]
jb m2
xor bh,const
xor bl,const1
xor cl,const2
xor dh,const3
xor dx,const4
xor bx,const5
xor cx,const6
xor esi,const7
xor edx,const8
xor ecx,const9
m2: sal cl,1010b
sal cx,232
sal ebx,79h
or const1,11111111b ;8-8
or const5,65407 ;16-16
or const8,9fffh ;32-32
or const5,127 ;16-8
or const8,7fh ;32-8
jb m1
cli
code ends
end