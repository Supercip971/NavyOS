BUILD_DIRECTORY = $(shell pwd)/build

CC := i686-elf-gcc
CFLAGS := 		\
    -O0			\
    -std=c99		\
    -fno-rtti		\
    -fno-exceptions 	\
    -MD			\
    -Wall		\
    -Wextra		\
    -Werror		\
    -Ilib/libc		\
    -ffreestanding	\
    -nostdlib		

LD := i686-elf-ld
LDFLAGS :=

AS = nasm
ASFLAGS = -f elf32

include kernel/.build.mk


all:
	$(KERNEL_SOURCES)
