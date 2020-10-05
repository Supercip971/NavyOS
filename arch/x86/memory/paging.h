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


#ifndef _NAVY_X86_PAGING_H
#define _NAVY_x86_PAGING_H
#pragma GCC diagnostic ignored "-Wpedantic"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


struct PAGE_DIR_ENTRY
{
    bool present:1;
    bool read_write:1;
    bool user_supervisor:1;
    bool write_trough:1;
    bool cache_disabled:1;
    bool accessed:1;
    bool zero:1;
    bool page_size:1;
    bool ignored:1;
    uint8_t available:3;
    uint32_t page_framenbr:20;
} __attribute__((packed));


struct PAGE_DIR
{
    struct PAGE_DIR_ENTRY entries[1024];
};

struct PAGE_TABLE_ENTRY
{
    bool present:1;
    bool read_write:1;
    bool user_supervisor:1;
    bool write_trough:1;
    bool cache_disabled:1;
    bool accessed:1;
    bool dirty:1;
    bool PAT:1;
    bool global:1;
    uint8_t available:3;
    uint32_t page_framenbr:20;
} __attribute__((packed));

struct PAGE_TABLE
{
    struct PAGE_TABLE_ENTRY entries[1024];
};

void init_paging(void);
void allocate_page(size_t);
extern void _asm_init_paging(void);
extern void _asm_load_pagedir(struct PAGE_DIR_ENTRY *);
extern void _asm_reload_pagedir(void);

#endif
