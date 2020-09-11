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

#include "arch/x86/device/ps2.h"
#include "arch/x86/fadt.h"
#include "arch/x86/io.h"
#include "kernel/log.h"

#include "arch/arch.h"

static bool has_first_channel;
static bool has_second_channel;

void
ps2_wait(void)
{
    uint8_t status = inb(PS2_READ);

    while (status & 0x2);

    return;
}

void
init_ps2(struct ACPISDTHeader *rsdt)
{
    struct FADT *fadt;

    uint8_t byte_0_ram;

    has_second_channel = true;
    has_first_channel = true;

    fadt = find_SDT(rsdt, "FADT");

    /*
     * Step 2: PS/2 exists ? 
     */
    if (fadt->BootArchitectureFlags < 32768)
    {
        has_first_channel = false;
        has_second_channel = false;
        klog(WARNING, "NO PS2 DEVICE !");
        return;
    }

    /*
     * Step 3: Disable devices 
     */
    outb(PS2_REG, 0xad);
    outb(PS2_REG, 0xa8);

    /*
     * Step 4: Flush output buffer 
     */
    inb(PS2_DATA);

    /*
     * Step 5: Set the controller config byte 
     */
    outb(PS2_REG, 0x20);
    byte_0_ram = inb(PS2_DATA);
    outb(PS2_REG, 0x60);
    outb(PS2_DATA, byte_0_ram & 0xdc);

    if ((byte_0_ram & 0x10) == 0)
    {
        has_second_channel = false;
        klog(WARNING, "NO DUAL PS2 !\n");
    }

    /*
     * Step 6: Perform Controller Self Test 
     */
    outb(PS2_REG, 0xaa);
    ps2_wait();

    if (inb(0x60) == 0xfc)
    {
        klog(ERROR, "PS2 Test failed !\n");
        has_second_channel = false;
        has_first_channel = false;

        return;
    }

    /*
     * Step 7: Check dual channel 
     */
    if (has_second_channel)
    {
        outb(PS2_REG, 0xa8);
        byte_0_ram = inb(PS2_DATA);

        if (byte_0_ram & 0x10)
        {
            has_second_channel = false;
            klog(WARNING, "NO DUAL PS2 !\n");
        }

        else
        {
            outb(PS2_REG, 0xa7);
        }
    }

    /*
     * Step 8: Perform Interface Test 
     */
    outb(PS2_REG, 0xab);
    if (inb(PS2_DATA) == 0xfc)
    {
        klog(ERROR, "Couldn't check the first channel of the PS2 controller\n");
        has_first_channel = false;
    }

    if (has_second_channel)
    {
        outb(PS2_REG, 0xa9);

        if (inb(PS2_DATA) == 0xfc)
        {
            klog(ERROR, "Couldn't check the second channel fo the PS2 controller\n");
            has_second_channel = false;
        }
    }

    /*
     * Step 9: Enable device 
     */

    if (has_first_channel)
    {
        outb(PS2_REG, 0xae);

        outb(PS2_REG, 0x20);
        byte_0_ram = inb(PS2_DATA);

        outb(PS2_REG, 0x60);
        outb(PS2_DATA, byte_0_ram | 0x41);
        klog(OK, "First channel PS2 initialised\n");
    }

    if (has_second_channel)
    {
        outb(PS2_REG, 0xa8);

        outb(PS2_REG, 0x20);
        byte_0_ram = inb(PS2_DATA);

        outb(PS2_REG, 0x60);
        outb(PS2_DATA, byte_0_ram | 0x20);
        klog(OK, "Second channel PS2 initialised\n");
    }
}
