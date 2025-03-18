BITS 16
org 0x7c00 

boot:
    mov     si, message
    mov     ah, 0x0e 

.read_loop:

    lodsb
    or      al, al 
    jz      halt_program 
    int     0x10 
    jmp     .read_loop

halt_program:
    cli     ;clear interupt flag 
    hlt     ;halt 

message : db "CHRINOVIC'S TERRIBLE BOOTLOADER...", 0 

times 510 - ($-$$)db 0; pad remaaing t10 bytes with zeros
dw 0xaa55




