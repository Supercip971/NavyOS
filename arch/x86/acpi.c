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
#include "arch/x86/rsdt.h"
#include "arch/x86/io.h"
#include "kernel/log.h"

#include <multiboot2.h>


void 
init_acpi(uint32_t addr)
{
    struct multiboot_tag_old_acpi *acpi =
        (struct multiboot_tag_old_acpi *) get_tag(MULTIBOOT_TAG_TYPE_ACPI_OLD, addr);

    klog(OK, "RSDP found on 0x%x\n", acpi->rsdp);
    struct RSDPDescriptor *rsdp = (struct RSDPDescriptor *) acpi->rsdp;
    struct FADT *fadt;

    klog(LOG, "ACPI Revision number %d\n", rsdp->Revision);

    if (rsdp->Revision == 2)
    {
        // TODO XSDT
        klog(ERROR, "Not coded yet !\n");
        hlt();
    }

    else
    {
        klog(LOG, "Using RSDT\n");
        struct ACPISDTHeader *rsdt = (struct ACPISDTHeader *) rsdp->RsdtAddress;

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
        klog(LOG, "ACPI enabled\n");
    }

}
