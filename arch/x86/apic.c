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

bool
check_apic(void)
{
    uint32_t eax;
    uint32_t edx;

    cpuid(1, &eax, &edx);
    return (bool) edx & CPUID_FEAT_EDX_APIC;
}

uint32_t
cpu_get_apic_base()
{
    uint32_t eax;
    uint32_t edx;

    cpuGetMSR(IA32_APIC_BASE_MSR, &eax, &edx);

    if(MEM_EXT) {
        return (eax & 0xfffff000) | ((edx & 0x0f) << 32);
    } else {
        return (eax & 0xfffff000);
    }
}

void 
cpu_set_apic_base(uint32_t *apic)
{
    uint32_t edx = 0;
    uint32_t eax = (*apic & 0xfffff000) | IA32_APIC_BASE_MSR_ENABLE;
    
    if(MEM_EXT) {
        edx = (*apic >> 32 & 0x0f);
    }

    cpuSetMSR(IA32_APIC_BASE_MSR, eax, edx);
}

uint32_t 
APIC_reg_read(uint32_t reg) 
{
    return *((uint32_t *) (cpu_get_apic_base() + reg));
}

void 
APIC_reg_write(uint32_t reg, uint32_t data)
{
    *((uint32_t *) (cpu_get_apic_base() + reg)) = data;
}

void 
init_apic(void)
{
    disable_pic();
    APIC_reg_write(0xf0, APIC_reg_read(0xf0) | 0x100);
}

void
APIC_sendEOI(void)
{
    APIC_reg_write(0xb0, 0);
}
