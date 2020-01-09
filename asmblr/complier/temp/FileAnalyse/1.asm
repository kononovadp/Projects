data segment
Data1 segment
name1 db 'Hello'
field1 dw 3131h
Data1 ends
data2 segment
const dd 4242q
const2 db 1011b
data2 ends
data ends
code segment
code1 segment
assume ds:data1,cs:code1 
inc cx
@5: dec di
adc bh,bl
cmp dx,80h
jb @5
code1 ends
code2 segment
assume ds:data2,cs:code2
xor al,01h
cmp dx,1010b
jb @6 
sal di,1
@6: or dh,cl
code2 ends
code ends
end