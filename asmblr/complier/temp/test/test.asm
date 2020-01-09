Data1 Segment
Vb db 10011b
String db Д–€док Ц new?
Vw dw 4567d
Vd dd 0d7856fdah
Data1 ends
Data2 Segment
Doublesg dw 678
QWERTY dd 67ff89h
Zxcv db 89h
Data2 Ends
Assume cs:Code,Ds:Data1,Gs:Data2
Code Segment
label1:
Cli
Inc cl
Jb Label2
Inc Bx
Dec Vw[si]
Dec gs:zxCV[bp]
Add Eax, Esi
Cmp Ax, Doublesg[edi]
Cmp ebx, qwerty[ebx]
Xor vb[edx], al
Mov dx, 5634h
Or Vd[esp], 0101b
Jb label1
Label2:
Code ends