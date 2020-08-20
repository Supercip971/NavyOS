CONFIG_KEYBOARD_LAYOUT?=en_us

KERNEL_SOURCES = \
	$(wildcard kernel/*.c) \
	$(wildcard arch/x86/*.c)

KERNEL_ASSEMBLY_SOURCES = \
	$(wildcard arch/*/*.asm)

KERNEL_LIBRARIES_SOURCES = \
	$(wildcard libraries/libc/*.c) \
	

KERNEL_BINARY = kernel.bin

KERNEL_OBJECTS = \
	$(patsubst %.c, $(BUILD_DIRECTORY)/%.o, $(KERNEL_SOURCES)) \
	$(patsubst %.asm, $(BUILD_DIRECTORY)/%.o, $(KERNEL_ASSEMBLY_SOURCES)) \
	$(patsubst lib/%.c, $(BUILD_DIRECTORY)/kernel/%.o, $(KERNEL_LIBRARIES_SOURCES))

OBJECTS += $(KERNEL_OBJECTS)

$(BUILD_DIRECTORY)/kernel/%.o: libraries/%.c
	$(DIRECTORY_GUARD)
	@echo [KERNEL] [CC] $<
	@$(CC) $(CFLAGS) -ffreestanding -nostdlib -c -o $@ $<

$(BUILD_DIRECTORY)/kernel/%.o: kernel/%.c
	$(DIRECTORY_GUARD)
	@echo [KERNEL] [CC] $<
	@$(CC) $(CFLAGS) -ffreestanding -nostdlib -c -o $@ $<

$(BUILD_DIRECTORY)/arch/%.o: arch/%.c
	$(DIRECTORY_GUARD)
	@echo [KERNEL] [CC] $<
	@$(CC) $(CFLAGS) -ffreestanding -nostdlib -c -o $@ $<

$(BUILD_DIRECTORY)/arch/%.o: arch/%.asm
	$(DIRECTORY_GUARD)
	@echo [KERNEL] [AS] $<
	@$(AS) $(ASFLAGS) $^ -o $@

$(KERNEL_BINARY): $(KERNEL_OBJECTS)
	$(DIRECTORY_GUARD)
	@echo [KERNEL] [LD] $(KERNEL_BINARY)
	@$(CC) $(LDFLAGS) -T arch/x86/link.ld -o $@ -ffreestanding $^ -nostdlib -lgcc
