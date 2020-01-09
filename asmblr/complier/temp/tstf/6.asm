.model flat
.data
Data1 segment
const dd 96
const1 dw 96
const2 db 96
Data1 ends
.stack 256h
.code
mov ax,data1
mov ds,ax
end