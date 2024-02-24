mov ah, 0x0e ; tty

mov al, [the_secret]
int 0x10 

mov bx, 0x7c0 ; segment is automatically <<4 for you: i.e., given ds = 0x4d, then [0x20] is 0x4d0 + 0x20 = 0x4f0
mov ds, bx
; WARNING: all memory references will be offset by 'ds' 
; used implicitly by cpu
mov al, [the_secret]
int 0x10

mov al, [es:the_secret]
int 0x10 ; doesn't look right... isn't 'es' currently 0x000?

mov bx, 0x7c0
mov es, bx
mov al, [es:the_secret]
int 0x10


jmp $

the_secret:
    db "X"

times 510 - ($-$$) db 0
dw 0xaa55