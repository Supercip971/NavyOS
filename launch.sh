#!/bin/bash
./build.sh
qemu-system-x86_64 -kernel ./navy.bin -serial file:debug.log
