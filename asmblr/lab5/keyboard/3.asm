.model compact
.data
.stack
db 255
data1 segment
mes1 db 'First string: Hello, World',13,10,'$'
mes2 db 'Second string: Hello, Assembler',13,10,'$'
col dw 0h
sym db 0h
sym2 db 0h
data1 ends
.code
code1:
mov ax,data1
mov ds,ax
;--------����� �� ����� ������� NUL ������� �������--------
mov dh,0 ;����� ������
mov dl,-1 ;����� �������
mov bh,0 ;����� ��������
mov al,55h;0h ;��������� ������
mov cx,1 ;���������� ��������� ��������
mov bl,0b;19 ;�������� (���� � ���)
mov si,0 ;�������
mov ah,0
mov al,3
int 10h
mov al,0h
m2:
mov ah,2 ;����������� �����
inc dl ;��������� ������
int 10h ;����� �� �����
mov ah,9 ;���������� ������ �����
add bl,10000b;150 ;�������� ������� �������
int 10h ;������� ������ �� �����
inc si ;��������� �������
cmp si,16 ;�������� ������� � 16
jne m2 ;���� �� ������ 16, �� ��������� ���� �����
;--------����� ������ �� �����--------
;������ ������
mov dh,1 ;����� ������
mov dl,0 ;����� �������
mov ah,2
int 10h ;��������� ������ �� ��������� ������
mov ah,9
mov dx,offset mes1
int 21h
;������ ������
mov dh,2 ;����� ������
mov dl,0 ;����� �������
mov ah,2
int 10h ;��������� ������ �� ��������� ������
mov ah,9
mov dx,offset mes2
int 21h
mov ah,2
mov dh,0
mov dl,0
int 10h
mov ah,1
int 21h
;--------������ � �����������--------
keyboard:
mov ah,0
int 16h
mov sym,ah
cmp sym,4Dh
je right
cmp sym,4Bh
je left
cmp sym,48h
je up
cmp sym,50h
je down
cmp sym,39h
je backspace
cmp sym,1Ch
je ent
cmp sym,01h
je exit
right:
mov ah,2
inc dl
int 10h
cmp sym,4Dh
je keyboard
left:
mov ah,2
dec dl
int 10h
cmp sym,4Bh
je keyboard
up:
mov ah,2
dec dh
int 10h
cmp sym,48h
je keyboard
down:
mov ah,2
inc dh
int 10h
cmp sym,50h
je keyboard
backspace:
mov ah,8
mov bh,0
int 10h
mov col,ah
cmp sym,39h
je keyboard
ent:
mov ah,8
mov bh,0
int 10h
mov sym2,al
mov ah,9
mov al,sym2
mov bl,col
mov cl,4
shr bl,cl
mov bh,0
mov cx,1
int 10h
jmp keyboard
exit:
int 20h
end code1