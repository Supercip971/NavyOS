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

#ifndef _NAVY_x86_APIC_H 
#define _NAVY_x86_APIC_H

#ifdef __PHYSICAL_MEMORY_EXTENSION__
#define MEM_EXT 1
#else
#define MEM_EXT 0
#endif
#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100 // Processor is a BSP
#define IA32_APIC_BASE_MSR_ENABLE 0x800

#include <stdbool.h>
#include <stdint.h>

bool check_apic(void);
uint32_t cpu_get_apic_base(void);
void cpu_set_apic_base(uint32_t *);

uint32_t APIC_reg_read(uint32_t);
void APIC_reg_write(uint32_t, uint32_t);

void init_apic(void);
void APIC_sendEOI();

#endif