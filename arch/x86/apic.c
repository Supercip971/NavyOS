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

#include "arch/x86/apic.h"
#include "arch/x86/pic.h"
#include "arch/x86/cpuid.h"
#include "arch/x86/madt.h"

#include "arch/arch.h"
#include "kernel/log.h"

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
    struct MADT *madt = (struct MADT *)find_SDT(rsdt, "APIC");
    klog(OK, madt->h.Signature);
    return;
}
