.386p
Data Segment			
Top_real_mode dd ?

db        0eah                  ;машинний код команди jmp
dw        offset protect        ;зміщення мітки переходу в сегменті кодів
dw        offset deskr_cs         ;селектор сегмента кодів 
dw        offset deskr_ss         ;селектор сегмента кодів 
dw        offset deskr_es         ;селектор сегмента кодів 
Data Ends			
Code Segment	
Assume cs:Code, ds:Data		
Start: 
Cli
Mov word ptr Top_real_mode,sp
Mov	word ptr Top_real_mode+2,ss
mov eax,cr0
or al,1
mov cr0,eax
;------------


mov ah,1
int 21h
mov ah, 4ch		 
int 21h
End Start	
protect:
;завантажити селектори для інших дескрипторів
; припускаємо, що RPL=0
mov        ax,offset deskr_ss
mov        ss,ax
mov        sp,Top_stp
mov        ax,offset deskr_ds
mov        ds,ax
mov        ax,offset deskr_es
mov        es,ax	
Code Ends

;protect:
;завантажити селектори для інших дескрипторів
; припускаємо, що RPL=0


