#include <mm/pmm.h>
#include <util/maths.h>
#include <debug.h>

typedef struct{

	uint32_t size;
	uint64_t base;
	uint64_t len;
	uint32_t type;
	
}__attribute__((packed)) mmap_entry;

void bitmap_setb(uint32_t index){
	bitmap[index / 8] |= 1 << (index % 8);
}

void bitmap_clearb(uint32_t index){
	bitmap[index / 8] &= ~(1 << (index % 8));
}

uint32_t bitmap_index(uint32_t* base, uint32_t length){
	return (uint32_t)base / block_size / 8 + length / block_size / 8; 	
}

void init_bitmap(struct multiboot_info* mboot){
	
	for(int i = 0; i < mboot->mmap_length;){
		mmap_entry* entry = mboot->mmap_addr + i;
		if((uint64_t)entry->base + entry->len > UINT32_MAX){
			entry->len = (uint64_t) UINT32_MAX - entry->len; 
		}
		i += entry->size + 4;
		memory_length += entry->len;
	}	

	print("Total memory: ");
	printhex(memory_length);

	arena_addr = (void*) 0;
	block_size = 4096;
	block_limit = memory_length / block_size;
	bitmap_size = memory_length / block_size / 8;

	for(int i = 0; i < mboot->mmap_length;){
		mmap_entry* entry = mboot->mmap_addr + i;
		if(entry->type == 1 && entry->len >= bitmap_size){
			bitmap = (uint8_t*)((uint32_t)entry->base);
			break;
		} 
		i += entry->size + 4;
	}
	
}

void populate_bitmap(struct multiboot_info* mboot){

	uint32_t bmap_block_size = round_up(bitmap_size, block_size) / block_size;

	print("BMAP_BLOCK_SIZE: ");
	printhex(bmap_block_size);

	for(int i = 0; i < bitmap_size; i++){ //Empty out the entire bitmap
		bitmap[i] = 0; 
	}
	
	for(int i = 0; i < bmap_block_size; i++){ // Allocate part of the bitmap which the bitmap takes up by itself
		bitmap_setb((uint32_t)bitmap / block_size + i);
	}

	
	for(int i = 0; i < mboot->mmap_length;){ // Populate the bitmap according to the memory map
		const mmap_entry* entry = mboot->mmap_addr + i;
		if(entry->type == 1){
			i += entry->size + 4; 
			continue;
		}
		for(int j = 0; j < (uint32_t)entry->len / block_size; j++){
			bitmap_setb((uint32_t) entry->base / block_size + j);
		}
	
		i += entry->size + 4; 
	}


}