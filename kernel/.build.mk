KERNELS_SOURCES = \
    $(wildcard kernel/*.c) \
    $(wildcard arch/x86/*.c)

KERNEL_ASSEMBLY = \
    $(wildcard arch/x86/*.asm)

KERNEL_BINARY = kernel.bin

KERNEL_OBJECTS = \
		 $(patsubst %.c, $(BUILD_DIRECTORY)/%.o, $(KERNEL_SOURCES)) \
		 $(patsubst %.asm, $(BUILD_DIRECTORY)/%.o, $(KERNEL_ASSEMBLY_SOURCES))

OBJECTS += $(KERNEL_OBJECTS)

$(BUILD_DIRECTORY)/kernel/%.o: kernel/%.c
	$(DIRECTORY_GUARD)
	@echo [KERNEL] [CC] $<
	@$(CC) $(CFLAGS) -nostdlib -ffreestanding -c -o $@ $<


$(BUILD_DIRECTORY)/arch/%.o: arch/%.c
	$(DIRECTORY_GUARD)
	@echo [KERNEL] [CC] $<
	@$(CC) $(CFLAGS) -nostdlib -ffreestanding -c -o $@ $<

$(BUILD_DIRECTORY)/arch/%.asm: arch/%.asm
	$(DIRECTORY_GUARD)
	@echo [KERNEL] [AS] $<
	@$(AS) $(ASFLAGS) $^ -o $@

$(KERNEL_BINARY): $(KERNEL_OBJECTS)
	@$(DIRECTORY_GUARD)
	@echo [KERNEL] [LD] $(KERNEL_BINARY)
	@$(CC) $(LDFLAGS) -T arch/x86/link.ld -o $@ -ffreestanding $^ -nostdlib -lgcc
