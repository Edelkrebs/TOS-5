#include <stdio.h>
#include <terminal.h>
#include <printk.h>

static inline uint16_t generate_entry(char character, uint8_t color){
	return (color << 8) | character;
}

void cls(){
	for(int i = 0; i <= width * height; i++){
		*((uint16_t*) 0xb8000 + i) = generate_entry(' ', text_color_attrib);
	}
	row = 0;
	column = 0;
}

int print(const char* str){
	int i = printk(str, row, column);
	return i;
}