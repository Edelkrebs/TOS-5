ASMSOURCES := $(shell find -name *.asm)
SOURCES := $(shell find -name *.c)
OBJECTS := $(SOURCES:.c=.o) $(ASMSOURCES:.asm=.o)

ASFLAGS = -f elf32
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc
CFLAGS = -c -std=gnu99 -ffreestanding -O2 -Wall -Werror -I kernel/include -c

AS = nasm
CC = i686-elf-gcc

all: kernel 	
run: all
	qemu-system-i386 -kernel bin/tos-5.bin -d int -D qlog.txt

image: all
	mkdir -p iso/boot/grub
	cp bin/tos-5.bin iso/boot/tos-5.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o bin/tos-5.iso iso
	qemu-system-i386 -cdrom bin/tos-5.iso -d int -D qlogimg.txt
	
kernel: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o bin/tos-5.bin 

%.o:%.asm
	mkdir -p boot	
	$(AS) $(ASFLAGS) $< -o $@

%.o:%.c
	mkdir -p bin
	$(CC) $< -o $@ $(CFLAGS)


