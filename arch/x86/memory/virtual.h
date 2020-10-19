/*
 * Copyright (C) 2020 Jordan DALCQ & contributors 
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


#ifndef _NAVY_X86_VIRTUAL_H
#define _NAVY_x86_VIRTUAL_H
#pragma GCC diagnostic ignored "-Wpedantic"

#ifndef PAGE_SIZE
#define PAGE_SIZE (4096)
#endif

#define __pd_index(x) ((x) >> 22)
#define __pt_index(x) (((x) >> 12) & 0x03FF)

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <multiboot2.h>
#include <Navy/libmultiboot.h>

#include <Navy/range.h>

#define MEMORY_NONE (0)
#define MEMORY_USER (1 << 0)
#define MEMORY_CLEAR (1 << 1)

union PAGE_DIR_ENTRY
{
    struct
    {
        bool present:1;
        bool write:1;
        bool user:1;
        bool write_trough:1;
        bool cache_disabled:1;
        bool accessed:1;
        bool dirty:1;
        bool pat:1;
        uint32_t ignored:4;
        uint32_t page_framenbr:20;
    } __attribute__((packed));

    uint32_t as_uint;

} __attribute__((packed));

typedef union PAGE_DIR_ENTRY PageDirEntry;

struct PAGE_DIR
{
    PageDirEntry entries[1024];
} __attribute__((packed));

union TABLE_ENTRY
{
    struct
    {
        bool present:1;
        bool write:1;
        bool user:1;
        bool write_trough:1;
        bool cache_disabled:1;
        bool accessed:1;
        bool ignored1:1;
        bool LargePage:1;
        uint32_t Ignored2:4;
        uint32_t page_framenbr:20;
    } __attribute__((packed));

    uint32_t as_uint;
} __attribute__((packed));

typedef union TABLE_ENTRY PageTableEntry;

struct PAGE_TABLE
{
    PageTableEntry entries[1024];
} __attribute__((packed));

void init_paging(BootInfo *);
void allocate_page(size_t);
void memory_map_identity(void *, Range, uint8_t);
void virtual_free(void *, Range);
int address_space_switch(void *);

bool is_virtual_present(void *, uintptr_t);
int virtual_map(void *, Range, uintptr_t, uint8_t);
uintptr_t virtual_to_physical(void *, uintptr_t);

extern void _asm_init_paging(void);
extern void _asm_load_pagedir(uintptr_t);
extern void _asm_reload_pagedir(void);

#endif
