; Infinite loop (e9 fd ff) -> machine code for the jmp instruction
loop:
    jmp loop 

; Fill with 510 zeros minus the size of the previous code
times 510-($-$$) db 0
; Magic number: the last two bytes (511 and 512), BIOS checks to identify a valid boot sector
dw 0xaa55 

; to compile: 
; nasm -f bin boot_sect_simple.asm -o boot_sect_simple.bin --> will cause OSX warning, so instead,
; qemu boot_sect_simple.bin
