#ifndef __VMM_H
#define __VMM_H

#include <stdint.h>

uint32_t* page_directory;

void init_vmm();

void map_page(void* vaddr, void* paddr, uint16_t flags);
void unmap_page(void* vaddr);

#endif