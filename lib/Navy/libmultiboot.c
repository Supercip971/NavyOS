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

#include <Navy/range.h>
#include <Navy/libmultiboot.h>
#include <Navy/macro.h>

#include <stdint.h>
#include <multiboot2.h>
#include <string.h>

#include "arch/arch.h"
#include "kernel/log.h"

void
multiboot2_parse_mmap(BootInfo * info, struct multiboot_tag_mmap *tag)
{
    Range range;
    MemoryMapEntry *entry;
    struct multiboot_mmap_entry *mmap;

    info->memory_map_size = 0;
    info->memory_usable = 0;

    for (mmap = tag->entries; (uint8_t *) mmap < (uint8_t *) tag + tag->size;
         mmap = (struct multiboot_mmap_entry *) ((uintptr_t) mmap + tag->entry_size))
    {
        if (info->memory_map_size > LIMIT_MEMORY_MAP_SIZE)
        {
            klog(ERROR, "Invalid memory map size ! (%d)\n", info->memory_usable);
            disable_interrupts();
            hlt();
        }

        if ((mmap->addr > UINT32_MAX) || (mmap->addr + mmap->len > UINT32_MAX))
        {
            continue;
        }

        if (mmap->type == MULTIBOOT_MEMORY_AVAILABLE)
        {
            info->memory_usable += mmap->len;
        }

        entry = &info->mmap[info->memory_map_size];

        range.begin = mmap->addr;
        range.size = mmap->len;

        align_range(&range);

        entry->range = range;
        entry->type = mmap->type;

        info->memory_map_size++;
    }
}

void
multiboot2_parse_module(BootInfo * info, struct multiboot_tag_module *m)
{
    Module *module;
    Range range;

    if (info->modules_size < LIMIT_MODULES_SIZE)
    {
        klog(ERROR, "Cannot parse the modules !\n");
        disable_interrupts();
        hlt();
    }

    module = &info->modules[info->modules_size];

    range.begin = m->mod_start;
    range.size = m->mod_end - m->mod_start;
    align_range(&range);

    strncpy(module->cmd, (const char *) m->cmdline, LIMIT_CMD_SIZE);

    info->modules_size++;
}


void
multiboot2_parse_header(BootInfo * info, uintptr_t addr)
{
    struct multiboot_tag *tag = (struct multiboot_tag *) addr + 8;

    while (tag->type != MULTIBOOT_TAG_TYPE_END)
    {
        switch (tag->type)
        {
            case MULTIBOOT_TAG_TYPE_ACPI_OLD:
                info->rsdp = (uintptr_t) & ((struct multiboot_tag_old_acpi *) tag)->rsdp;
                break;

            case MULTIBOOT_TAG_TYPE_MMAP:
                multiboot2_parse_mmap(info, (struct multiboot_tag_mmap *) tag);
                break;

            case MULTIBOOT_TAG_TYPE_MODULE:
                multiboot2_parse_module(info, (struct multiboot_tag_module *) tag);
                break;
        }

        tag =
            (struct multiboot_tag *) __align_up((uintptr_t) tag + tag->size,
                                                MULTIBOOT_TAG_ALIGN);
    }

}
