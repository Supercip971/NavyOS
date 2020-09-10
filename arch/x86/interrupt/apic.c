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

#include "arch/x86/cpuid.h"
#include "arch/x86/madt.h"

#include "arch/x86/interrupt/lapic.h"
#include "arch/x86/interrupt/apic.h"
#include "arch/x86/interrupt/pic.h"

#include "arch/arch.h"
#include "kernel/log.h"

#include <macro.h>

bool
check_apic(void)
{
    uint32_t eax;
    uint32_t edx;

    cpuid(1, &eax, &edx);
    return edx & CPUID_FEAT_EDX_APIC;
}

void
APIC_sendEOI(void)
{
    return;
}

void
init_apic(struct ACPISDTHeader *rsdt)
{
    struct MADT_LAPIC *lapic;
    struct MADT_IOAPIC *ioapic;
    struct MADT_ISO *iso;
    struct MADT_NMI *nmi;
    struct MADT_LAPIC_IO *lapic_io;
    struct MADT *madt = (struct MADT *) find_SDT(rsdt, "APIC");
    struct MADT_Entry *entry = (struct MADT_Entry *) ((uint32_t) & madt->entries);


    while ((uint32_t) entry < (uint32_t) & madt->h + (uint32_t) madt->h.Length)
    {
        switch (entry->type)
        {
            case LAPIC:
                lapic = (struct MADT_LAPIC *) entry;
                __unused(lapic);
                klog(OK, "LAPIC !\n");
                break;
            case IOAPIC:
                ioapic = (struct MADT_IOAPIC *) entry;
                __unused(ioapic);
                klog(OK, "IOAPIC !\n");
                break;
            case ISO:
                iso = (struct MADT_ISO *) entry;
                __unused(iso);
                klog(OK, "ISO !\n");
                break;
            case NMI:
                nmi = (struct MADT_NMI *) entry;
                __unused(nmi);
                klog(OK, "NMI !\n");
                break;
            case LAPIC_AO:
                lapic_io = (struct MADT_LAPIC_IO *) entry;
                __unused(lapic_io);
                klog(OK, "LAPIC_AO !\n");
                break;
            default:
                klog(ERROR, "Unknown entry, CODE: %d\n", entry->type);
                hlt();
        }

        entry = (struct MADT_Entry *) ((uint32_t) entry + entry->length);
    }

    return;
}
