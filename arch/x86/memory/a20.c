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

#include "arch/x86/memory/a20.h"
#include "arch/x86/device/ps2.h"
#include "arch/x86/io.h"
#include "arch/arch.h"

#include "kernel/log.h"

void
init_a20(void)
{
    uint8_t a;

    disable_interrupts();
    ps2_wait();

    outb(PS2_REG, 0xad);
    ps2_wait();

    a = inb(PS2_DATA);
    ps2_wait();

    outb(PS2_REG, 0xd1);
    ps2_wait();

    outb(PS2_REG, a | 2);
    ps2_wait();

    outb(PS2_REG, 0xae);
    enable_interrupts();

    return;
}
