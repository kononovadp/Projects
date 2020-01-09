data segment
Data1 segment
name1 db 'Hello'
field1 dw 3131h
Data1 ends
data2 segment
qwer db 1010b
asdf db 1010b
zxcv db 'hello'
rtyu db 1010b
qwer1 dw 1010h
asdf1 dw 1010h
zxcv1 dw 2020h
rtyu1 dw 1010
qwer2 dd 1010
asdf2 dd 1010h
zxcv2 dd 2020
rtyu2 dd 1010b
qwer5 db 1010b
asdf5 db 1010b
zxcv7 dw 2020h
zxcv9 dw 2020
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
adc ax,si
cmp dx,1010b
jb
sal di,1
or dh,cl
cli
code1 ends
code ends
end