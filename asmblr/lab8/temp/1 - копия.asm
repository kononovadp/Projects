.386p
Data Segment			
Top_real_mode dd ?

db        0eah                  ;�������� ��� ������� jmp
dw        offset protect        ;������� ���� �������� � ������� ����
dw        offset deskr_cs         ;�������� �������� ���� 
dw        offset deskr_ss         ;�������� �������� ���� 
dw        offset deskr_es         ;�������� �������� ���� 
Data Ends			
Code Segment	
Assume cs:Code, ds:Data		
Start: 
Cli
Mov word ptr Top_real_mode,sp
Mov	word ptr Top_real_mode+2,ss
mov eax,cr0
or al,1
mov cr0,eax
;------------


mov ah,1
int 21h
mov ah, 4ch		 
int 21h
End Start	
protect:
;����������� ��������� ��� ����� �����������
; ����������, �� RPL=0
mov        ax,offset deskr_ss
mov        ss,ax
mov        sp,Top_stp
mov        ax,offset deskr_ds
mov        ds,ax
mov        ax,offset deskr_es
mov        es,ax	
Code Ends

;protect:
;����������� ��������� ��� ����� �����������
; ����������, �� RPL=0


