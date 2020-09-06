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

#include "arch/x86/gdt.h"
#include "arch/x86/idt.h"
#include "arch/x86/acpi.h"
#include "arch/x86/rsdt.h"
#include "arch/x86/apic.h"
#include "arch/x86/pic.h"
#include "arch/x86/io.h"
#include "arch/x86/paging.h"
#include "arch/x86/pit.h"

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
    klog(LOG, "GDT loaded\n");

    /*
     * init_paging(); klog(LOG, "Paging initialised\n");
     */

    rsdt = init_acpi(addr);

    klog(LOG, "ACPI initialised\n");

    /*
     * if (check_apic()) { disable_pic(); init_apic(rsdt); klog(LOG, "APIC
     * initialised\n"); }
     * 
     * else {
     */
    init_ps2(rsdt);
    klog(LOG, "PS2 initialised\n");

    init_pic();
    klog(LOG, "PIC initialised\n");
    /*
     * } 
     */

    init_idt();
    klog(LOG, "IDT loaded\n");


    init_pit(1000);
    klog(LOG, "PIT initialised\n");
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
