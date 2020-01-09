; програмний модуль BigShow.asm
.386
_text segment word public 'text' use16
 assume cs:_text
;
;*****************************************
; п/п виведення на екран в hex-форматi даних iз регiстра ebx:
; якщо di=28 – виводяться усі 4 байти
; якщо di=20 – виводяться 3 молодших байти
; якщо di=12 – виводяться 2 молодших байти
; якщо di=4 – виводиться один молодший байт
show_bt proc
 pushad
 mov cx,di
 mov ah,2
bt0:
 mov edx,ebx
 shr edx,cl
 and dl,00001111b
 cmp dl,10
 jl bt1
 add dl,7
bt1:
 add dl,30h
 int 21h
 sub cl,4
 jnc bt0
 popad
 ret
show_bt endp
BigShow proc far ; procedure BigShow(var mas, len:word)
 public BigShow
; mas - адреса байтового масиву
@mas equ [bp+8] ; адреса адреси
; len - кiлькiсть байт масива, якi необхiдно вивести на екран
@len equ [bp+6] ; адреса кiлькостi
 push bp
 mov  bp,sp ; базова адреса фактичних параметрiв
; перехiд на новий рядок екрану
 mov ah,2
 mov dl,13
 int 21h
 mov dl,10
 int 21h
; обчислення кiлькостi пробілів у першому рядку
 mov ax,@len
 test ax,00000011b
 pushf
 shr ax,2
 popf
 jz @1
 inc ax
@1:
 xor cx,cx
 mov di,28
 and ax,00000111b
 jz  @2
; формування пробілiв на вiдсутнiх подвiйних словах
 mov ah,8
 sub ah,al
 mov al,ah
 xor ah,ah
 imul ax,8+1
 mov cx,ax
 @2:
 mov dx,@len
 and dx,00000011b
 jz l000
; формування початкового значення кiлькостi зсувiв
 mov di,dx ;di - 1 2 3
 dec di ;di - 0 1 2
 shl di,3 ;di - 0 8 16
 add di,4 ;di - 4 12 20
; формування пробілів на вiдсутнiх байтах у подвiйному словi
 mov dh,4
 xchg dh,dl ;dh - 1 2 3
 sub dl,dh ;dl - 3 2 1
 shl dl,1 ;dl - 6 4 2
 xor dh,dh ;dx - 6 4 2
  add cx,dx
l000:
 jcxz l002
; виведення початкових пробілiв у першому рядку
l001:
 mov ah,2
 mov dl," "
 int 21h
 loop l001
l002:
 mov cx,@len
 shr cx,2
 cmp di,28
 jz @3
 inc cx
@3:
 xor esi,esi
 lds si,@mas
 lea esi,[esi+ecx*4]-4
 std
; виведення масиву
l004:
 lodsd
 mov ebx , eax
 call show_bt
 mov di,28
 mov ah , 2
 mov dl,20h
 int 21h
 dec ecx
 test ecx,7
 jne l005
; перехiд на новий рядок
 mov ah,2
  mov dl,13
 int 21h
 mov dl,10
 int 21h
l005:
 jcxz L006
 jmp l004
l006:
 mov ah,2
 mov dl,13
 int 21h
 mov  dl,10
 int 21h
; mov ah,1
; int 21h
 pop bp
 ret 6
BigShow endp
_text ends
 end