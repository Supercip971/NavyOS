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

#include "arch/x86/interrupt/pic.h"
#include "arch/x86/io.h"

#include "kernel/log.h"

#include <Navy/macro.h>

void
init_pic(void)
{
    outb(MASTER_CMD, 0x10 | 0x01);
    io_wait();
    outb(SLAVE_CMD, 0x10 | 0x01);
    io_wait();

    outb(MASTER_DATA, MASTER_OFFSET);
    io_wait();
    outb(SLAVE_DATA, SLAVE_OFFSET);
    io_wait();

    outb(MASTER_DATA, 4);
    io_wait();
    outb(SLAVE_DATA, 2);
    io_wait();

    outb(MASTER_DATA, 0x01);
    io_wait();
    outb(SLAVE_DATA, 0x01);
    io_wait();

    outb(MASTER_DATA, 0);
    io_wait();
    outb(SLAVE_DATA, 0);
    io_wait();
}

void
PIC_sendEOI(int intno)
{
    if (intno >= 40)
    {
        outb(SLAVE_CMD, 0x20);
    }

    outb(MASTER_CMD, 0x20);

}
