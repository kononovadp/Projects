.model flat
.386p
.STACK 256
descr struc
limit_1 dw 0 ;молодші 2 байта розміру сегменту (розряди 0-15)
base_1 dw 0 ;молодші 2 байта фізичної 32-розрядної адреси сегменту 
base_2 db 0 ;3-тій байт фізичної 32-розрядної адреси сегменту
attrib db 0 ;байт атрибутів сегменту
bt6 db 0  ;старші 4 розряди байту – атрибути сегменту,
;молодші 4 розряди байту - розряди 16-19 розміру сегменту
base_3 db 0 ;4-тий байт фізичної 32-розрядної адреси сегменту
descr ends
;================тестовий дескриптор================
descrtest struc
tlimit_1 dw 10 ;молодші 2 байта розміру сегменту (розряди 0-15)
tbase_1 dw 0 ;молодші 2 байта фізичної 32-розрядної адреси сегменту 
tbase_2 db 0 ;3-тій байт фізичної 32-розрядної адреси сегменту
tattrib db 0 ;байт атрибутів сегменту
tbt6 db 0  ;старші 4 розряди байту – атрибути сегменту,
;молодші 4 розряди байту - розряди 16-19 розміру сегменту
tbase_3 db 0 ;4-тий байт фізичної 32-розрядної адреси сегменту
descrtest ends
;================
test1 segment para public 'data' use16 ; Визначення таблиці глобальних дескрипторів
tselector0 descrtest	<>
tdescr_gdt descrtest	<>
tdescr_ds descrtest <>
tdescr_es descrtest <>; video
tdescr_ss descrtest <>
tdescr_cs descrtest <>
tgdt_size equ $-tselector0-1
tdeskr_Int_code descrtest <>
test1 ends
;================
;ОПИС вказівника ТАБЛИЦІ ДЕСКРИПТОРІВ
point_dt struc
lim dd 0
adr dd 0
point_dt ends
;Рекомендується розміщувати GDT в окремому  логічному  сегменті
GDT segment para public 'data' use16 ; Визначення таблиці глобальних дескрипторів
selector0 descr	<>
descr_gdt descr	<>
descr_ds descr <>
descr_es descr <>; video
descr_ss descr <>
descr_cs descr <>
gdt_size equ $-selector0-1
deskr_Int_code descr <>
GDT ends

