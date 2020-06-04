#!/bin/sh
# Copyright (C) 2020 Jordan DALCQ & contributors
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

if [ -d "obj" ]; then
    echo "[+] Object cleaned !"
    rm -rf obj
fi

out=$(ls)

mkdir obj

for DIR in $out; do
    if [ -d $DIR ]; then
        (cd $DIR && DESTDIR="../obj" make)
    fi
done

i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld obj/*.o -o navy.bin -lgcc
