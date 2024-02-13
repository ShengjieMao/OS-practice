; string:
mystring:
    db 'Hello, World', 0


; function:
; jump conditions: if equal, if less than, etc.
; calling function is a jump to a label:
;       >call< and >ret< will help to store return address with CPU, >pusha< and >popa< helps save register data
mov al, 'X'
jmp print
endprint:

...

print:
    mov ah, 0x0e  ; tty code
    int 0x10      ; I assume that 'al' already has the character
    jmp endprint  ; this label is also pre-agreed


; external files:
%include "fileName.asm"

