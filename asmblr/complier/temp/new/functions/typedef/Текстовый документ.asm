 0000				code segment
 0000				code1 segment
				assume ds:data1,cs:code1
 0000  FA			m1:Cli
 0001  41			Inc cx
 0002  FE 0E 0001 R		Dec const1
 0006  72 0B			jb m2
 0008  13 DA			adc bx,dx
 000A  83 F9 08			Cmp cx,[8]
 000D  31 16 000C R		Xor [const6],dx
 0011  D1 E0			Sal ax,1
 0013  83 0E 0008 R 41		m2:Or const4,65
 0018  72 E6			Jb m1
 0000				code1 ends
 0000				code ends
				end