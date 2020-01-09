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
data ends
code segment
code1 segment
assume ds:data1,cs:code1
m1: cli
or const1,255 ;8-8
or const6,65530 ;16-16
or const8,655350 ;32-32
jb m1
code1 ends
code ends
end