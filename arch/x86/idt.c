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

#include "arch/x86/idt.h"
#include "arch/x86/io.h"

#include <string.h>
#include <stdint.h>

struct idtdesc kidt[256];
struct idtr kidtr;

extern uint32_t __interrupt_vector[];

void
init_idt_desc(uint16_t selector, uint32_t offset, uint8_t type_attr, struct idtdesc *desc)
{
    desc->offset0_15 = (offset & 0xffff);
    desc->selector = selector;
    desc->zero = 0;
    desc->type_attr = type_attr;
    desc->offset16_31 = (offset & 0xffff0000) >> 16;
}

void
init_idt(void)
{
    uint16_t i;

    for (i = 0; i < 256; i++)
    {
        init_idt_desc(0x08, __interrupt_vector[i], INTGATE, &kidt[i]);
    }


    kidtr.limite = sizeof(struct idtdesc) * 256;
    kidtr.base = (uint32_t) & kidt[0];

    idt_flush((uint32_t) & kidtr);
}
