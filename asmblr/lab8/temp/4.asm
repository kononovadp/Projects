.model flat
.386p
.STACK 256


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
	db        0eah                  ;машинний код команди jmp
;dw        offset protect        ;зміщення мітки переходу в сегменті кодів
;dw        offset deskr_cs         ;селектор сегмента кодів 
;dw        offset deskr_ss         ;селектор сегмента кодів 
;dw        offset deskr_es         ;селектор сегмента кодів 
; БАЙТИ АТРИБУТІВ
code_seg	equ	10011010b; не підпорядкований сегмент кодів, дозволено читати 
data_seg	equ	10010010b; сегмент даних, дозволено записувати
stack_seg	equ	10010110b; сегмент стека

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

;  загальна частина для всіх дескрипторів 
assume ds:GDT
mov		ax,GDT
mov 		ds,ax
;assume 	ds:GDT 


;Формування дескриптора gdt
mov  deskr_gdt.limit_1, gdt_size ; розмір gdt
xor		 eax,eax
mov		ax,GDT
shl		 eax,4 	
mov		dword ptr deskr_gdt.base_1,  eax
mov		deskr_gdt.attrib,data_seg


;Формування дескриптора сегмента даних
mov  deskr_ds.limit_1,gdt_size ; розмір ds
xor		 eax,eax
mov		ax,GDT
shl		 eax,4 	
mov		dword ptr deskr_ds.base_1,  eax
mov		deskr_ds.attrib,data_seg


;Формування дескриптора сегмента ES
mov  deskr_es.limit_1,0ffffh ; розмір es
mov		dword ptr deskr_es.base_1,  0b8000h
mov		deskr_es.attrib,data_seg

;Формування дескриптора сегмента SS
mov  deskr_ss.limit_1, 10 ; розмір ss
xor		 eax,eax
mov		ax,ST_p	
shl		 eax,4 	
mov		dword ptr deskr_ss.base_1,  eax
mov		deskr_ss.attrib,stack_seg




;Формування дескриптора сегмента кодів
mov  deskr_cs.limit_1,gdt_size ; розмір сегмента кодів

; формування фізичної адреси сегмента кодів
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



