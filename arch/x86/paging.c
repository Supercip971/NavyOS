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

#include "arch/x86/paging.h"

#include <stdint.h>
#include <stddef.h>

static uint32_t page_dir[1024] __attribute__((aligned(4096)));

void
init_paging()
{
    size_t i;

    for(i = 0; i < 1024; i++)
    {
        page_dir[i] = 2;    /* Set as not present */
    }

    _asm_load_directory(page_dir);
}
