;masm
.model small
.386p
.STACK 256

;.model flat

; ОПИС ДЕСКРИПТОРА СЕГМЕНТА
descr struc
limit_1 dw 0 ; молодші 2 байта розміру сегменту (розряди 0-15)
base_1 dw 0 ; молодші 2 байта фізичної 32-розрядної адреси сегменту 
base_2 db 0 ; 3-тій ба	йт фізичної 32-розрядної адреси сегменту
attrib db 0 ; байт атрибутів сегменту
bt6 db 0 ; старші 4 розряди байту – атрибути сегменту,
; молодші 4 розряди байту - розряди 16-19 розміру сегменту
base_3 db 0 ; 4-тий байт фізичної 32-розрядної адреси сегменту
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
	db        0eah                  ;машинний код команди jmp
;dw        offset protect        ;зміщення мітки переходу в сегменті кодів
;dw        offset deskr_cs         ;селектор сегмента кодів 
;dw        offset deskr_ss         ;селектор сегмента кодів 
;dw        offset deskr_es         ;селектор сегмента кодів 
; БАЙТИ АТРИБУТІВ
code_seg	equ	10011010b; не підпорядкований сегмент кодів, дозволено читати 
data_seg	equ	10010010b; сегмент даних, дозволено записувати
stack_seg	equ	10010110b; сегмент стека

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

;  загальна частина для всіх дескрипторів 
;_code1 segment
;assume ds:GDT
;mov		ax,GDT
;mov 		ds,ax
;assume 	ds:GDT 

;Формування дескриптора сегмента кодів
;mov  deskr_cs.limit_1,code_size ; розмір сегмента кодів

; формування фізичної адреси сегмента кодів
;xor		 eax,eax
;mov		ax,_CODE1
;shl		 eax,4 	; відлуння реального режиму від TASM
			; TASM транслює _CODE для реального режиму
;mov		dword ptr deskr_cs.base_1,  eax
; атрибути сегмента кодів
;mov		deskr_cs.attrib,code_seg



.Code	
;Assume cs:Code, ds:Data	
Start: 

mov ax,@Data
mov ds,ax
xor ax,ax

;  загальна частина для всіх дескрипторів 
;_code1 segment
assume ds:GDT
mov		ax,GDT
mov 		ds,ax
;assume 	ds:GDT 

;Формування дескриптора сегмента кодів
mov  deskr_cs.limit_1,code_size ; розмір сегмента кодів

; формування фізичної адреси сегмента кодів
xor		 eax,eax
mov		ax,@CODE
shl		 eax,4 	; відлуння реального режиму від TASM
			; TASM транслює _CODE для реального режиму
mov		dword ptr deskr_cs.base_1,  eax
; атрибути сегмента кодів
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



