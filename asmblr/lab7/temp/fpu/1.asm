MODEL	TINY
STACK 100h	
DATASEG
	Hellostr DB ?
CODESEG		
start:	
	mov ax,DATASEG
	mov ds,ax
	mov Hellostr,1
	mov dx,offset Hellostr               
	mov ah,09h
	int 21h
mov ah,1
int 21h
	mov ah,04Ch
	mov al,1h
	int 21h
end start