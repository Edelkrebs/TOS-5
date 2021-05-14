#ifndef __MULTIBOOT_H
#define __MULTIBOOT_H

#include <stdint.h>

struct multiboot_info{
	uint32_t flags; // 0 
	uint32_t mem_lower; // 4
	uint32_t mem_upper; // 8
	uint32_t boot_device; // 12
	uint32_t cmdline; // 16
	uint32_t mods_count; // 20
	void* mods_addr; // 24
	uint32_t syms1; // 28
	uint32_t syms2; // 32
	uint32_t syms3; // 36
	uint32_t syms4; // 40
	uint32_t mmap_length; // 44
	void* mmap_addr;
	uint32_t drives_length;
	uint32_t drives_addr;
	uint32_t config_table;
	uint32_t boot_loader_name;
	uint32_t apm_table;
	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint16_t vbe_mode;
	uint16_t vbe_interface_seg;
	uint16_t vbe_interface_off;
	uint16_t vbe_interface_len;
	uint64_t framebuffer_addr;
	uint32_t framebuffer_pitch_1;
	uint32_t framebuffer_pitch_2;
	uint32_t framebuffer_pitch_3;
	uint16_t framebuffer_pitch_4;
	uint32_t framebuffer_width;
	uint32_t framebuffer_height;
	uint8_t framebuffer_bpp;
	uint8_t framebuffer_type;
	uint16_t color_info_1;
	uint16_t color_info_2;
	uint16_t color_info_3;
}__attribute__((packed)) ; 

#endif