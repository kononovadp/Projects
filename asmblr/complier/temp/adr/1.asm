data segment 
;Data1 segment
a db 10 dup(?)
;Data1 ends
data ends
code segment
;code1 segment  ;выполнение задания 1
assume ds:data,cs:code
@start:
mov ax,data
mov ds,ax
mov cx,10
mov si,0
mov di,0
mov bx,offset start;cs:0000
m1:
mov al,[bx+si]
mov a.[di],al
inc di
inc si
loop m1
;code1 ends ;конец первого сегмента кодов
mov ax,4c00h
int 21h
code ends
end @start