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
    -I. \
    -Ilib/multiboot \
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

.PHONY: format 
format:
	indent -bad -bap -bl -blf -bli0 -bbo -i4 -l79 -lp -ppi1 -psl -c33 -cd33 -cdb -nce -cli1 -cp33  -fc1 -fca -npcs -nprs -saf -sai -saw -sc -ts4 -nsob -nss */*/*.c

.PHONY: run-qemu
run-qemu: 
	qemu-system-x86_64 -s -kernel kernel.bin -serial stdio --enable-kvm
