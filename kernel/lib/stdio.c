#include <stdio.h>
#include <terminal.h>
#include <debug.h>

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

int putch(char c){
	return kputch(c, row, column);
}

int println(const char* str){
	int i = print(str);
	i &= putch('\n');
	return i;
}

int print(const char* str){
	return printk(str, row, column);
}