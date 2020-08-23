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


#include "kernel/log.h"
#include "arch/x86/vga.h"
#include "arch/x86/pic.h"
#include "arch/x86/interrupt.h"
#include "arch/arch.h"

#include <macro.h>
#include <stdint.h>

const char *exceptions[32] = {
    "Division by zero", 
    "Debug", 
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating-Point Exception",
    "Aligment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception"
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Security Exception",
    "Reserved"
};

void 
register_dump(struct InterruptStackFrame stackframe)
{  
    klog(NONE, " CS=%08x  DS=%08x  ES=%08x  FS=%08x   GS=%08x\n", stackframe.cs, stackframe.ds, stackframe.es, stackframe.fs, stackframe.gs);
    klog(NONE, "EAX=%08x EBX=%08x ECX=%08x EDX=%08x\n", stackframe.eax, stackframe.ebx, stackframe.ecx, stackframe.edx);
    klog(NONE, "EDI=%08x ESI=%08x EBP=%08x ESP=%08x\n", stackframe.edi, stackframe.esi, stackframe.ebp, stackframe.esp);
    klog(NONE, "INT=%08x ERR=%08x EIP=%08x FLG=%08x\n", stackframe.intno, stackframe.err, stackframe.eip, stackframe.eflags);
}

void 
interrupts_handler(uint32_t esp, struct InterruptStackFrame stackframe)
{
    __unused(esp);
    
    if(stackframe.intno < 32) {
        debug_clear();
        klog(ERROR, "%s (INT: %d, ERR: %d)\n", exceptions[stackframe.intno], stackframe.intno, stackframe.err);
        klog(NONE, "\n\n === CPU DUMP === \n\n");
        register_dump(stackframe);
        asm("hlt");
    }

    PIC_sendEOI();
}