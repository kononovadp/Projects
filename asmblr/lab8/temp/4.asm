.model flat
.386p
.STACK 256


; ���� ����������� ��������
descr struc
limit_1 dw 0 ; ������� 2 ����� ������ �������� (������� 0-15)
base_1 dw 0 ; ������� 2 ����� ������� 32-�������� ������ �������� 
base_2 db 0 ; 3-�� ��	�� ������� 32-�������� ������ ��������
attrib db 0 ; ���� �������� ��������
bt6 db 0 ; ������ 4 ������� ����� � �������� ��������,
; ������� 4 ������� ����� - ������� 16-19 ������ ��������
base_3 db 0 ; 4-��� ���� ������� 32-�������� ������ ��������
descr           ends


GDT segment para public 'data' use16
selector0 descr <>
deskr_gdt descr <>
deskr_ds descr <>
deskr_es descr <>                                                             
deskr_ss descr <>  
deskr_cs descr <> 
gdt_size equ $-selector0-1
GDT ends

ST_p segment use16
db 1000 dup (0)
top_stp equ $
ST_p	ends

.data  		
MOD_error dw ?
	db        0eah                  ;�������� ��� ������� jmp
;dw        offset protect        ;������� ���� �������� � ������� ����
;dw        offset deskr_cs         ;�������� �������� ���� 
;dw        offset deskr_ss         ;�������� �������� ���� 
;dw        offset deskr_es         ;�������� �������� ���� 
; ����� ������Ҳ�
code_seg	equ	10011010b; �� �������������� ������� ����, ��������� ������ 
data_seg	equ	10010010b; ������� �����, ��������� ����������
stack_seg	equ	10010110b; ������� �����

a1 db 'Start',10,13,24h
a2 db 'world',10,13,36


.Code	
;Assume cs:Code, ds:Data	
Start: 

mov ax,@Data
mov ds,ax
xor ax,ax

mov ah,09h
mov dx, offset a1
int 21h

in al,92h
or al,2
out 92h,al

;  �������� ������� ��� ��� ����������� 
assume ds:GDT
mov		ax,GDT
mov 		ds,ax
;assume 	ds:GDT 


;���������� ����������� gdt
mov  deskr_gdt.limit_1, gdt_size ; ����� gdt
xor		 eax,eax
mov		ax,GDT
shl		 eax,4 	
mov		dword ptr deskr_gdt.base_1,  eax
mov		deskr_gdt.attrib,data_seg


;���������� ����������� �������� �����
mov  deskr_ds.limit_1,gdt_size ; ����� ds
xor		 eax,eax
mov		ax,GDT
shl		 eax,4 	
mov		dword ptr deskr_ds.base_1,  eax
mov		deskr_ds.attrib,data_seg


;���������� ����������� �������� ES
mov  deskr_es.limit_1,0ffffh ; ����� es
mov		dword ptr deskr_es.base_1,  0b8000h
mov		deskr_es.attrib,data_seg

;���������� ����������� �������� SS
mov  deskr_ss.limit_1, 10 ; ����� ss
xor		 eax,eax
mov		ax,ST_p	
shl		 eax,4 	
mov		dword ptr deskr_ss.base_1,  eax
mov		deskr_ss.attrib,stack_seg




;���������� ����������� �������� ����
mov  deskr_cs.limit_1,gdt_size ; ����� �������� ����

; ���������� ������� ������ �������� ����
xor		 eax,eax
mov		ax,@CODE
shl		 eax,4 	
mov		dword ptr deskr_cs.base_1,  eax
mov		deskr_cs.attrib,code_seg


mov eax,cr0
and al,0feh
mov cr0,eax

;jnz m1

;jnz m2
;assume ds:@Data
mov ax,@data
mov ds,ax

m1:
mov ah,09h
mov dx, offset a2
int 21h

m2:
mov ah,4ch
int 21h

;Code Ends

end start



