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

[ GLOBAL _asm_init_paging ]
_asm_init_paging:
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax 
    ret

[ GLOBAL _asm_load_pagedir ]
_asm_load_pagedir:
    mov eax, [esp + 4]
    mov cr3, eax 
    ret

[ GLOBAL _asm_reload_pagedir ]
_asm_reload_pagedir:
    mov eax, cr3 
    mov cr3, eax
    ret
