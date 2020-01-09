.model svart
;.386

Node struc
namex db 4 dup (0ffh) 
field1 dw 2 dup (3231h)
Node ENDS

Data1 segment
a db 12h,13h
I_struc db ?
;pp1_8 pnt <>
;pp1_16 pnt <>
;pp1 ends


A0 Node <>
A1 Node 2 dup (<>)
A2 Node 4 dup (<>)
A3 Node 8 dup (<>)
Data1 ends

data2 segment 
b db 14h,15h
B0 Node <>
B1 Node 2 dup (<>)
B2 Node 4 dup (<>)
B3 Node 8 dup (<>)
data2 ends
code1 segment  
	assume ds:data1,cs:code1 
start:	mov	ax,data1 
	mov	ds,ax
	mov	ax,data2
	mov	es,ax  
	xor	ax,ax  
	mov	cx,length A1 
	mov	si,0 
jmp far ptr m2 
	mov bx, offset A1 
	CA0:
	mov A0.field1.[si],bx 
	add bx,8 
	add si,2 
	loop CA0
;jmp m3
	mov	cx,length A2 
	mov	si,0 
	mov bx, offset A2 
	CA1:
	mov A1.field1.[si],bx 
	add bx,8 
	cmp cx,3 
	je @1 
	jne @2 
	@1: add si,4 
	@2: add si,2 
	loop CA1


	mov	cx,4 
	mov	si,0 
	mov bx, offset A3 
	CA2:
	mov A2.field1.[si],bx 
	add bx,8 
	cmp cx,3 
	je @3 
	jne @4 
	@3: add si,4 
	@4: add si,2 
	loop CA2
	add si,4 
	mov cx,4 
	CA2_1:
	mov A2.field1.[si],bx 
	add bx,8 
	cmp cx,3 
	je @5 
	jne @6 
	@5: add si,4 
	@6: add si,2 
	loop CA2_1
	m3: 
jmp far ptr m2
;	mov ax, 4c00h
;	int 21h
code1 ends

code2 segment 

;m2 label far
;	assume ds:data1,es:data2,cs:code2 
m2 label far 
	mov ax,data1 
	mov ds,ax
	mov ax,data2 
	mov es,ax
;m2 label far
	cld 
	lea si,A0.field1 
	lea di,B0.field1
	mov cx,2;length A0

rep	movs b0+[di],a0+[si] ;field1,a0.fild1

	
	mov ax,4c00h
	int 21h
code2 ends 
end start
