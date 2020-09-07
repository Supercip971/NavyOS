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

#ifndef _NAVY_X86_IDT_H
#define _NAVY_X86_IDT_H

#include <stdint.h>
#include <stddef.h>

struct idtdesc
{
    uint16_t offset0_15;        /* Offset bits 0..15 */
    uint16_t selector;          /* code seg in GDT or LDT */
    uint8_t zero;
    uint8_t type_attr;          /* type and attr */
    uint16_t offset16_31;       /* Offset bits 16..31 */
} __attribute__((packed));

struct idtr
{
    uint16_t limite;
    uint32_t base;
} __attribute__((packed));

enum type_attr
{
    INTGATE = 0x8e,
    TRAPGATE = 0xef
};

void init_idt_desc(uint16_t, uint32_t, uint8_t, struct idtdesc *);
void init_idt(void);

extern void idt_flush(uint32_t);

#endif
