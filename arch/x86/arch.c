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
#include "arch/x86/device/vga.h"
#include "arch/x86/device/keyboard.h"
#include "arch/x86/device/serial.h"
#include "arch/x86/device/ps2.h"
#include "arch/x86/device/pit.h"

#include "arch/x86/interrupt/idt.h"
#include "arch/x86/interrupt/apic.h"
#include "arch/x86/interrupt/pic.h"

#include "arch/x86/acpi.h"
#include "arch/x86/rsdt.h"
#include "arch/x86/io.h"

#include "arch/x86/memory/a20.h"
#include "arch/x86/memory/gdt.h"
#include "arch/x86/memory/paging.h"

#include "kernel/log.h"
#include <macro.h>
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
    struct ACPISDTHeader *rsdt;

    term_init();
    serial_init(COM1);
    serial_print(COM1, "\033c");

    init_gdt();
    klog(OK, "GDT loaded\n");

    rsdt = init_acpi(addr);
    klog(OK, "ACPI initialised\n");

    init_ps2(rsdt);

    init_pic();
    klog(OK, "PIC initialised\n");

    init_idt();
    klog(OK, "IDT loaded\n");

    init_pit(1000);
    klog(OK, "PIT initialised\n");

    if (check_a20())
    {
        klog(OK, "A20 Line already enabled\n");
    }

    else
    {
        init_a20();
        if (!check_a20())
        {
            klog(ERROR, "Couldn't enable A20 Line !\n");
            disable_interrupts();
            hlt();
        }
    }

    init_paging();
    klog(OK, "Paging enabled\n");
}

void
breakpoint(void)
{
    __asm__ volatile ("1: jmp 1b");
}

void
hlt(void)
{
    __asm__("hlt");
}

void
disable_interrupts(void)
{
    __asm__("cli");
}

void
enable_interrupts(void)
{
    __asm__("sti");
}

void
vga_print(const char *s)
{
    term_puts(s, LIGHT_GREY, BLACK);
}

void
disable_vga_cursor()
{
    disable_cursor();
}

void
vga_printerr(const char *s)
{
    term_puts(s, WHITE, RED);
}

void
vga_putc(char c)
{
    term_putc(c, LIGHT_GREY, BLACK);
}

void
reboot(void)
{
    uint8_t good = 0x2;

    while (good & 0x02)
    {
        good = inb(0x64);
    }

    outb(0x64, 0xFE);
    hlt();
}

unsigned char
kbd_getc(void)
{
    return getKeyChar();
}

char
kbd_lastKeyCode(void)
{
    return getKeyChar();
}
