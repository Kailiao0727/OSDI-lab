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
OBJECTS = $(C_SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o) $(AS_SOURCES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.o)

all: kernel8.img

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.S | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

kernel8.elf: $(OBJECTS) linker.ld
	$(LD) -T linker.ld -o $@ $(OBJECTS)

kernel8.img: kernel8.elf
	$(OBJCPY) -O binary $< $@

clean:
	rm -rf $(BUILD_DIR) kernel8.elf kernel8.img

qemu: kernel8.img
	$(QEMU) $(QEMUFLAGS) -kernel kernel8.img

qemu-uart: kernel8.img
	$(QEMU) $(QEMUFLAGS2) -kernel kernel8.img

debug: kernel8.img
	$(QEMU) $(QEMUFLAGS2) -kernel $< -S -s