# Toolchain
CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy
QEMU = qemu-system-aarch64

# Project structure
SRC_DIR = .
BUILD_DIR = build

# Source files (from your screenshot)
C_SOURCES = \
    $(SRC_DIR)/boot.c \
    $(SRC_DIR)/gpio.c \
    $(SRC_DIR)/main.c \
    $(SRC_DIR)/uart.c

ASM_SOURCES = $(SRC_DIR)/start.S

HEADERS = \
    $(SRC_DIR)/boot.h \
    $(SRC_DIR)/gpio.h \
    $(SRC_DIR)/peripherals.h \
    $(SRC_DIR)/type.h \
    $(SRC_DIR)/uart.h

# Output files
TARGET = bootloader
ELF = $(BUILD_DIR)/$(TARGET).elf
BIN = $(BUILD_DIR)/$(TARGET).img

# Compiler/linker flags
CFLAGS = \
    -Wall \
    -nostdlib \
    -nostartfiles \
    -ffreestanding \
    -mgeneral-regs-only \
    -I$(SRC_DIR) \
		-g

LDFLAGS = -T $(SRC_DIR)/linker.ld
ASFLAGS = $(CFLAGS)

# QEMU settings
QEMU_FLAGS = \
    -machine raspi3b \
    -serial null \
    -serial pty

all: $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

$(ELF): $(ASM_SOURCES) $(C_SOURCES) $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(ASFLAGS) $(LDFLAGS) $(ASM_SOURCES) $(C_SOURCES) -o $@

run: $(BIN)
	$(QEMU) $(QEMU_FLAGS) -kernel $(BIN)

debug: $(BIN)
	$(QEMU) $(QEMU_FLAGS) -kernel $(BIN) -S -gdb tcp::1234

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run debug