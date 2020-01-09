CODE SEGMENT BYTE PUBLIC
                   ASSUME CS:CODE
                   PUBLIC UpperCase, StringOf    ; объявить имена
              function Uppercase(S: String): String
              UpperRes        EQU  DWORD PTR [BP+10]
              UpperStr        EQU  DWORD PTR [BP+6]
              Uppercase       PROC FAR
                    PUSH BP            ; сохранить регистр BP
                    MOV  BP,SP         ; установить стек
                    PUSH DS            ; сохранить регистр DS
                    LDS  SI,UpperStr   ; загрузить адрес строки
                    LES  DI,UpperRes   ; загрузить адрес результата
                    CLD                ; переместить строку
                    LODSB              ; загрузить длину строки
                    STOSB              ; скопировать результат
                    MOV CL,AL          ; поместить длину строки в СХ
                    XOR CH,CH
                    JCXZ U3            ; пропустить в случае пустой
                                       ; строки
              U1:   LODSB              ; пропустить, если символ отличен
                                       ; от 'а'...'z'
                    CPM AL,'a'
                    JB  U2
                    CPM AL,'z'
                    JA  U2             ; переместить строку
                    SUB AL,'a'-'A'     ; преобразовать в прописные буквы
              U2:   STOBS              ; сохранить результат

                    LOOP U1            ; цикл по всем символам
              U3:   POP  DS            ; восстановить регистр DS
                    POP  BP            ; восстановить регистр ВР
                    RET  4             ; удалить параметры и возвратить
                                       ; управление
              UpperCase   ENDP
              ; function StringOf(Ch: Char; Count: Byte): String
              StrOfRes        EQU  DWORD PTR [BP + 10]
              StrOfChar       EQU  BYTE  PTR [BP + 8]
              StrOfCOunt      EQU  BYTE  PTR [BP + 6]
               StringOf       PROC FAR
                 PUSH BP               ; сохранить регистр ВР
                 MOV  BP,SP            ; установить границы стека
                 LES  DI,StrOfRes      ; загрузить адрес результата
                 MOV  AL,StrOfCount    ; загрузить счетчик
                 CLD                   ; продвинуться на строку
                 STOSB                 ; сохранить длину
                 MOV  CL,AL            ; поместить значение счетчика в CX
                 XOR  CH,CH
                 MOV  AL,StrOfChar     ; загрузить символ
                 REP  STOSB            ; сохранить строку символов
                 POP                   ; восстановить ВР
                 RET                   ; извлечь параметры и выйти
              SrtingOf    ENDP
              CODE       ENDS
                         END

             Чтобы ассемблировать  этот  пример  и скомпилировать модуль,
        можно использовать следующие команды:

             TASM STR5
             BPC stringer