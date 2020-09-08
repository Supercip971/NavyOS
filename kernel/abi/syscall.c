/*
 * Copyright (C) 2020  Jordan DALCQ & contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "kernel/abi/syscall.h"
#include "kernel/log.h"
#include <stdarg.h>

uint32_t
syscall(uint32_t eax, uint32_t ebx, uint32_t ecx)
{
    switch (eax)
    {
        case 0:
            klog(ebx, (char *) ecx);
            break;
        default:
            klog(ERROR, "Unkown syscall !\n");
            return 1;
    }

    return 0;
}
