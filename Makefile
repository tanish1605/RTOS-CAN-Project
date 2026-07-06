TARGET = firmware

CC = arm-none-eabi-gcc

AS = arm-none-eabi-gcc

OBJCOPY = arm-none-eabi-objcopy

CPU = -mcpu=cortex-m3 -mthumb

CFLAGS = $(CPU) -Wall -O0 -g -Iinclude

LDFLAGS = -T linker.ld -nostdlib

C_SOURCES = $(wildcard src/*.c) \
            $(wildcard drivers/*.c)

ASM_SOURCES = $(wildcard arch/*.s)

BUILD_DIR = build

C_OBJECTS = \
    $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(wildcard src/*.c)) \
    $(patsubst drivers/%.c,$(BUILD_DIR)/%.o,$(wildcard drivers/*.c)) \
	$(patsubst kernel/%.c,$(BUILD_DIR)/%.o,$(wildcard kernel/*.c))

ASM_OBJECTS = $(patsubst arch/%.s,$(BUILD_DIR)/%.o,$(ASM_SOURCES))

OBJECTS = $(C_OBJECTS) $(ASM_OBJECTS)

all: $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: arch/%.s
	@mkdir -p $(BUILD_DIR)
	$(AS) $(CPU) -c $< -o $@

$(BUILD_DIR)/%.o: drivers/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: kernel/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(CPU) $(OBJECTS) $(LDFLAGS) -o $@

clean:
	rm -rf build
	