.model small
.386p
.stack 256
;.model tiny
.Data ;Segment			
mes1 db 'Error!!!';,13,10,'$'
;Dat ;Ends			
.Code ;Segment			
;Assume cs:Code, ds:Data
Start: 
;Assume cs:Code, ds:Dat
mov ax,@Data	        
mov ds, ax
mov	eax,cr0
test	al,1
jnz	MOD_error ; процесор уже в захищеному режимі
;Крім того, необхідно розблокувати 20-й розряд адрес ПЕОМ
in al,92h
or al,2
out	92h,al

mov eax,cr0
and al,0feh
mov cr0,eax

mov ax,@data
mov ds,ax

MOD_error:
mov ah,9
mov dx,offset mes1
int 21h
;------------------
mov ah,1
int 21h
mov ah, 4ch		 
int 21h		
;Code Ends
End Start