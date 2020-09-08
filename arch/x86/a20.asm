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
[GLOBAL check_a20]
[EXTERN init_a20]

check_a20:
        pushad
        mov edi, 0x112345
        mov esi, 0x012345
        mov [esi], esi
        mov [edi], edi 
        cmpsd 
        popad

        pushfd
        pop eax 
        
        ret
