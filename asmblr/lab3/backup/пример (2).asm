;prg12_6.asm
masm
model	small
stack	256
.586P
pnt struc	;��������� pnt, ���������� ��������� �����������
	union		;�������� ���������� � ��������� �����������
offs_16	dw	?
offs_32	dd	?
	ends		;����� �������� �����������
segm	dw	?
	ends		;����� �������� ���������
.data
point	union	;����������� �����������,
;����������� ��������� ���������
off_16	dw	?
off_32	dd	?
point_16	pnt	<>
point_32	pnt	<>
point	ends
tst	db	"������ ��� ������������"
adr_data	point	<>	;����������� ���������� �����������
.code	
main:	
	mov	ax,@data
	mov	ds,ax
	mov	ax,seg tst
;�������� ����� �������� ������ tst � ���� ��������� adr_data
	mov	adr_data.point_16.segm,ax
;����� ����������� ����� ������� �������� �� ����� ���� �������, � �������, � ������� bx:
	mov	bx,adr_data.point_16.segm 
;��������� �������� � ���� ��������� adr_data
	mov	ax,offset tst	;�������� ������ � ax
	mov	adr_data.point_16.offs_16,ax
;����������, ����� �����������, ����� ������� �������� �� ����� ����:
	mov	bx,adr_data.point_16.offs_16
	exit:
	mov	ax,4c00h
	int	21h
end	main
=====================================================================================================
;prg_12_1.asm 
MASM 
MODEL small 
STACK 256 
.data 
mes	db	0ah,0dh,'������- ','$' 
mas	db	10 dup (?) ;�������� ������ 
i	db	0 
.code 
main: 
mov	ax,@data 
mov	ds,ax 
xor	ax,ax	;��������� ax 
mov	cx,10	;�������� �������� ����� � cx 
mov	si,0	;������ ���������� �������� � cx 
go:	 ;���� ������������� 
mov	bh,i	;i � bh 
mov	mas[si],bh	;������ � ������ i 
inc	i	 ;��������� i 
inc	si	 ;����������� � ���������� 
;�������� ������� 
loop	go	;��������� ���� 
;����� �� ����� ������������� ������� 
mov	cx,10 
mov	si,0 
mov	ah,09h 
lea	dx,mes 
int	21h 
show: 
mov	ah,02h	;������� ������ �������� 
;�� al �� ����� 
mov	dl,mas[si] 
add	dl,30h	;�������������� ����� � ������ 
int	21h 
inc	si 
loop	show 
exit: 
mov	ax,4c00h	;����������� ����� 
int	21h 
end	main	 ;����� ���������