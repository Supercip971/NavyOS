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

#ifndef _NAVY_X86_MADT_H 
#define _NAVY_X86_MADT_H

#include <stdint.h>
#include "arch/x86/acpi.h"

enum MADT_EntryType 
{
    LAPIC       =   0,
    IOAPIC      =   1,
    ISO         =   2,
    NMI         =   4,
    LAPIC_AO    =   5,
};

struct MADT_Entry 
{
    uint8_t type;
    uint8_t length;
};

struct MADT_LAPIC 
{
    uint8_t processor_id;
    uint8_t APIC_id;
    uint32_t flags;         /* If the 0th bit at 1 -> processor enabled */
} __attribute__((packed));

struct MADT_IOAPIC 
{
    struct MADT_Entry e;
    uint8_t IOAPIC_id;
    uint8_t reserved;
    uint32_t IOAPIC_addr;
    uint32_t interrupt_base;
} __attribute__((packed));

struct MADT_ISO 
{
    struct MADT_Entry e;
    uint8_t bus;
    uint8_t irq;            /* The legacy PIC Interrupt this ISO redirects */
    uint32_t interrupt;     /* The starting interrupt this I/O APIC can service */
    uint32_t flags;         /* Further information about the interrupt */
} __attribute__((packed));

struct MADT_NMI 
{
    struct MADT_Entry e;
    uint8_t processor_id;   /* Processor id this NMI corresponds to */
    uint16_t flags;         /* Further information about the interrupt */
    uint8_t LINT;            /* Local Interrupt Pin to mask as non-maskable */
} __attribute__((packed));

struct MADT_LAPIC_AO
{
    struct MADT_Entry e;
    uint16_t reserved;
    uint64_t apic_address;   /* The 64 bit LAPIC address needed ? */
} __attribute__((packed));

struct MADT
{
    struct ACPISDTHeader h;
    uint32_t LAPIC_addr;     /* Local APIC address */
    uint32_t flags;    
    
    struct MADT_Entry entries[];      /* If the 0th bit at 1 -> Dual PICs installed */    
} __attribute__((packed));

#endif