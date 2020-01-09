.286
; 7 6 5 4 3 2 1 0 - DL
; 1 0 1 0 1 0 1 0 - DL
; 6 1 2 5 6 0 5 7 - DH
code SEGMENT
mov DL,10101010b
mov DH,00000000b

mov CL,DL; 7>0
and CL,80h
shr CL,7
or DH,CL

mov CL,DL; 5>1 
and CL,60h
shr CL,4
or DH,CL

mov CL,DL; 0>2 
and CL,10h
shl CL,2
or DH,CL

mov CL,DL; 6>3
and CL,70h
shr CL,3
or DH,CL

mov CL,DL; 5>4 
and CL,60h
shr CL,1
or DH,CL

mov CL,DL; 2>5 
and CL,30h
shl CL,3
or DH,CL

mov CL,DL; 1>6 
and CL,20h
shl CL,5
or DH,CL

mov CL,DL; 6>7 
and CL,70h
shl CL,1
or DH,CL

code ENDS
end