#ifndef __PMM_H
#define __PM_H

#include <stdint.h>
#include <multiboot.h>

typedef struct{

	uint8_t* bitmap;
	void* arena_addr;
	uint32_t block_size;
	uint32_t block_limit;
	uint32_t bitmap_size;
	
}__attribute__((packed)) bitmap_allocator;

bitmap_allocator bmap;

void bitmap_setb(uint32_t index);
void bitmap_clearb(uint32_t index);
uint32_t bitmap_index(uint32_t* base, uint32_t length);

void init_bitmap(struct multiboot_info* mboot);
void populate_bitmap(struct multiboot_info* mboot);
void* pmm_alloc(uint32_t size);
void pmm_free(void* paddr);

#endif