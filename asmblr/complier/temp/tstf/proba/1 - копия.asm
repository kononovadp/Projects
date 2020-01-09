data segment
Data1 segment
const db 1101b
const1 db 125
const2 db 85h
const3 db 'Hello'
const4 dw 1010b
const5 dw 0;201
const6 dw 98h
const7 dd 1011b
const8 dd 0;1010
const9 dd 1000h
Data1 ends
data ends
code segment
code1 segment
assume ds:data1,cs:code1
m1: cli
or const1,255 ;8-8
or const5,6553727 ;16-16
or const8,4294967295;65535056 ;32-32
or const5,127 ;16-8
or const8,127 ;32-8
jb m1
code1 ends
code ends
end