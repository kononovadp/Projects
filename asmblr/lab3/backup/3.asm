;� ���� �������� ������������ ��������� ���������, ������� ������������ ������������� 
;����� ������ �������� ����� � ������. ��������� ������������ ���������, �� ����� ����������
;������ ������� � ��������� ��� ������ ������� db,ff ��������� ������ invalid opcode 
;� ���������� ������ �� ����.
Node struc
namex db 4 dup (0ffh) 
field1 dw 2 dup (3231h)
Node ENDS
data segment 
Data1 segment
I_struc db ?
A0 Node <>
A1 Node 2 dup (<>)
A2 Node 4 dup (<>)
A3 Node 8 dup (<>)
Data1 ends
data2 segment ;������ ������� ������ ����� ������ ��� ������� 2
B0 Node <>
B1 Node 2 dup (<>)
B2 Node 4 dup (<>)
B3 Node 8 dup (<>)
data2 ends
data ends
code segment
code1 segment  ;���������� ������� 1
	assume ds:data1,cs:code1 ;��������� ����� � ������������ ���������� ����� � ������
	;mov	ax,data1 ;�������� � ax �������� ������ � ���������� �������� Data1
	;mov	ds,ax ;��� ������ ������ ���� � ���������� �������� ds
	;xor	ax,ax ;��������� ax 
	mov	cx,length A1 ;�������� � ������� ������ ���������, �� ������� ����� ���������� ��������
	mov	si,0 ;�������� ��������� ������� 
	mov bx, offset A1 ;�������� ������ �������� ��������� ��������� � bx
	CA0:
	mov field1.A0[si],bx ;�������� � ������ ������� ��������� ����������� ���������
	add bx,8 ;����� �� ��������� �� ��������� �������
	add si,2 ;����� �������
	loop CA0
;--------------------------------------------------------------------------	
;�������� �������� ��������� ��������� A2 � ���� field1 ������� �������� A1	
	mov	cx,length A2 ;�������� � ������� ������ ���������, �� ������� ����� ���������� ��������
	mov	si,0 ;�������� ��������� ������� 
	mov bx, offset A2 ;�������� �������� ��������� ��������� � bx
	CA1:
	mov field1.A1[si],bx ;�������� � ������ ������� ��������� ����������� ���������
	add bx,8 ;������ �� ��������� �� ��������� �������
	cmp cx,3 ;����� ������� �� ������� ��������, ����� ���������� �� 4 �������� ������, ����� ������� � ���� field1
	je @1 ;���� cx = 3, �� ����������� ����� �� 4 ��������, ����� ������� � ���� field1
	jne @2 ; � ��������� ������� ������ ���������� �� 2
	@1: add si,4 ;����� ������� �� 4
	@2: add si,2 ;����� ������� �� 2
	loop CA1
;--------------------------------------------------------------------------	
;�������� �������� ��������� ��������� A3 � ���� field1 ������� �������� A2
;(���������� �� ������ �������, �������� ���� ����� ��������� ������� � ������� ����������� ������!)
	mov	cx,4 ;� ����� ����� ������������ �������� ��������� ���������
	mov	si,0 ;�������� ��������� ������� 
	mov bx, offset A3 ;�������� �������� ��������� ��������� � bx
	CA2:
	mov field1.A2[si],bx ;�������� � ������ ������� ��������� ����������� ���������
	add bx,8 ;��������� �� ��������� �� ��������� �������
	cmp cx,3 ;����� ������� �� ������� ��������, ����� ���������� �� 4 �������� ������, ����� ������� � ���� field1
	je @3 ;���� cx = 3, �� ����������� ����� �� 4 ��������, ����� ������� � ���� field1
	jne @4 ; � ��������� ������� ������ ���������� �� 2
	@3: add si,4 ;����� ������� �� 4
	@4: add si,2 ;����� ������� �� 2
	loop CA2
	add si,4 ;������� �� 4 ��������, ����� ������� � ���� field1
	mov cx,4 ;�� ������ ����� �������������� 4 ��������� ��������
	CA2_1:
	mov field1.A2[si],bx ;�������� � ������ ������� ��������� ����������� ���������
	add bx,8 ;��������� �� ��������� �� ��������� �������
	cmp cx,3 ;����� ������� �� ������� ��������, ����� ���������� �� 4 �������� ������, ����� ������� � ���� field1
	je @5 ;���� cx = 3, �� ����������� ����� �� 4 ��������, ����� ������� � ���� field1
	jne @6 ; � ��������� ������� ������ ���������� �� 2
	@5: add si,4 ;����� ������� �� 4
	@6: add si,2 ;����� ������� �� 2
	loop CA2_1
	exit: ;���������� ���������, ��� ��� ������ ��������� ��������� ����� � ������ �� �������������� ��������� ���� ���������� ���������
	mov ax, 4c00h
	int 21h
code1 ends ;����� ������� �������� �����
;===========================������ ����� ������;===========================
code2 segment ;���������� ������� 2
	assume ds:data1,es:data2,cs:code2 ;������� ��������� - ds, ������� ��������� - es
	mov ax,data1 ;������������� ������� �������� ������, ������� ����� ����������� �� ������ �������
	mov ds,ax
	mov ax,data2 ;������������� ������� �������� ������, � ������� ����� ���������� ������ �������
	mov es,ax
	cld ;����� ����� df
	lea si,A0 ;��������� ������ �������� ��������� A0, ������� ���������� ����������
	lea di,B0 ;��������� ������ �������� ��������� B0, � ������� ����� ����������� ��������� �0
	mov	cx,length A0 ;�������� � ������� ���������� ����� ���������, ������� ����� ��������� �� ������ ���������
	rep movs B0, A0 ;����������� ��������� ��������� �0 � ��������� B0
	lea dx,B0 ;� dx ���������� �������� ��������� B0
	;���������� ������ ���������
	mov ax,4c00h
	int 21h
code2 ends ;����� ������� �������� �����
code ends
end