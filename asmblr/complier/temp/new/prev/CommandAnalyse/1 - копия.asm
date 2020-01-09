data segment
Data1 segment
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
Data1 ends
Dat2 segment
const10 db 'world!'
const11 db 14h
const12 db 57
const13 db 101110b
const14 dw 980h
const15 dw 205d
const16 dw 110011b
const17 dd 4568h
const18 dd 2010
const19 dd 11110001b
Dat2 ends
data ends
code segment
code1 segment
assume ds:data1,cs:code1
m1: cli
inc bh
inc cx
inc esi
dec const
dec const1
dec const2
dec const3
dec const4
dec const5
dec const6
dec const7
dec const8
dec const9
adc bh,cl
adc bx,dx
adc ecx,ebx
cmp bh,const
cmp bl,const1
cmp cl,const2
cmp dh,const3
cmp dx,const4
cmp bx,const5
cmp cx,const6
cmp esi,const7
cmp edx,const8
cmp ecx,const9
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
code1 ends
code ends
end