;Визначимо  вказівник для GDT (в логічному сегменті даних _DATA):
ST_p segment use16
Db 1000 dup (0)
Top_stp	dw 1000;equ	$; Top_stp=1000
ST_p ends
IDT	segment para public 'data' use16
Vector=0
Rept 256
Dw Vector * Proc_int_size; зміщення процедури
Dw offset deskr_Int_code; селектор дескриптора в GDT
Db 0; завжди 0
Db 10001111b ;байт атрибутів - шлюз пастки
Dw 0; всі процедури розміщуються в перших 64К
Vector=Vector+1
Endm
IDT	ends
.data
Top_real_mode dd ? ;Перед переключенням у захищений режим  потрібно  заборонити переривання
pidt point_dt <>
pgdt point_dt <> ;вказівник для GDT (в логічному сегменті даних
mes1 db 'Error!!!',13,10,'$'
mess_protect_mode db '0123456'
code_seg equ 10011010b; не підпорядкований сегмент кодів, дозволено читати 
data_seg equ 10010010b; сегмент даних, дозволено записувати
tdata_seg equ 10010010b; тестовий сегмент даних, дозволено читати
stack_seg equ 10010110b; сегмент стека
db 0eah ;машинний код команди jmp
dw offset protect ;зміщення мітки переходу в сегменті кодів
dw offset descr_cs ;селектор сегмента кодів 
dw offset tdescr_cs ;селектор тестового сегмента даних 
tempvar dw 0
.code			
Start: 
mov	eax,cr0
test al,1
;jz MOD_error ; процесор уже в захищеному режимі
;Крім того, необхідно розблокувати 20-й розряд адрес ПЕОМ
in al,92h
or al,2
out	92h,al
mov	ax,GDT
mov ds,ax
assume ds:GDT 
;Формування дескриптора сегмента кодів
mov	descr_cs.limit_1,gdt_size ; розмір сегмента кодів
;формування фізичної адреси сегмента кодів
xor	eax,eax
mov	ax,@code
shl	eax,4 ;відлуння реального режиму від TASM
mov	dword ptr descr_cs.base_1,  eax
mov	descr_cs.attrib,code_seg
;дескриптор GDT формується для доступу до GDT системними 
;програмами в захищеному режимі 
;--------------------------------------------------------
mov descr_gdt.limit_1,gdt_size
xor eax,eax
mov ax,GDT
shl eax,4
mov dword ptr descr_gdt.base_1,eax
mov descr_gdt.attrib,  data_seg
;Аналогічно формуються дескриптори сегментів даних.
mov descr_ds.limit_1,gdt_size
xor eax,eax
mov ax,GDT
shl eax,4
mov dword ptr descr_gdt.base_1,eax
mov descr_gdt.attrib,  data_seg
;Сегмент стека
mov descr_ss.limit_1,10
xor eax,eax
mov ax,ST_p
shl eax,4
mov dword ptr descr_ss.base_1,eax
mov descr_ss.attrib,  stack_seg
;Відеобуфер
mov descr_es.limit_1,0ffffh;
mov dword ptr descr_es.base_1,0b8000h
mov descr_es.attrib,data_seg
;формування  GDT
xor eax,eax
mov ax,GDT
shl eax,4
mov pgdt.adr,eax
mov ax,gdt_size
mov pgdt.lim,eax
;завантаження GDT
lgdt pgdt
;Переключення  у  захищений  режим  виконується установкою в 1 молодшого біта регістра управління CR0:
Cli
Mov word ptr Top_real_mode,sp
Mov	word ptr Top_real_mode+2,ss
mov eax,cr0
or al,1
mov cr0,eax
protect:
;завантажити селектори для інших дескрипторів
;припускаємо, що RPL=0
mov ax,offset descr_ss
mov ss,ax
mov sp,Top_stp
mov ax,offset descr_ds
mov ds,ax
mov ax,offset descr_es
mov es,ax
;Виведення повідомлення на екран
mov cx,20
mov si,offset mess_protect_mode
mov di,1640 ;початкова адреса виведення 
mov ah,07h ;атрибут символів
outmes:
mov al,[si]
mov es:[di],ax
inc si
add di,2
loop outmes
;-----------------------------------------------------
;завантаження тестового сегмента даних в регістр es
mov	ax,test1
mov es,ax
assume es:test1 
;дескриптори тестових сегментів даних.
mov tdescr_ds.tlimit_1,tgdt_size
xor eax,eax
mov ax,test1
shl eax,4
mov dword ptr tdescr_gdt.tbase_1,eax
mov tdescr_gdt.tattrib, tdata_seg
;1. Перевірка захисту  від виходу за межі сегменту даних.
mov si,453[16]
cmp tdescr_ds.tlimit_1,tgdt_size
jg $
;8. Перевірка захисту від завантаження в сегментний регістр 
;селектора дескриптора сегмента іншого типу.
;9. Перевірка захисту від завантаження в сегментний регістр  
;селектора неіснуючого або некоректного дескриптора.
mov tempvar,offset tdescr_cs
cmp tempvar,offset tdescr_ds
jne esprot ;$
mov ax,tempvar
mov es,ax
esprot:
;14. Перевірити запис 1 в біт A
mov cx,tempvar
cmp tdescr_gdt.tattrib,10010011b
je return_dos;$
;===========================
;повернення в реальний режим
return_dos:
assume ds:GDT; 
cli
mov ax, offset descr_GDT
; в режимі реальних адрес в цьому випадку виконували команду mov ax,GDT
mov ds,ax
mov descr_cs.limit_1,0ffffh
mov descr_ds.limit_1,0ffffh
mov descr_ss. attrib,   data_seg
; перезавантаження тіньових регістрів
mov ax,offset descr_ds
mov ds,ax
mov ax,offset descr_es
mov es,ax
mov ax,offset descr_ss
mov ss,ax
db 0eah
dw offset jumpt
dw offset descr_cs
jumpt:
;переключення в режим реальних адрес
mov eax,cr0
and al,0feh
mov cr0,eax
db 0eah
dw offset r_mode
;dw _CODE
r_mode:
assume ds:_DATA
mov ax,_data
mov ds,ax
lss sp,Top_real_mode
sti
mov ah,01h
int 21h ;чекать введення з клавіатури 
mov ax,3
int 10h ; переключить відеоконтролер
;закінчення роботи програми (стандартно)
mov ax,4c00h
int 21h
Int_code segment	para public 'code' use16
Assume cs:Int_code
Vector=0
I_beg:
Pusha
Mov ax,vector
Jmp common_int
I_end:
Proc_int_size = I_end-I_beg
; Процедура обробки 0-го переривання виділена виключно
; для автоматичного визначення її розміру (Proc_int_size)
Vector=1
Rept 255
pusha
Mov	ax,vector
Jmp	common_int
Vector = Vector + 1
Endm
Mes_int	Db		'INTERUPT N'
common_int:
; формування номера переривання в Mes_int
mov	cl,10
div cl; молодша цифра в ah
or ah,30h ;формування текстового коду цифри
mov bh,ah
xor	ah,ah
div	cl; середня цифра в ah, старша - в al
or ax,3030h ;формування текстового коду цифр
mov dx,ax
; виведення повідомлення на екран
push offset descr_es; селектор дескриптора із 1-го етапу
pop	es
mov si,offset Mes_int
mov cx,10
mov di,2620 ;початкова адреса для виведення 
mov ah,07h ;атрибут символів
outstr:
mov al,CS:[si]
stosw
inc si
loop outstr
mov	al,' '
stosw
mov	al,dl ;старша десяткова цифра номера вектора 
stosw
mov	al,dh ;середня десяткова цифра номера вектора
stosw
mov	al,bh ;молодша десяткова цифра номера вектора
stosw
; після виведення повідомлення організуємо передачу управління
; в основний сегмент для переключення в режим реальних адрес
; Для цього використаємо команду IRET
; В даній точці програми в стек записано вміст всіх регістрів, адреса 
;команди, яка визвала виключення, та вміст регістра ознак. 
; Ми все це проігноруємо і запишемо в стек нові дані
pushf
push offset descr_cs; селектор дескриптора сегмента кодів із 1-го етапу
push offset return_dos
iret; передача управління по адресі return_dos основного сегмента кодів
common_end:
Int_code_size =common_end-I_beg
jmp exit
MOD_error:
mov ah,9
mov dx,offset mes1
int 21h
;------------------
exit:
mov ah,1
int 21h
mov ah, 4ch		 
int 21h		
mov ax,_data
mov ds,ax
; формування  IDT
xor eax,eax
mov ax,IDT
shl eax,4
mov pidt.adr,eax
mov pidt.lim,8*256
; завантаження  IDT
lidt pidt
xor eax,eax
mov pidt.adr,eax
mov pidt.lim,3ffh
lidt pidt
Int_code ends
;--------------------------------------------------------

End Start