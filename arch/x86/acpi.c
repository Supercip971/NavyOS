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

#include "arch/x86/acpi.h"
#include "arch/x86/rsdp.h"
#include "arch/x86/fadt.h"
#include "arch/x86/io.h"

#include "kernel/log.h"

#include <multiboot2.h>
#include <Navy/libmultiboot.h>


struct ACPISDTHeader *
init_acpi(BootInfo * info)
{
    struct ACPISDTHeader *rsdt;
    struct FADT *fadt;

    struct RSDPDescriptor *rsdp = (struct RSDPDescriptor *) info->rsdp;

    klog(OK, "RSDP found on 0x%x\n", info->rsdp);
    klog(LOG, "ACPI Revision number %d\n", rsdp->Revision);

    if (rsdp->Revision == 2)
    {
        /*
         * TODO XSDT 
         */
        klog(ERROR, "Not coded yet !\n");
        hlt();
    }

    else
    {
        klog(LOG, "Using RSDT\n");
        rsdt = (struct ACPISDTHeader *) rsdp->RsdtAddress;

        if (!rsdt_checksum(rsdt))
        {
            klog(ERROR, "RSDT table invalid !");
            hlt();
        }

        fadt = (struct FADT *) find_SDT(rsdt, "FADT");
    }

    if (fadt->SMI_CommandPort == 0 || (fadt->AcpiEnable == 0 && fadt->AcpiDisable == 0))
    {
        klog(OK, "ACPI was already enabled !\n");
        klog(WARNING, "%x", fadt->PM1aControlBlock);
    }

    else
    {
        outb(fadt->SMI_CommandPort, fadt->AcpiEnable);
        while ((inw(fadt->PM1aControlBlock) & 1) == 0);
    }

    return rsdt;
}
