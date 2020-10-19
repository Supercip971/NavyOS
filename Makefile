.SUFFIXES:
.DEFAULT_GOAL := all

BUILD_DIRECTORY = $(shell pwd)/build

DIRECTORY_GUARD=@mkdir -p $(@D)

CC := i686-elf-gcc
CFLAGS := \
    -O0 \
    -fno-exceptions 	        \
    -fno-omit-frame-pointer     \
    -MD			                \
    -Wall		                \
    -Wextra		                \
    -Werror                     \
    -I.                         \
    -Ilib/multiboot             \
    -Ilib/libc		            \
	-Ilib						\
    -ffreestanding	            \
    -g			                \
    -nostdlib			        \
    -ansi                       \
    -pedantic                   \
    -pedantic-errors            \

LD := i686-elf-ld
LDFLAGS :=

AS = nasm
ASFLAGS = -f elf32

include kernel/.build.mk

all: $(KERNEL_BINARY) 

format:
	sh ./format.sh
	

run-qemu: 
	sh ./make-iso.sh
	qemu-system-i386 -cdrom navy.iso -serial stdio -smp cores=4 

run-gdb:
	sh ./make-iso.sh
	qemu-system-i386 -s -S -cdrom navy.iso -serial stdio -smp cores=4 

run-debug:
	sh ./make-iso.sh
	qemu-system-i386 -cdrom navy.iso -serial stdio -smp cores=4 --no-shutdown --no-reboot

run-bochs:
	sh ./make-iso.sh
	bochs -q

clean:
	rm -rf build/

.PHONY: run-bochs
.PHONY: run-qemu
.PHONY: run-gdb
.PHONY: format 
.PHONY: all
.PHONY: clean
