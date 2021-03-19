#include <printk.h>
#include <terminal.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

static inline uint16_t* coords_to_address(uint32_t row, uint32_t column){
	return (uint16_t*) 0xb8000 + (row * height + column);
}

static inline uint16_t generate_entry(char character, uint8_t color){
	return (color << 8) | character;
}

int printk(const char* str, uint32_t r, uint32_t col){

	if(!str) return 1;

	row = r;
	column = col;
	for(size_t i = 0; i <= strlen(str); i++){
		if(str[i] == '\n'){
			i++;
			row++;
			column = 0;
			continue;
		}
		*(coords_to_address(row, column)) = generate_entry(str[i], text_color_attrib);
		column++;
	}
	
	return 0;
}