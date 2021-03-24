#include <mm/pmm.h>
#include <debug.h>
#include <stddef.h>

typedef struct{

	uint32_t size;
	uint64_t base;
	uint64_t len;
	uint32_t type;
	
}__attribute__((packed)) mmap_entry;

void bitmap_setb(uint32_t index){
	bmap.bitmap[index >> 3] |= 1 << (index % 8);
}

void bitmap_clearb(uint32_t index){
	bmap.bitmap[index >> 3] &= ~(1 << (index % 8));
}

uint32_t bitmap_index(uint32_t* base, uint32_t length){
	return (uint32_t)base / bmap.block_size / 8 + length / bmap.block_size / 8; 	
}

void init_bitmap(struct multiboot_info* mboot){

	uint32_t mem_size = 0;
	
	for(int i = 0; i < mboot->mmap_length;){
		const mmap_entry* entry = mboot->mmap_addr + i;
		i += entry->size + 4;
		mem_size += entry->len;
	}	

	print("Total memory: ");
	printhex(mem_size);

	bmap.arena_addr = (void*) 0;
	bmap.block_size = 4096;
	bmap.block_limit = mem_size / bmap.block_size;
	bmap.bitmap_size = mem_size / bmap.block_size / 8;

	for(int i = 0; i < mboot->mmap_length;){
		const mmap_entry* entry = mboot->mmap_addr + i;
		if(entry->type == 1 && entry->len >= bmap.bitmap_size){
			bmap.bitmap = (uint8_t*)((uint32_t)entry->base);
			break;
		} 
		i += entry->size + 4;
	}
	
}

void populate_bitmap(struct multiboot_info* mboot){

	bmap.bitmap = (uint8_t*)0x9FC00;

	__attribute__((unused)) uint32_t bmap_block_size = (uint32_t)bmap.bitmap / 4096 / 8 + bmap.bitmap_size / 4096 / 8;

	for(int i = 0; i < bmap.bitmap_size; i++){
		bmap.bitmap[i] = 0;
	}

	for(int i = 0; i <= bmap_block_size; i++){
		bitmap_setb((uint32_t)bmap.bitmap / 4096 / 8 + i);
	}

	for(int i = 0; i < mboot->mmap_length;){
		const mmap_entry* entry = mboot->mmap_addr + i;
		i += entry->size + 4;
	}
}