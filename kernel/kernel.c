#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <terminal.h>
#include <debug.h>
#include <multiboot.h>
#include <pmm.h>

struct multiboot_info* multiboot;

void kmain(struct multiboot_info* mboot_info) 
{

	multiboot = mboot_info;

	init_bitmap
	init_terminal(VGA_WHITE, VGA_BLACK);
	cls();
	printregs();
	
	while(1);

}