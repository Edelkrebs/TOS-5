#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <mm/pmm.h>
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
	void* addr = pmm_alloc(1);
	printhex((uint32_t)addr);
	printhex(bitmap_getb((uint32_t)addr / block_size / 8));
	pmm_free(addr, 1);
	printhex(bitmap_getb((uint32_t)addr / block_size / 8));

	while(1);

}