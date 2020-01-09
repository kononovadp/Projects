CODE SEGMENT BYTE PUBLIC
                   ASSUME CS:CODE
                   PUBLIC UpperCase, StringOf    ; �������� �����
              function Uppercase(S: String): String
              UpperRes        EQU  DWORD PTR [BP+10]
              UpperStr        EQU  DWORD PTR [BP+6]
              Uppercase       PROC FAR
                    PUSH BP            ; ��������� ������� BP
                    MOV  BP,SP         ; ���������� ����
                    PUSH DS            ; ��������� ������� DS
                    LDS  SI,UpperStr   ; ��������� ����� ������
                    LES  DI,UpperRes   ; ��������� ����� ����������
                    CLD                ; ����������� ������
                    LODSB              ; ��������� ����� ������
                    STOSB              ; ����������� ���������
                    MOV CL,AL          ; ��������� ����� ������ � ��
                    XOR CH,CH
                    JCXZ U3            ; ���������� � ������ ������
                                       ; ������
              U1:   LODSB              ; ����������, ���� ������ �������
                                       ; �� '�'...'z'
                    CPM AL,'a'
                    JB  U2
                    CPM AL,'z'
                    JA  U2             ; ����������� ������
                    SUB AL,'a'-'A'     ; ������������� � ��������� �����
              U2:   STOBS              ; ��������� ���������

                    LOOP U1            ; ���� �� ���� ��������
              U3:   POP  DS            ; ������������ ������� DS
                    POP  BP            ; ������������ ������� ��
                    RET  4             ; ������� ��������� � ����������
                                       ; ����������
              UpperCase   ENDP
              ; function StringOf(Ch: Char; Count: Byte): String
              StrOfRes        EQU  DWORD PTR [BP + 10]
              StrOfChar       EQU  BYTE  PTR [BP + 8]
              StrOfCOunt      EQU  BYTE  PTR [BP + 6]
               StringOf       PROC FAR
                 PUSH BP               ; ��������� ������� ��
                 MOV  BP,SP            ; ���������� ������� �����
                 LES  DI,StrOfRes      ; ��������� ����� ����������
                 MOV  AL,StrOfCount    ; ��������� �������
                 CLD                   ; ������������ �� ������
                 STOSB                 ; ��������� �����
                 MOV  CL,AL            ; ��������� �������� �������� � CX
                 XOR  CH,CH
                 MOV  AL,StrOfChar     ; ��������� ������
                 REP  STOSB            ; ��������� ������ ��������
                 POP                   ; ������������ ��
                 RET                   ; ������� ��������� � �����
              SrtingOf    ENDP
              CODE       ENDS
                         END

             ����� ��������������  ����  ������  � �������������� ������,
        ����� ������������ ��������� �������:

             TASM STR5
             BPC stringer