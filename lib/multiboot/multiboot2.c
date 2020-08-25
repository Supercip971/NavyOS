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

#include <multiboot2.h>
#include <stdint.h>

struct multiboot_tag *
get_tag(uint32_t type, uint32_t addr)
{
	struct multiboot_tag *tag = (struct multiboot_tag *) addr + 8;

	while (tag->type != MULTIBOOT_TAG_TYPE_END)
	{
		if (tag->type == type)
		{
			return tag;
		}

		tag =
			(struct multiboot_tag *) ((uint8_t *) tag +
									  ((tag->size + 7) & ~7));
	}

	return MULTIBOOT_HEADER_TAG_END;
}
