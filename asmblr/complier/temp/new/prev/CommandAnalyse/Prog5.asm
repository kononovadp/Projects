;prg12_6.asm
;masm
.model	small
.stack	256
.386p

.data
a db 31h
c	db	10 dup (?)
tst	db	'Hello'
b	db	32h

.code	
;	assume cs:code; ds:data
main:	
	mov	ax,@data
	mov	ds,ax
	mov	ax,seg tst
	mov	bx, offset c
	mov	si, 0
	mov 	di, 0
	mov     cx, 10
m1:	mov 	al, cs:[si]
	mov	[bx+di],al
	inc 	si
	inc	di
	loop 	m1



mov	ax,4c00h
	int	21h
end	main

;