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


#include "arch/x86/vga.h"
#include "arch/x86/io.h"

uint8_t        col;
uint8_t        row;
uint8_t        default_color;

uint16_t       *vga_buffer = (uint16_t *)0xB8000;


void
term_init(void)
{

    // Init the cursor
    outb(0x3D4, 0xA);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | 2);
    //

    default_color = DEFAULT_FGCOLOR | DEFAULT_BGCOLOR << 4;
    for(col = 0; col < VGA_COL; col++) {
        for(row = 0; row < VGA_ROW; row++) {
            uint16_t index    = (VGA_COL * row) + col;
            vga_buffer[index] = ((uint16_t)default_color << 8) | ' ';
        }
    }

    col = 0;
    row = 0;
    movcur(col, row);
}


void 
term_clear(void)
{
    term_init();
}


void 
term_putc(char c, Colors fg, Colors bg)
{
    uint16_t index;
    uint8_t color = fg | bg << 4;

    switch(c) {
        case '\t':
            col += 4;
            break;
        case '\n':
            row++;
            col = 0;
            break;
        default:
            index = (VGA_COL * row) + col;
            vga_buffer[index] = ((uint16_t)color << 8) | c;
            col++;
            break;
    }

    if(col > VGA_COL) {
        col = 0;
        row++;
    }
    
    if(row > VGA_ROW) {
        term_shift();
    }

    movcur(col, row);
}


void 
term_puts(char *s, Colors fg, Colors bg)
{
    while(*s != 0) {
        term_putc(*s++, fg, bg);
    }
}


void move_cursor(uint8_t x, uint8_t y)
{
    col = x;
    row = y;

    movcur(x, y);
}


void movcur(uint8_t x, uint8_t y)
{
    uint16_t pos = (y+1) * VGA_COL + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}


void 
term_shift(void)
{
    for(row = 0; row < VGA_ROW; row++) {
        for(col = 0; col < VGA_COL; col++) {
            uint16_t current_line = (VGA_COL * row) + col;
            uint16_t next_line = (VGA_COL * (row+1)) + col;
            vga_buffer[current_line] = vga_buffer[next_line];
        }
    }

    for(col = 0; col < VGA_COL; col++) {
        uint16_t index = (VGA_COL * VGA_ROW-1) + col;
        vga_buffer[index] = ((uint16_t)default_color << 8) | ' ';
    }

    row = VGA_ROW-1;
    col = 0;
}
