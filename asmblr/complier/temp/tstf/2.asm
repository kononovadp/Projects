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
const8 dd 1989
const9 dd 239h
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
m1:Cli
Inc cx
Dec const5
jb m2
adc bx,dx
Cmp cx,[8]
Xor [const4],dx
Sal ax,1
m2:Or const4,65
Jb m1
code1 ends
code ends
end