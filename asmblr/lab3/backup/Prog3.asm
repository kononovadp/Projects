;prg12_6.asm
;masm
.model	small
.stack	256
.386p
pnt struc	
;point	union	
offs_8	db	34h
offs_16	dw	5678h
segm	dw	5759h
pnt	ends		

.data
a db 31h
adr0	pnt	<>
adr1	pnt	2 dup (<>)
tst	db	'Hello'
b	db	32h
b0	pnt     <>

.code	
;	assume cs:code; ds:data
main:	
	mov	ax,@data
	mov	ds,ax
	mov	ax,seg tst
	mov	adr0.segm,ax
	mov	bx,adr0.segm 
	mov	bx, offset tst
;	mov	adr0.offs_8, [bx]  	
 	mov	al,[bx]
	mov	adr0.offs_8,al
	mov	cx,4
	mov     si,1
	mov	di,0
m1:	mov     al,[bx+si]
	mov	adr0.[byte ptr offs_16.di],al
	inc si
	inc di
	loop m1
  
	mov	ax,4c00h
	int	21h
end	main

;