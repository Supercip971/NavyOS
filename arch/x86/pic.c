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

#include "arch/x86/pic.h"
#include "arch/x86/io.h"

void 
init_pic(void)
{
    uint8_t mask_master;
    uint8_t mask_slave;

    mask_master = inb(MASTER_DATA);
    mask_slave = inb(SLAVE_DATA);

    outb(MASTER_CMD,  0x10 | 0x01);
    io_wait();
    outb(SLAVE_CMD,  0x10 | 0x01);
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

    outb(MASTER_DATA, mask_master);
    outb(SLAVE_DATA, mask_slave);
}

void 
PIC_sendEOI(uint8_t irq)
{
    if(irq >= 8) {
        outb(SLAVE_CMD, 0x20);
    }

    outb(MASTER_CMD, 0x20);
}