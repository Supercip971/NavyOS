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

#ifndef _NAVY_X86_GDT_H
#define _NAVY_X86_GDT_H

#define GDT_SIZE 5

#include <stdint.h>

struct gdtdesc {    // https://wiki.osdev.org/File:Gdtr.png
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));

struct gdtentry {   // https://wiki.osdev.org/File:GDT_Entry.png
    uint16_t base0_15;
    uint16_t limit0_15;
    uint8_t base24_31;
    uint8_t limit16_19;
    uint8_t base16_23;

    uint8_t access;
    uint8_t flags;
} __attribute__((packed));


enum gdtbit {   // https://wiki.osdev.org/File:Gdt_bits_fixed.png
    // Access Byte
    PRESENT     = 0b10000000,
    CODE_SEQ    = 0b00010000,
    DATA_SEQ    = 0b00010000,
    USER_PRIV   = 0b01100000,
    EXECUTABLE  = 0b00001000,
    GROWS_DOWN  = 0b00000100,
    READ_WRITE  = 0b00000010,

    // Flag
    BYTE_GR     = 0b0000,
    PAGE_GR     = 0b1000,
    BITS16      = 0b0000,
    BITS32      = 0b0100,
};

void init_gdt_desc(uint32_t, uint32_t, uint8_t, uint8_t, struct gdtentry *);
void init_gdt(void);

extern void gdt_flush(uint32_t);

#endif