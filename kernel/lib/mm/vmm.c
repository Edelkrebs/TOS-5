#include <mm/vmm.h>
#include <mm/pmm.h>
#include <debug.h>

void init_vmm(){
	for(int i = 0; i < 4096 / sizeof(page_directory); i++){
		page_directory[i] = 0;
	}
}

static void create_pdentry(uint32_t index, void* ptaddr, uint16_t flags){
	page_directory[index] = (uint32_t)(((uint32_t)ptaddr << 11) | flags);
}

void* vaddr_to_paddr(void* vaddr){
	return (void*) 0;
}

void map_page(void* vaddr, void* paddr, uint16_t flags){
	uint32_t pd_index = (uint32_t) vaddr >> 22;
	uint32_t pt_index = (uint32_t) vaddr >> 12 & 0x03FF;

	if(!(page_directory[pd_index] & 0x1)){
		create_pdentry(pd_index, (void*)((uint32_t)pmm_alloc(4096) / 4096), 0x1);
	}

	uint32_t* pt = (uint32_t*) ((page_directory[pd_index] >> 12) * 4096);

	if(!(pt[pt_index] & 0x1)){
		return;	
	}

	pt[pt_index] = ((uint32_t) ((uint32_t)paddr / 4096) << 12) | (flags & 0xFFF) | 0x1;  
}