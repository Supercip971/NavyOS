/*
 * Copyright (C) 2020  Jordan DALCQ & contributors
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

#ifndef _NAVY_LIBMULTIBOOT_H
#define _NAVY_LIBMULTIBOOT_H

#include <stdint.h>
#include <stddef.h>
#include <Navy/range.h>
#include <multiboot2.h>

#define LIMIT_CMD_SIZE 256
#define LIMIT_MEMORY_MAP_SIZE 64
#define LIMIT_MODULES_SIZE 16

struct MMAP_ENTRY
{
    Range range;
    uint8_t type;
};

typedef struct MMAP_ENTRY MemoryMapEntry;

struct MODULE
{
    Range range;
    char cmd[LIMIT_CMD_SIZE];
};

typedef struct MODULE Module;

struct BOOTINFO
{
    size_t memory_map_size;
    size_t modules_size;
    size_t memory_usable;

    uintptr_t rsdp;

    MemoryMapEntry mmap[LIMIT_MEMORY_MAP_SIZE];
    Module modules[LIMIT_MODULES_SIZE];
};

typedef struct BOOTINFO BootInfo;

void multiboot2_parse_header(BootInfo *, uintptr_t);

#endif
