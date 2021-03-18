ASMSOURCES := $(shell find -name *.asm)
SOURCES := $(shell find -name *.c)
OBJECTS := $(SOURCES:.c=.o) $(ASMSOURCES:.asm=.o)

ASFLAGS = -f elf32
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc
CFLAGS = -c -std=gnu99 -ffreestanding -O2 -Wall -Werror -c

AS = nasm
CC = i686-elf-gcc

all: kernel 

run: all
	qemu-system-i386 -kernel bin/tos-5.bin -d int

	
kernel: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o bin/tos-5.bin 

%.o:%.asm
	$(AS) $(ASFLAGS) $< -o $@

%.o:%.c
	$(CC) $< -o $@ $(CFLAGS)


