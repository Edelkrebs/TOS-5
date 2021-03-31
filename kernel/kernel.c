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
	identity_map((void*) 0, 63, 3);

	for(int i = 0; i < kernel_size / 4096; i++){
		map_page((void*)(0xC0000000 + i * 4096), (void*)(0x100000 + i * 4096), 0x3);
	}

	activate_paging((void*)page_directory);

	printhex(0x000);

	while(1);

}