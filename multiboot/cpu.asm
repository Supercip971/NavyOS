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

can_cpuid:
        pushfd
        pop eax

        mov ecx, eax ;ECX -> counter
        xor eax, 1 << 21
        push eax 
        popfd

        pushfd
        pop eax

        push ecx
        popfd

        xor eax, ecx
        jz CpuError
        ret

CpuError:
        extern err_cpuid
        call err_cpuid

        cli
        jmp _start.hang

check_long:
        mov eax, 0x80000001
        cpuid
        test edx, 1 << 29
        jz CpuError
        ret
