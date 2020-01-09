.model flat
.386p
.STACK 256
descr struc
limit_1 dw 0 ;������� 2 ����� ������ �������� (������� 0-15)
base_1 dw 0 ;������� 2 ����� ������� 32-�������� ������ �������� 
base_2 db 0 ;3-�� ���� ������� 32-�������� ������ ��������
attrib db 0 ;���� �������� ��������
bt6 db 0  ;������ 4 ������� ����� � �������� ��������,
;������� 4 ������� ����� - ������� 16-19 ������ ��������
base_3 db 0 ;4-��� ���� ������� 32-�������� ������ ��������
descr ends
;================�������� ����������================
descrtest struc
tlimit_1 dw 10 ;������� 2 ����� ������ �������� (������� 0-15)
tbase_1 dw 0 ;������� 2 ����� ������� 32-�������� ������ �������� 
tbase_2 db 0 ;3-�� ���� ������� 32-�������� ������ ��������
tattrib db 0 ;���� �������� ��������
tbt6 db 0  ;������ 4 ������� ����� � �������� ��������,
;������� 4 ������� ����� - ������� 16-19 ������ ��������
tbase_3 db 0 ;4-��� ���� ������� 32-�������� ������ ��������
descrtest ends
;================
test1 segment para public 'data' use16 ; ���������� ������� ���������� �����������
tselector0 descrtest	<>
tdescr_gdt descrtest	<>
tdescr_ds descrtest <>
tdescr_es descrtest <>; video
tdescr_ss descrtest <>
tdescr_cs descrtest <>
tgdt_size equ $-tselector0-1
tdeskr_Int_code descrtest <>
test1 ends
;================
;���� ��������� �����ֲ ���������в�
point_dt struc
lim dd 0
adr dd 0
point_dt ends
;������������� ���������� GDT � ��������  ��������  �������
GDT segment para public 'data' use16 ; ���������� ������� ���������� �����������
selector0 descr	<>
descr_gdt descr	<>
descr_ds descr <>
descr_es descr <>; video
descr_ss descr <>
descr_cs descr <>
gdt_size equ $-selector0-1
deskr_Int_code descr <>
GDT ends

