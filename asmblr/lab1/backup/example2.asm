.286
;7 6 5 4 3 2 1 0
;3 2 1 0 7 6 5 4
code SEGMENT
mov DL,10101010b
mov DH,00000000b

mov CL,DL ; 3 > 7
and CL,8
shl CL,4  
or DH,CL
nop
mov CL,DL ; 2 > 6
and CL,4
shl CL,4
or  DH,CL
nop
mov CL,DL ; 1 > 5
and CL,2
shl CL,4
or  DH,CL 
nop
mov CL,DL ; 0 > 4
and CL,1
shl CL,4 
or DH,CL
nop
mov CL,DL ; 7 > 3
and CL,80h
shr CL,4
or DH,CL
nop
mov CL,DL ; 6 > 2
and CL,40h 
shr CL,4
or DH,CL
nop
mov CL,DL ; 5 > 1
and CL,20h
shr CL,4
or DH,CL
nop
mov CL,DL ; 4 > 0
and CL,10h
shr CL,4
or DH,CL

code ENDS
end