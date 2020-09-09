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


#ifndef _NAVY_X86_PAGING_H
#define _NAVY_x86_PAGING_H
#pragma GCC diagnostic ignored "-Wpedantic"

#include <stdint.h>

void init_paging(void);
extern void _asm_load_directory(uint32_t *);

union PAGE_DIR
{
    struct
    {
        uint32_t page_align:20;
        uint8_t available:2;
        uint8_t ignored:1;
        uint8_t page_size:1;
        uint8_t zero:1;
        uint8_t accessed:1;
        uint8_t cache_disabled:1;
        uint8_t write_trough:1;
        uint8_t user_supervisor:1;
        uint8_t read_write:1;
        uint8_t present:1;
    } bits;

    uint32_t content:31;
};

union PAGE_ENTRY
{
    struct
    {
        uint32_t page_align:20;
        uint8_t available:2;
        uint8_t global:1;
        uint8_t PAT:1;
        uint8_t dirty:1;
        uint8_t accessed:1;
        uint8_t cache_disabled:1;
        uint8_t write_trough:1;
        uint8_t user_supervisor:1;
        uint8_t read_write:1;
        uint8_t present:1;
    } bits;

    uint32_t content:31;
};

#endif
