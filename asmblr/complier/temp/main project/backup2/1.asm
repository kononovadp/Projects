data segment
Data1 segment
name1 db 'Hello'
field1 dw 3131h
Data1 ends
Data2 segment
const dd 4242q
const2 db 1011b
data2 ends
data ends
code segment
code1 segment
assume ds:data1,cs:code1
inc cx
dec di
adc bh,bl
cmp dx,80h
jb
assume ds:data2,cs:code1
xor al,01h
cmp dx,1010b
jb
sal di,1
or dh,cl
cli
code1 ends
code ends
end