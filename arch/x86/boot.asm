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

[ BITS 32 ]

;; Multiboot 2
MULTIBOOT2_HEADER_MAGIC                 equ 0xe85250d6
MULTIBOOT_ARCHITECTURE_I386             equ 0
HEADER_LENGTH                           equ multiboot_end - multiboot_start
CHECKSUM                                equ -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT_ARCHITECTURE_I386 + HEADER_LENGTH) 
MULTIBOOT_HEADER_TAG_ADDRESS            equ 2
MULTIBOOT_HEADER_TAG_OPTIONAL           equ 1
MULTIBOOT_TAG_TYPE_FRAMEBUFFER          equ 8
MULTIBOOT_HEADER_TAG_END                equ 0

section .multiboot
align 8 
multiboot_start:
    dd MULTIBOOT2_HEADER_MAGIC
    dd MULTIBOOT_ARCHITECTURE_I386
    dd HEADER_LENGTH
    dd CHECKSUM

align 8
framebuffer_tag_start:	
    dw MULTIBOOT_TAG_TYPE_FRAMEBUFFER
    dw MULTIBOOT_HEADER_TAG_OPTIONAL
    dd framebuffer_tag_start - framebuffer_tag_stop 
    dd 20
    dd 0
    dd 0
    dd 32
framebuffer_tag_stop:

align 8
    dw MULTIBOOT_HEADER_TAG_END
    dw 0
    dd 8
multiboot_end:
;;
 
section .bss
    align 16
    stack_bottom:
        resb 16384 ; 16 KiB
    stack_top:

section .text
    global _start:function (_start.end - _start)
    _start:
	cli
    cld


	mov esp, stack_top
    xor ebp, ebp

    ; Push the pointer to the Multiboot information struct
    push eax

    ; Push the magic value 
    push ebx

	extern kmain
	call kmain
 
.hang:	hlt
	jmp .hang
.end:
