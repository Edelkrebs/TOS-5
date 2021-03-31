#ifndef __VMM_H
#define __VMM_H

#include <stdint.h>

uint32_t* page_directory;
uint32_t* pt_start;

void init_vmm();
void* get_paddr(void* vaddr);
void identity_map(void* addr, uint32_t number_of_pages, uint16_t flags);
void map_page(void* vaddr, void* paddr, uint16_t flags);
void unmap_page(void* paddr);

#endif