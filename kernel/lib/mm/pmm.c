#include <mm/pmm.h>
#include <util/maths.h>
#include <debug.h>

typedef struct{

	uint32_t size;
	uint64_t base;
	uint64_t len;
	uint32_t type;
	
}__attribute__((packed)) mmap_entry;

uint16_t number_of_entrys; 

void bitmap_setb(uint32_t index){
	bitmap[index / 8] |= 1 << (index % 8);
}

void bitmap_clearb(uint32_t index){
	bitmap[index / 8] &= ~(1 << (index % 8));
}

uint32_t bitmap_testb(uint32_t index){
	return !!(bitmap[index / 8] & (1 << (index % 8)));
}

void init_bitmap(struct multiboot_info* mboot){

	kernel_size = &_kernel_end - &_kernel_start;
	
	for(int i = 0; i < mboot->mmap_length;){
		mmap_entry* entry = mboot->mmap_addr + i;
		i += entry->size + 4;
		memory_length += entry->len;;
	}

	print("Total memory: ");
	printhex64(memory_length);
	print("Kernel start: ");
	printhex((uint32_t)&_kernel_start);
	print("Kernel end: ");
	printhex((uint32_t)&_kernel_end);
	print("Kernel size: ");
	printhex(kernel_size);

	block_size = 4096;
	block_limit = memory_length / block_size;
	bitmap_size = memory_length / block_size / 8;

	for(int i = 0; i < number_of_entrys;){
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

	for(int i = 0; i <= round_up(kernel_size, block_size) / block_size; i++){
		bitmap_setb((uint32_t)&_kernel_start / block_size + i);
	}

}

void* pmm_alloc(uint32_t size){

	assert(size == 0, "Couldnt allocate memory!");

	uint32_t blocks_to_alloc = round_up(size, block_size) / block_size;

	printhex(blocks_to_alloc);

	int count = 0;
	for(int i = 0; i < block_limit; i++){
		for(int j = 0; j < blocks_to_alloc; j++){
			if(bitmap_testb(i + j) == 0){
				count++;
				if(count == blocks_to_alloc){
					print("Did it\n");
					printhex(count);
					return (void*)((i) * block_size);
				}
			}else{
				count = 0;
				break;
			}		
		}
	}
	
	panic("Couldnt allocate memory!EEE");
																	
	return (void*) 0;	
}

void pmm_free(void* paddr, uint32_t blocks){
	for(int i = 0; i < blocks; i++){
		bitmap_clearb((uint32_t)paddr / block_size / 8 + i);
	}
}