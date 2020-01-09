.model flat
.data
const db 1101b
const1 db 125
const2 db 85h
const3 db 'Hello'
const4 dw 1010b
const5 dw 2015d
const6 dw 98h
const7 dd 1011b
const8 dd 1989
const9 dd 239h
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
.stack 256h
.code
inc cx
@m1: dec di
adc bh,bl
cmp dx,80h
jb @m2
xor al,01h
adc ax,si
cmp dx,1010b
jb @m1
sal di,1
or dh,cl
@m2: cli
end