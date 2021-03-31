#include <mm/vmm.h>
#include <mm/pmm.h>
#include <debug.h>

void init_vmm(){
	page_directory = (uint32_t*) pmm_alloc(4096);
	for(int i = 0; i < 4096 / 4; i++){ // zero out page directory
		page_directory[i] = 0;
	}
	pt_start = (uint32_t*)pmm_alloc(1024 * 4096);
	for(int i = 0; i < 1024 * 1024; i++){
		pt_start[i] = 0;
	}
}

static void create_pdentry(uint32_t index, void* ptaddr, uint16_t flags){
	page_directory[index] = ((uint32_t)ptaddr / 4096) << 12 | flags | 1;
}

void* get_paddr(void* vaddr){
	uint32_t pdindex = (uint32_t) vaddr >> 22;
	uint32_t ptindex = (uint32_t) vaddr >> 12 & 0x3FF;

	if((page_directory[pdindex] & 1) == 0){
		create_pdentry(pdindex, (void*)((uint32_t)pt_start + (4096 * pdindex + ptindex * 4)), 0x1);		
	}		

	uint32_t* pt = (uint32_t*)((uint32_t)pt_start + (pdindex * 4096));

	return (void*)((pt[ptindex] & ~0xFFF) + ((uint32_t) vaddr & 0xFFF));	
}

void map_page(void* vaddr, void* paddr, uint16_t flags){
	uint32_t pdindex = (uint32_t) vaddr >> 22;
	uint32_t ptindex = (uint32_t) vaddr >> 12 & 0x3FF;

	if((page_directory[pdindex] & 1) == 0){
		create_pdentry(pdindex, (void*)((uint32_t)pt_start + (4096 * pdindex + ptindex * 4)), 0x3);		
	}		

	uint32_t* pt = (uint32_t*)((uint32_t)pt_start + (pdindex * 4096));

	if((pt[ptindex] & 1) == 1){
		panic("Trying to allocate a page twice!");
	}

	pt[ptindex] = ((uint32_t)paddr) | (flags & 0xFFF) | 1;

}

void identity_map(void* vaddr, uint32_t number_of_pages, uint16_t flags){
	vaddr = (uint32_t*)((uint32_t)vaddr & 0xFFFFF000);
	
	uint32_t virtualaddress = (uint32_t)vaddr;
	for(int i = 0; i < number_of_pages; i++){
		map_page((void*) virtualaddress, (void*) virtualaddress, flags);
		virtualaddress += 4096;
	}
	
}