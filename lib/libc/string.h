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

#ifndef _NAVY_LIBC_STRING_H
#define _NAVY_LIBC_STRING_H

#include <stdint.h>
#include <stddef.h>

size_t strlen(const char *);
char *strcat(char *, const char *);
char *memcpy(void *, const void *, size_t);
void *memset(void *, int, size_t);
char *strrev(char *);
int memcmp(const void *, const void *, size_t);
int strncmp(const char *, const char *, size_t);

#endif
