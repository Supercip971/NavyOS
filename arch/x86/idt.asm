[ GLOBAL idt_flush ]
idt_flush:
    mov edx, [esp + 4]
    lidt [eax]
    sti 

    ret