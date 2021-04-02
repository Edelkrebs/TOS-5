#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <mm/pmm.h>
#include <mm/vmm.h>
#include <debug.h>
#include <terminal.h>
#include <util/maths.h>
#include <cpu.h>

#define KERNEL_OFFSET 0xC0000000
#define PAGE_SIZE 4096

struct multiboot_info* multiboot;

void kmain(struct multiboot_info* mboot_info) 
{
	multiboot = mboot_info;

	init_terminal(VGA_WHITE, VGA_BLACK);
	cls();
	init_bitmap(multiboot);
	populate_bitmap(multiboot);

	init_vmm();

	/*for(int i = 0; i < round_up(kernel_size, PAGE_SIZE) / PAGE_SIZE; i++){
		map_page((void*)(KERNEL_OFFSET + i * PAGE_SIZE), (void*)((uint32_t)&_kernel_start + i * PAGE_SIZE), 0x3);
	}*/

	/*for(int i = 0; i < round_up(kernel_size, PAGE_SIZE) / PAGE_SIZE; i++){
		map_page((void*)(KERNEL_OFFSET + i * PAGE_SIZE), (void*)((uint32_t)&_kernel_start + i * PAGE_SIZE), 0x3);
	}*/

	identity_map((void*) 0, 64, 3);

	map_page((void*) 0xC0000000, (void*) 0x100000, 0x3);
	map_page((void*) 0xC0001000, (void*) 0x101000, 0x3);
	map_page((void*) 0xC0002000, (void*) 0x102000, 0x3);
	map_page((void*) 0xC0003000, (void*) 0x103000, 0x3);
	map_page((void*) 0xC0004000, (void*) 0x104000, 0x3);
	map_page((void*) 0xC0005000, (void*) 0x105000, 0x3);
	map_page((void*) 0xC0006000, (void*) 0x106000, 0x3);

	activate_paging((void*)page_directory);

	while(1);

}