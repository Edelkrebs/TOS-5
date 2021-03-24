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
	bmap->bitmap_addr[index >> 3] |= 1 << (index % 8);
}

void bitmap_clearb(uint32_t index){
	bmap->bitmap_addr[index >> 3] &= ~(1 << (index % 8));
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

	

}