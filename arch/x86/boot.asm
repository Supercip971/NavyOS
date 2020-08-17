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
