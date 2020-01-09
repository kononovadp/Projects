 0000  FA			m1: cli
 0001  FE C7			inc bh
 0003  41			inc cx
 0004  66| 46			inc esi
 0006  FE 0E 0000 R		dec const
 000A  FE 0E 0001 R		dec const1
 000E  FE 0E 0002 R		dec const2
 0012  FE 0E 0003 R		dec const3
 0016  FF 0E 0008 R		dec const4
 001A  FF 0E 000A R		dec const5
 001E  FF 0E 000C R		dec const6
 0022  66| FF 0E 000E R		dec const7
 0027  66| FF 0E 0012 R		dec const8
 002C  66| FF 0E 0016 R		dec const9
 0031  12 F9			adc bh,cl
 0033  13 DA			adc bx,dx
 0035  66| 13 CB		adc ecx,ebx
 0038  3A 3E 0000 R		cmp bh,const
 003C  3A 1E 0001 R		cmp bl,const1
 0040  3A 0E 0002 R		cmp cl,const2
 0044  3A 36 0003 R		cmp dh,const3
 0048  3B 16 0008 R		cmp dx,const4
 004C  3B 1E 000A R		cmp bx,const5
 0050  3B 0E 000C R		cmp cx,const6
 0054  66| 3B 36 000E R		cmp esi,const7
 0059  66| 3B 16 0012 R		cmp edx,const8
 005E  66| 3B 0E 0016 R		cmp ecx,const9
 0063  72 2B			jb m2
 0065  32 3E 0000 R		xor bh,const
 0069  32 1E 0001 R		xor bl,const1
 006D  32 0E 0002 R		xor cl,const2
 0071  32 36 0003 R		xor dh,const3
 0075  33 16 0008 R		xor dx,const4
 0079  33 1E 000A R		xor bx,const5
 007D  33 0E 000C R		xor cx,const6
 0081  66| 33 36 000E R		xor esi,const7
 0086  66| 33 16 0012 R		xor edx,const8
 008B  66| 33 0E 0016 R		xor ecx,const9
 0090  C0 E1 0A			m2: sal cl,1010b
 0093  C1 E1 E8			sal cx,232
 0096  66| C1 E3 79		sal ebx,79h
 009A  80 0E 0001 R FF		or const1,11111111b ;8-8
 009F  81 0E 000A R FF7F	or const5,65407 ;16-16
 00A5  66| 81 0E 0012 R		or const8,9fffh ;32-32
       00009FFF
 00AE  83 0E 000A R 7F		or const5,127 ;16-8
 00B3  66| 83 0E 0012 R		or const8,7fh ;32-8
       7F
 00B9  0F 82 FF43		jb m1