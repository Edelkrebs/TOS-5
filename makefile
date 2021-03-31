ASMSOURCES := $(shell find -name *.asm)
SOURCES := $(shell find -name *.c)
OBJECTS := $(SOURCES:.c=.o) $(ASMSOURCES:.asm=.o)

ASFLAGS = -f elf32
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc
CFLAGS = -c -std=gnu99 -ffreestanding -O2 -Wall -Werror -I kernel/include -c

BIN = bin/tos-5.bin
ISO = bin/tos-5.iso
AS = nasm
CC = i686-elf-gcc

all: kernel 	
run: all
	mkdir -p log
	qemu-system-i386 -m 1G -kernel $(BIN) -d int -D log/qlog.txt -no-shutdown -no-reboot

image: all
	mkdir -p iso/boot/grub
	mkdir -p log
	cp $(BIN) iso/boot/tos-5.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) iso
	qemu-system-i386 -cdrom $(ISO) -m 1G -no-reboot -monitor stdio -d int -no-shutdown
	
kernel: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $(BIN) 

%.o:%.asm
	mkdir -p boot	
	$(AS) $(ASFLAGS) $< -o $@

%.o:%.c
	mkdir -p bin
	$(CC) $< -o $@ $(CFLAGS)

clear:
	rm -rf $(OBJECTS) $(BIN)