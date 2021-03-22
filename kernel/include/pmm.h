#ifndef __PMM_H
#define __PMM_H

#include <stdint.h>
#include <multiboot.h>

typedef struct{

	void* bitmap_addr;
	void* arena_addr;
	uint32_t block_size;
	uint32_t block_limit;
	
}__attribute__((packed)) bitmap;

void bitmap_set(struct bitmap* bmap, uint32_t index);
void bitmap_unset(struct bitmap* bmap, uint32_t index);

void init_bitmap(bitmap* bmap, struct multiboot_info* mboot);
void* pmm_alloc(uint32_t size);
void pmm_free(void* paddr);

#endif