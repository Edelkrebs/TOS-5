#ifndef __PMM_H
#define __PMM_H

#include <stdint.h>
#include <multiboot.h>

extern uint8_t _kernel_start;
extern uint8_t _kernel_end;

uint8_t* bitmap;
uint32_t block_size;
uint32_t block_limit;
uint32_t bitmap_size;
	
uint64_t memory_length;
uint32_t kernel_size;

void bitmap_setb(uint32_t index);
void bitmap_clearb(uint32_t index);
uint32_t bitmap_testb(uint32_t index);

void init_bitmap(struct multiboot_info* mboot);
void populate_bitmap(struct multiboot_info* mboot);
void* pmm_alloc(uint32_t size);
void pmm_free(void* paddr, uint32_t length);

#endif