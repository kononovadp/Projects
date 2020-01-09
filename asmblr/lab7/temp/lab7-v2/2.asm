model small
.stack 100h 
.386
.data
min_x dq -3.6 ;мінімальне значення по осі х
max_x dq 3.6 ;максимальне значення по осі х
max_crt_x dw 320 ;максимальна кількість точок на екрані по осі х                                    
crt_x dw ? ;екранна координата по осі х
scale_x	dq ? ;масштаб по осі х
min_y dq -1.1
max_y dq 1.1
max_crt_y dw 200
crt_y dw ?
scale_y dq ?
.code
start:
scale macro p1
; обчислення масштабного коефіцієнта по осі p1 
; наприклад, для осі х
: (max_x - min_x) / max_crt_x
; top=0
fld 		max_&p1		; st0=max_&p1; top=7
fsub 		min_&p1		; st0=max_&p1 - min_&p1; ;top=7
fild 	max_crt_&p1	; st0=max_crt_&p1,
; st1=max_&p1-min_&p1; top=6
fdivp 		st (1), st (0)		; 1-й крок st1=st1/st0
; 2-й крок st1 стає st0; top=7
; і містить масштаб
fstp scale_&p1 ;top=0
endm
x_proc proc
; перетворення екранної координати в дійсну.
; top=0
fld 		scale_x		; st0 - масштаб
fild 		crt_x			; st0=crt_x, st1-масштаб
 ;top=6
fmulp 	st (1), st (0)		; top=7
fadd 		min_x		; st0 - реальне зн. Х; top=7
x_proc endp

y_proc proc
; контроль діапазону (top не змінюється)
fcom 		min_y;  порівняння ST (0) та min_y
fstsw 		ax; результат порівняння в ax
sahf 				; результат порівняння 
;ST (0) та min_y в регістр Flags
jc 		@minus		; st0 < min_y
; поза видимим діапазоном
; по @minus забезпечити top=0 і
; crt_y=max_crt_y

fcom 		max_y		; порівняння ST (0) та max_y
fstsw		ax
sahf
ja 		@plus		; st0 > max_y (zf=cf=0)
; поза видимим діапазоном
; по @plus - забезпечити top=0
; і встановити crt_y=0
fsub		min_y;
fdiv 		scale_y
frndint				; округлення до цілого
fistp		 crt_y			; TOP=0!!!
mov 		ax,max_crt_y
sub 		ax,crt_y
mov 		crt_y,ax		; дзеркальне відображення
y_proc endp
;scale x
;scale y
finit
call x_proc
mov ah,0
int 16h
;mov ah,0 
;mov al,saveMode 
;int 10h
mov ax,4c00h
int 21h
;call main

end start

 