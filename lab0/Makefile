ARCH = aarch64-linux-gnu
QEMU = qemu-system-aarch64
QEMUFLAGS = -M raspi3b -display none -d in_asm
#qemu-system-aarch64 -M raspi3b -kernel kernel8.img -display none -d in_asm
all: kernel8.img

a.o: a.S
	$(ARCH)-gcc -c a.S -o a.o

kernel8.elf: a.o linker.ld
	$(ARCH)-ld -T linker.ld -o kernel8.elf a.o

kernel8.img: kernel8.elf
	$(ARCH)-objcopy -O binary kernel8.elf kernel8.img

clean:
	rm -f *.o kernel8.elf kernel8.img

qemu: kernel8.img
	$(QEMU) $(QEMUFLAGS) -kernel kernel8.img