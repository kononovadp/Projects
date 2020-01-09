.286
; #10
;7 6 5 4 3 2 1 0 - result
;1 0 3 2 5 4 7 6 - input

code SEGMENT
mov DL,0ffh ; input data
mov DH,00000000b

mov CL,DL ;1>7
and CL,8
shl CL,2
or DH,CL

mov CL,DL ;0>6
and CL,4
shl CL,2
or  DH,CL

mov CL,DL ;3>5
and CL,2
shl CL,6
or  DH,CL

mov CL,DL ;2>4
and CL,1
shl CL,6
or DH,CL

mov CL,DL ;5>3
and CL,128
shr CL,6
or DH,CL

mov CL,DL ;4>2
and CL,64
shr CL,6
or DH,CL

mov CL,DL ;7>1
and CL,32
shr CL,2
or DH,CL

mov CL,DL ;0>6
and CL,16
shr CL,2
or DH,CL

code ENDS
end