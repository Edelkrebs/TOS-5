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
	qemu-system-i386 -kernel $(BIN) -d int -D qlog.txt

image: all
	mkdir -p iso/boot/grub
	cp $(BIN) iso/boot/tos-5.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO) iso
	qemu-system-i386 -cdrom $(ISO) -d int -D qlogimg.txt
	
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