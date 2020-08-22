[ GLOBAL _asm_default_int ]
_asm_default_int:
    pushad
    extern isr_default_int
    call isr_default_int

    popad
    iret

[ GLOBAL idt_flush ]
idt_flush:
    mov edx, [esp + 4]
    lidt [eax]
    sti 

    ret