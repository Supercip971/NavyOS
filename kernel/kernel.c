/*
 * Copyright (C) 2020 Jordan DALCQ & contributors
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

#include <stddef.h>
#include <stdint.h>
#include <multiboot2.h>
#include <Navy/libmultiboot.h>


#include "kernel/warning.h"
#include "kernel/log.h"
#include "kernel/ascii.h"
#include "arch/arch.h"

void
kmain(uintptr_t addr, uint32_t magic)
{
    BootInfo info;

    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC)
    {
        klog(ERROR, "Invalid magic number: 0x%x\n", magic);
        disable_interrupts();
        hlt();
    }

    multiboot2_parse_header(&info, addr);


    init_arch(&info);

    klog(NONE, ascii_art);
    klog(OK, "Available memory: %dMib\n", info.memory_usable / (1024 * 1024));
    vga_print(ascii_art);

    disable_interrupts();
    hlt();
}
