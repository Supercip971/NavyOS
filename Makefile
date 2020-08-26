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
    -ffreestanding	            \
    -g			                \
    -nostdlib			

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
	qemu-system-x86_64 -s -cdrom navy.iso -serial stdio --enable-kvm

.PHONY: run-qemu
.PHONY: format 
.PHONY: all
