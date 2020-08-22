%macro INTERRUPT_NAME 1
dd __interrupt%1
%endmacro

%macro INTERRUPT_ERR 1
__interrupt%1:
    push %1
    jmp _asm_interrupts_handler 
%endmacro

%macro INTERRUPT_NOERR 1
__interrupt%1:
    push 0
    push %1
    jmp _asm_interrupts_handler
%endmacro

%macro INTERRUPT_SYSCALL 1
__interrupt%1:
    push 0
    push %1
    jmp _asm_interrupts_handler
%endmacro

[ EXTERN interrupts_handler ]

_asm_interrupts_handler:
    cld

    pushad  ; Push EAX, ECX, EDX, EBX, ESP, EBP, ESI et EDI

    push ds
    push es 
    push fs
    push gs
    
    ; Check if in the kernel seg
    mov ax, 0x10

    mov ds, ax 
    mov es, ax 
    mov fs, ax 
    mov gs, ax 

    push esp 

    call interrupts_handler 

    pop gs 
    pop fs 
    pop es 
    pop ds 

    popad 

    add esp, 8; pop errcode and interrupt nbr

    iret ; Return from iterrupt


INTERRUPT_NOERR 0

[ GLOBAL __interrupt_vector]

__interrupt_vector:
    INTERRUPT_NAME 0