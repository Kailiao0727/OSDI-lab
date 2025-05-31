ARCH = aarch64-linux-gnu
QEMU = qemu-system-aarch64
QEMUFLAGS = -machine raspi3b -display none -serial null -serial pty
QEMUFLAGS2 = -M raspi3b -display none -serial null -serial stdio

CC = $(ARCH)-gcc
LD = $(ARCH)-ld
OBJCPY = $(ARCH)-objcopy

INCLUDE = -Iinclude
CFLAGS = \
    -Wall \
    -nostdlib \
    -nostartfiles \
    -ffreestanding \
    -mgeneral-regs-only \
    -g \
    $(INCLUDE)

#dir
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
AS_SOURCES = $(SRC_DIR)/start.S
LD_SOURCES = $(SRC_DIR)/linker.ld
OBJECTS = $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) $(AS_SOURCES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)

TARGET = bootloader
ELF = $(BUILD_DIR)/$(TARGET).elf
BIN = $(BUILD_DIR)/$(TARGET).img

all: $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ELF): $(OBJECTS) $(LD_SOURCES)
	$(LD) -T $(LD_SOURCES) -o $@ $(OBJECTS)

$(BIN): $(ELF)
	$(OBJCPY) -O binary $< $@

clean:
	rm -rf $(BUILD_DIR) $(ELF) $(BIN)

run: $(BIN)
	$(QEMU) $(QEMUFLAGS) -kernel $(BIN)

qemu: $(BIN)
	$(QEMU) $(QEMUFLAGS2) -kernel $(BIN)

kernel: kernel8.img
	$(QEMU) $(QEMUFLAGS) -kernel kernel8.img

debug: $(BIN)
	$(QEMU) $(QEMUFLAGS2) -kernel $< -S -s