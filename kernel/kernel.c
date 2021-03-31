#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <mm/pmm.h>
#include <mm/vmm.h>
#include <debug.h>
#include <terminal.h>
#include <util/maths.h>

struct multiboot_info* multiboot;

void kmain(struct multiboot_info* mboot_info) 
{
	multiboot = mboot_info;

	init_terminal(VGA_WHITE, VGA_BLACK);
	cls();
	init_bitmap(multiboot);
	populate_bitmap(multiboot);

	init_vmm();
	identity_map((void*) 0, 64, 3);

	printhex((uint32_t)get_paddr((uint32_t*) 0x10000));	
	
	while(1);

}