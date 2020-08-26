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

#include "arch/arch.h"
#include "arch/x86/vga.h"
#include "arch/x86/serial.h"

#include "arch/x86/gdt.h"
#include "arch/x86/idt.h"
#include "arch/x86/acpi.h"
#include "arch/x86/pic.h"
#include "arch/x86/io.h"

#include "kernel/log.h"
#include <multiboot2.h>


void
debug_print(const char *msg)
{
    serial_print(COM1, msg);
}

void
debug_putc(const char c)
{
    serial_putc(COM1, c);
}

void
debug_clear(void)
{
    debug_print("\033c");
}

void
init_arch(uint32_t addr)
{
    term_init();
    serial_init(COM1);
    serial_print(COM1, "\033c");

    init_gdt();
    klog(LOG, "GDT loaded\n");

    init_acpi(addr);
    klog(LOG, "ACPI initialised\n");

    init_pic();
    klog(LOG, "PIC initialised\n");

    init_idt();
    klog(LOG, "IDT loaded\n");
}

void
breakpoint(void)
{
    asm volatile ("1: jmp 1b");
}

void
hlt(void)
{
    asm("hlt");
}
