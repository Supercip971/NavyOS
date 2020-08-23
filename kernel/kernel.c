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


#include "kernel/warning.h"
#include "kernel/log.h"
#include "arch/arch.h"

#include <macro.h>
#include <stdlib.h>
#include <math.h>

void
kmain(void)
{
    init_arch();
    klog(LOG, "Navy started");

    uint8_t a = 0;
    uint8_t b = 6;
    //uint8_t b = 8 / a;

    char *c = "Hello";
    char *d = "World";

    klog(LOG, "%d & %d", a, b);
    klog(LOG, "%s %s", c, d);

    __unused(b);

    while(1);
}

