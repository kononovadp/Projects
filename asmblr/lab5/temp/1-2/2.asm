.model compact
.386
.data
.stack
db 255
data1 segment
mes1 db 'First string: Hello, World',13,10,'$'
mes2 db 'Second string: Hello, Assembler',13,10,'$'
data1 ends
.code
code1:
mov ax,data1
mov ds,ax
mov ax,12
int 10h
;--------����� �� ����� ������� NUL ������� �������--------
mov dh,0 ;����� ������
mov dl,-1 ;����� �������
mov bh,0 ;����� ��������
mov al,0h ;��������� ������
mov cx,1 ;���������� ��������� ��������
mov bl,19 ;�������� (���� � ���)
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
add bl,150 ;�������� ������� �������
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
;--------������ � �����--------
xor ax,ax
int 33h
mov ax,1
int 33h
mov ax,0Ch
mov cx,1001b
push es
push cs
pop es
lea dx,prm
int 33h
pop es
;--------�������� �����--------
mov ah,1
int 21h
;--------�������� ����--------
prm proc far
push ds
push es
pusha
mov ax, 0B800h
mov es,ax
pop es
mov ax, data1
mov ds,ax
pop ds
;�������� ����
mov ah,2 ;������� 2-� �������
mov dl,cx;inc dl ;����������� ������
mov dh,dx
int 10h ;������� ������
popa
pop es
pop ds
retf
prm endp
end code1