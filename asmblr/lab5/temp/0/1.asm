Title WORD	
 
  Dat Segment			
  Greet DB 'Hello Word', 13,10,'$' 
        DB 41, 42, 43, 44, 45	
  A     DW 10 Dup(?)
  b     db 0  
  x     dw ?  
  y     dw ?
  z     dw ?
  masc db 9		
  Dat   Ends			
  	
  Code Segment			
  Assume cs:Code, ds:Dat
  
handler proc far
push ds
push cs
pop ds
;запись в es адреса начала видеопамяти
mov ax,0b800h
mov es,ax

mov ax,seg greet
mov ds,ax


mov ah,09h
	mov al,'k'
	mov bl,masc
	mov bh,0
	mov cx,25
m1:	int 10h     


inc masc

loop m1

	;mov	ah,02h	; вывести точку
	;mov	dx,32h
	;int	10h
	;mov	ax,1	; показать курсор
	;;int	33h
;
pop ds

ret

handler endp




 Start: mov ax, Dat	        
  	 mov ds, ax 	       
  	
	    mov ah,00
  	    mov al,03h
  	    int 10h

	mov ah,01h
	mov cx,0007h
	;int 10h
  	    
  	    mov ah,02h
  	    mov bh,00h
  	    mov dh,00h
  	    mov dl,00h
  	    int 10h 
	
	mov ah,09h
	mov al,'k'
	mov bl,4fh
	mov bh,0
	mov cx,25
	int 10h      
	mov ah,02h
	mov bh,0
	mov dx,0200h
	int 10h

	mov ah,09h
	mov dx, offset Greet
	int 21h
	
;	mov ah,0
;	mov al, 12h
;	int 10h


	mov ax,0000h
	int 33h

	mov ax,0001h
	int 33h

	mov ax,0002h
	int 33h
    
  	    
  	     	    
  	    mov ax,0003h
 	    int 33h         
	    mov   z,bx
  	    mov x,dx
  	    mov y,cx        
  	    
	mov	ax,000ch	
	mov	cx,0004h
	mov	dx,offset handler
	push cs
	pop es
	int	33h

	mov ah,1
	int 21h

	mov ax,000ch
	mov cx,0
	int 33h
	

  	 	 	
	 mov ah, 4ch		 
  	 int 21h		
  Code 	 Ends
  End 	 Start
  
  
