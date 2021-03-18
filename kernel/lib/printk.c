#include "../include/printk.h"
#include "../include/terminal.h"
#include <stdint.h>

static inline uint16_t* coords_to_address(uint32_t row, uint32_t column){
	return (uint16_t*) 0xb8000 + (row * width + column);
}

static inline uint16_t generate_entry(char character, uint8_t color){
	return (color << 8) | character;
}

int printk(const char* str, uint32_t row, uint32_t column){
	if(!str) return 1;

	

	return 0;
}