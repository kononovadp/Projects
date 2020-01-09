data segment
Data1 segment
const db 1101b
const8 dd 1010
Data1 ends
data ends
code segment
code1 segment
assume ds:data1,cs:code1
or const8,9fffh
or const8,9fffh
jb m1
m3: or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
m1: or const8,9fffh
cli
jb m3
jb m2
m4: or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
or const8,9fffh
m2: or const8,9fffh
jb m4
cli
code1 ends
code ends
end