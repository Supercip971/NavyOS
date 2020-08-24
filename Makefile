.SUFFIXES:
.DEFAULT_GOAL := all

BUILD_DIRECTORY = $(shell pwd)/build
DIRECTORY_GUARD=@mkdir -p $(@D)

CC := i686-elf-gcc
CFLAGS := 		\
    -O0			\
    -fno-exceptions 	\
    -fno-omit-frame-pointer \
    -MD			\
    -Wall		\
    -Wextra		\
    -Werror		\
    -I. \
    -Ilib/libc		\
    -ffreestanding	\
    -g			\
    -nostdlib		

LD := i686-elf-ld
LDFLAGS :=

AS = nasm
ASFLAGS = -f elf32

include kernel/.build.mk

.PHONY: all
all: $(KERNEL_BINARY) 

.PHONY: run-qemu
run-qemu: 
	qemu-system-x86_64 -s -kernel kernel.bin -serial stdio 
