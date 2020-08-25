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


#include <string.h>


size_t
strlen(const char *s)
{
	size_t i;

	for (i = 0; s[i] != '\0'; i++);
	return i;
}


char *
strcat(char *dst, const char *src)
{
	uint8_t length = strlen(dst);
	uint8_t i;

	for (i = 0; i < strlen(src); i++)
	{
		dst[length + i] = src[i];
	}

	dst[length + i] = '\0';
	return dst;
}

char *
memcpy(const void *dst, const void *src, size_t count)
{
	char *s = (char *) src;
	char *d = (char *) dst;

	while (count-- > 0)
	{
		*s++ = *d++;
	}

	return dst;
}

int
memcmp(const void *aptr, const void *bptr, size_t size)
{
	const unsigned char *a = (const unsigned char *) aptr;
	const unsigned char *b = (const unsigned char *) bptr;

	for (size_t i = 0; i < size; i++)
	{
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}