;���������  �������� ��� GDT (� �������� ������� ����� _DATA):
ST_p segment use16
Db 1000 dup (0)
Top_stp	dw 1000;equ	$; Top_stp=1000
ST_p ends
IDT	segment para public 'data' use16
Vector=0
Rept 256
Dw Vector * Proc_int_size; ������� ���������
Dw offset deskr_Int_code; �������� ����������� � GDT
Db 0; ������ 0
Db 10001111b ;���� �������� - ���� ������
Dw 0; �� ��������� ����������� � ������ 64�
Vector=Vector+1
Endm
IDT	ends
.data
Top_real_mode dd ? ;����� ������������� � ��������� �����  �������  ���������� �����������
pidt point_dt <>
pgdt point_dt <> ;�������� ��� GDT (� �������� ������� �����
mes1 db 'Error!!!',13,10,'$'
mess_protect_mode db '0123456'
code_seg equ 10011010b; �� �������������� ������� ����, ��������� ������ 
data_seg equ 10010010b; ������� �����, ��������� ����������
tdata_seg equ 10010010b; �������� ������� �����, ��������� ������
stack_seg equ 10010110b; ������� �����
db 0eah ;�������� ��� ������� jmp
dw offset protect ;������� ���� �������� � ������� ����
dw offset descr_cs ;�������� �������� ���� 
dw offset tdescr_cs ;�������� ��������� �������� ����� 
tempvar dw 0
.code			
Start: 
mov	eax,cr0
test al,1
;jz MOD_error ; �������� ��� � ���������� �����
;��� ����, ��������� ������������ 20-� ������ ����� ����
in al,92h
or al,2
out	92h,al
mov	ax,GDT
mov ds,ax
assume ds:GDT 
;���������� ����������� �������� ����
mov	descr_cs.limit_1,gdt_size ; ����� �������� ����
;���������� ������� ������ �������� ����
xor	eax,eax
mov	ax,@code
shl	eax,4 ;������� ��������� ������ �� TASM
mov	dword ptr descr_cs.base_1,  eax
mov	descr_cs.attrib,code_seg
;���������� GDT ��������� ��� ������� �� GDT ���������� 
;���������� � ���������� ����� 
;--------------------------------------------------------
mov descr_gdt.limit_1,gdt_size
xor eax,eax
mov ax,GDT
shl eax,4
mov dword ptr descr_gdt.base_1,eax
mov descr_gdt.attrib,  data_seg
;��������� ���������� ����������� �������� �����.
mov descr_ds.limit_1,gdt_size
xor eax,eax
mov ax,GDT
shl eax,4
mov dword ptr descr_gdt.base_1,eax
mov descr_gdt.attrib,  data_seg
;������� �����
mov descr_ss.limit_1,10
xor eax,eax
mov ax,ST_p
shl eax,4
mov dword ptr descr_ss.base_1,eax
mov descr_ss.attrib,  stack_seg
;³��������
mov descr_es.limit_1,0ffffh;
mov dword ptr descr_es.base_1,0b8000h
mov descr_es.attrib,data_seg
;����������  GDT
xor eax,eax
mov ax,GDT
shl eax,4
mov pgdt.adr,eax
mov ax,gdt_size
mov pgdt.lim,eax
;������������ GDT
lgdt pgdt
;������������  �  ���������  �����  ���������� ���������� � 1 ��������� ��� ������� ��������� CR0:
Cli
Mov word ptr Top_real_mode,sp
Mov	word ptr Top_real_mode+2,ss
mov eax,cr0
or al,1
mov cr0,eax
protect:
;����������� ��������� ��� ����� �����������
;����������, �� RPL=0
mov ax,offset descr_ss
mov ss,ax
mov sp,Top_stp
mov ax,offset descr_ds
mov ds,ax
mov ax,offset descr_es
mov es,ax
;��������� ����������� �� �����
mov cx,20
mov si,offset mess_protect_mode
mov di,1640 ;��������� ������ ��������� 
mov ah,07h ;������� �������
outmes:
mov al,[si]
mov es:[di],ax
inc si
add di,2
loop outmes
;-----------------------------------------------------
;������������ ��������� �������� ����� � ������ es
mov	ax,test1
mov es,ax
assume es:test1 
;����������� �������� �������� �����.
mov tdescr_ds.tlimit_1,tgdt_size
xor eax,eax
mov ax,test1
shl eax,4
mov dword ptr tdescr_gdt.tbase_1,eax
mov tdescr_gdt.tattrib, tdata_seg
;1. �������� �������  �� ������ �� ��� �������� �����.
mov si,453[16]
cmp tdescr_ds.tlimit_1,tgdt_size
jg $
;8. �������� ������� �� ������������ � ���������� ������ 
;��������� ����������� �������� ������ ����.
;9. �������� ������� �� ������������ � ���������� ������  
;��������� ���������� ��� ������������ �����������.
mov tempvar,offset tdescr_cs
cmp tempvar,offset tdescr_ds
jne esprot ;$
mov ax,tempvar
mov es,ax
esprot:
;14. ��������� ����� 1 � �� A
mov cx,tempvar
cmp tdescr_gdt.tattrib,10010011b
je return_dos;$
;===========================
;���������� � �������� �����
return_dos:
assume ds:GDT; 
cli
mov ax, offset descr_GDT
; � ����� �������� ����� � ����� ������� ���������� ������� mov ax,GDT
mov ds,ax
mov descr_cs.limit_1,0ffffh
mov descr_ds.limit_1,0ffffh
mov descr_ss. attrib,   data_seg
; ���������������� ������� �������
mov ax,offset descr_ds
mov ds,ax
mov ax,offset descr_es
mov es,ax
mov ax,offset descr_ss
mov ss,ax
db 0eah
dw offset jumpt
dw offset descr_cs
jumpt:
;������������ � ����� �������� �����
mov eax,cr0
and al,0feh
mov cr0,eax
db 0eah
dw offset r_mode
;dw _CODE
r_mode:
assume ds:_DATA
mov ax,_data
mov ds,ax
lss sp,Top_real_mode
sti
mov ah,01h
int 21h ;������ �������� � ��������� 
mov ax,3
int 10h ; ����������� �������������
;��������� ������ �������� (����������)
mov ax,4c00h
int 21h
Int_code segment	para public 'code' use16
Assume cs:Int_code
Vector=0
I_beg:
Pusha
Mov ax,vector
Jmp common_int
I_end:
Proc_int_size = I_end-I_beg
; ��������� ������� 0-�� ����������� ������� ��������
; ��� ������������� ���������� �� ������ (Proc_int_size)
Vector=1
Rept 255
pusha
Mov	ax,vector
Jmp	common_int
Vector = Vector + 1
Endm
Mes_int	Db		'INTERUPT N'
common_int:
; ���������� ������ ����������� � Mes_int
mov	cl,10
div cl; ������� ����� � ah
or ah,30h ;���������� ���������� ���� �����
mov bh,ah
xor	ah,ah
div	cl; ������� ����� � ah, ������ - � al
or ax,3030h ;���������� ���������� ���� ����
mov dx,ax
; ��������� ����������� �� �����
push offset descr_es; �������� ����������� �� 1-�� �����
pop	es
mov si,offset Mes_int
mov cx,10
mov di,2620 ;��������� ������ ��� ��������� 
mov ah,07h ;������� �������
outstr:
mov al,CS:[si]
stosw
inc si
loop outstr
mov	al,' '
stosw
mov	al,dl ;������ ��������� ����� ������ ������� 
stosw
mov	al,dh ;������� ��������� ����� ������ �������
stosw
mov	al,bh ;������� ��������� ����� ������ �������
stosw
; ���� ��������� ����������� ��������� �������� ���������
; � �������� ������� ��� ������������ � ����� �������� �����
; ��� ����� ����������� ������� IRET
; � ���� ����� �������� � ���� �������� ���� ��� �������, ������ 
;�������, ��� ������� ����������, �� ���� ������� �����. 
; �� ��� �� ���������� � �������� � ���� ��� ���
pushf
push offset descr_cs; �������� ����������� �������� ���� �� 1-�� �����
push offset return_dos
iret; �������� ��������� �� ����� return_dos ��������� �������� ����
common_end:
Int_code_size =common_end-I_beg
jmp exit
MOD_error:
mov ah,9
mov dx,offset mes1
int 21h
;------------------
exit:
mov ah,1
int 21h
mov ah, 4ch		 
int 21h		
mov ax,_data
mov ds,ax
; ����������  IDT
xor eax,eax
mov ax,IDT
shl eax,4
mov pidt.adr,eax
mov pidt.lim,8*256
; ������������  IDT
lidt pidt
xor eax,eax
mov pidt.adr,eax
mov pidt.lim,3ffh
lidt pidt
Int_code ends
;--------------------------------------------------------

End Start