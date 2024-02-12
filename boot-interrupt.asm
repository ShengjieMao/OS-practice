; prints "Hello" to the screen, using  BIOS interrupt 0x10 with function 0x0e

; video interrupt
mov ah, 0x0e ; tty mode
mov al, 'H'
int 0x10 ; Call interrupt 0x10 to display the character, display 'H'
mov al, 'e'
int 0x10
mov al, 'l'
int 0x10
int 0x10 ; 'l' is still on al, remember?
mov al, 'o'
int 0x10

jmp $ ; jump to current address = infinite loop

; padding and magic number
times 510 - ($-$$) db 0
dw 0xaa55 