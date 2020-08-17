LIBC_SOURCES = $(wildcard lib/libc/*.c)
LIBC_OBJECTS = $(patsubst %.c, $(BUILD_DIRECTORY)/%.o, $(LIBC_SOURCES))

$(BUILD_DIRECTORY)/libc/%.o: libc/%.c
	$(DIRECTORY_GUARD)
	@echo [LIBC] [CC] $<
	@$(CC) $(CFLAGS) -ffreestanding -nostdlib -c -o $@ $<

