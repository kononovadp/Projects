;masm
.model small
.386p
.STACK 256

;.model flat

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
deksr_gdt descr <>
deskr_ds descr <>
deskr_es descr <>                                                             
deskr_ss descr <>  
deskr_cs descr <> 
code_size equ $-selector0-1
GDT ends

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

a1 db 'Hello',10,13,24h


;GDT segment para public 'data' use16
;selector0 descr <>
;deksr_gdt descr <>
;deskr_ds descr <>
;deskr_es descr <>                                                             
;deskr_ss descr <>  
;deskr_cs descr <> 
;code_size equ $-selector0-1
;GDT ends

;  �������� ������� ��� ��� ����������� 
;_code1 segment
;assume ds:GDT
;mov		ax,GDT
;mov 		ds,ax
;assume 	ds:GDT 

;���������� ����������� �������� ����
;mov  deskr_cs.limit_1,code_size ; ����� �������� ����

; ���������� ������� ������ �������� ����
;xor		 eax,eax
;mov		ax,_CODE1
;shl		 eax,4 	; ������� ��������� ������ �� TASM
			; TASM �������� _CODE ��� ��������� ������
;mov		dword ptr deskr_cs.base_1,  eax
; �������� �������� ����
;mov		deskr_cs.attrib,code_seg



.Code	
;Assume cs:Code, ds:Data	
Start: 

mov ax,@Data
mov ds,ax
xor ax,ax

;  �������� ������� ��� ��� ����������� 
;_code1 segment
assume ds:GDT
mov		ax,GDT
mov 		ds,ax
;assume 	ds:GDT 

;���������� ����������� �������� ����
mov  deskr_cs.limit_1,code_size ; ����� �������� ����

; ���������� ������� ������ �������� ����
xor		 eax,eax
mov		ax,@CODE
shl		 eax,4 	; ������� ��������� ������ �� TASM
			; TASM �������� _CODE ��� ��������� ������
mov		dword ptr deskr_cs.base_1,  eax
; �������� �������� ����
mov		deskr_cs.attrib,code_seg


mov eax,cr0
test al,0e1h
mov cr0,eax

jnz m1

;jnz m2


m1: mov ah,09h
mov dx, offset a1
;db 36
int 21h
;db 36
m2:
mov ah,4ch
int 21h

;Code Ends

end start



