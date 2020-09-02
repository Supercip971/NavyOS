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

#ifndef NAVY_ARCH_H
#define NAVY_ARCH_H

#include <stdint.h>

void debug_print(const char *);
void debug_putc(const char);
void debug_clear(void);
void vga_print(const char *);
void vga_printerr(const char *);
void init_arch(uint32_t);
void breakpoint(void);
void hlt(void);


#endif
