;
; Copyright (C) 2020 Jordan DALCQ & Contributors
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.
;

;=== MULTIBOOT ===

[ BITS 32 ]

section .multiboot
    MBALIGN  equ  1 << 0            
    MEMINFO  equ  1 << 1            
    FLAGS    equ  MBALIGN | MEMINFO 
    MAGIC    equ  0x1BADB002       
    CHECKSUM equ -(MAGIC + FLAGS) 
 
    align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
 
section .bss
    align 16
    stack_bottom:
        resb 16384 ; 16 KiB
    stack_top:
 
section .text
    global _start:function (_start.end - _start)
    _start:
	mov esp, stack_top

	extern kmain
	call kmain
 
	cli
.hang:	hlt
	jmp .hang
.end:

;; === MULTIBOOT ===

;; === GDT ===

[ GLOBAL gdt_flush ]    ; Allows the C code to call gdt_flush().

gdt_flush:
   mov eax, [esp+4]  ; Get the pointer to the GDT, passed as a parameter.
   lgdt [eax]        ; Load the new GDT pointer

   mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
   mov ds, ax        ; Load all data segment selectors
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!
.flush:
   ret

[ GLOBAL tss_flush ]
tss_flush:
    mov ax, 0x2B
    ltr ax 
    ret

; === GDT ===

; === IDT ===
[ GLOBAL _asm_default_int ]
_asm_default_int:
    pusha
    extern isr_default_int
    call isr_default_int

    ;; Send EOI to the PIC (just for testing, will use the C function later)
    mov al, 0x20
    out 0x20, al

    popa
    iret

[ GLOBAL idt_flush ]
idt_flush:
    mov edx, [esp + 4]
    lidt [eax]
    sti 
    ret
; === IDT ===