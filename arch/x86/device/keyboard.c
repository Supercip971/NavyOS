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


#include "arch/x86/device/keyboard.h"
#include "arch/x86/device/ps2.h"
#include "arch/x86/io.h"

#include "kernel/log.h"

unsigned char kdbus[128] = 
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};	

bool did_twice = true;

void
keyscan()
{
    while(inb(PS2_READ) & 0x01 && (inb(PS2_READ) & 0x20) == 0x00) 
    {
        lastKey = inb(PS2_DATA);
    }
}

char
getLastKeyCode()
{
    return lastKey;
}

unsigned char 
getKeyChar()
{
   bool has_key;
   char c;

   disable_interrupts();
   has_key = lastKey < 80 && lastKey;
   enable_interrupts();

   while (!has_key)
   {
      hlt();

      disable_interrupts();
      has_key = lastKey < 80 && lastKey;
      enable_interrupts();
   }

    disable_interrupts();
    c = kdbus[lastKey];

    if(!did_twice) /* FIX ME */
    {
      lastKey = 0;
      did_twice = true;
    } 

    else 
    {
      did_twice = false;
    }

    enable_interrupts();
    return c;
}
