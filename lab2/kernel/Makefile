ARCH = aarch64-linux-gnu
QEMU = qemu-system-aarch64
QEMUFLAGS = -M raspi3b -display none -d in_asm
QEMUFLAGS2 = -M raspi3b -display none -serial null -serial stdio

CC = $(ARCH)-gcc
LD = $(ARCH)-ld
OBJCPY = $(ARCH)-objcopy

INCLUDE = -Iinclude
CFLAGS = -g $(INCLUDE)

#dir
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

C_SOURCES = $(wildcard $(SRC_DIR)/*.c)
AS_SOURCES = $(SRC_DIR)/boot.S
LD_SOURCES = $(SRC_DIR)/linker.ld
OBJECTS = $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) $(AS_SOURCES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)

TARGET = kernel8
ELF = $(BUILD_DIR)/$(TARGET).elf
BIN = $(BUILD_DIR)/$(TARGET).img

all: BIN

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

qemu: $(BIN)
	$(QEMU) $(QEMUFLAGS) -kernel $(BIN)

run: $(BIN)
	$(QEMU) $(QEMUFLAGS2) -initrd initramfs.cpio -kernel $(BIN)

debug: $(BIN)
	$(QEMU) $(QEMUFLAGS2) -initrd initramfs.cpio -kernel $< -S -s