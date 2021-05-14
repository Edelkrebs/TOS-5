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

uint32_t printk(const char* str, uint32_t r, uint32_t col){

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

	if(column > 0) column--;
	
	return 0;
}

uint32_t kputch(char c, uint32_t r, uint32_t col){
	if(c == '\n'){
		row++;
		column = 0;
		return 0;
	}
	*(coords_to_address(r, col)) = generate_entry(c, text_color_attrib);
	column++;
	
	return 0;
}

uint32_t printhex(uint32_t number){
	char* str =  "0x00000000\0";
	uint32_t numbercpy = number;
	for(int i = 9; i > 1; i--){
		number = numbercpy;
		numbercpy = numbercpy >> 4;
		number &= 0xF;
		if(number > 9) str[i] = number + 'A' - 10;
		else str[i] = number + '0';
	}
	printk(str, row, column);
	kputch('\n', row, column);
	return 1;
}

uint32_t printhex64(uint64_t number){
	char* str =  "0x0000000000000000\0";
	uint64_t numbercpy = number;
	for(int i = 17; i > 1; i--){
		number = numbercpy;
		numbercpy = numbercpy >> 4;
		number &= 0xF;
		if(number > 9) str[i] = number + 'A' - 10;
		else str[i] = number + '0';
	}
	printk(str, row, column);
	kputch('\n', row, column);
	return 1;	
}

void printreg(uint8_t reg){
	int value = 0;
	if(reg == 0){
		asm("movl %%eax, %0;" : "=r" (value) :: "eax");
	}else if(reg == 1){
		asm("movl %%ebx, %0;" : "=r" (value) :: "ebx");
	}else if(reg == 2){
		asm("movl %%ecx, %0;" : "=r" (value) :: "ecx");
	}else{
		asm("movl %%edx, %0;" : "=r" (value) :: "edx");
	}

	printhex(value);
}

void printregs(){
	printk("----Registers----\n", row, column);
	printk("EAX: ", row, column);
	printreg(0);
	printk("EBX: ", row, column);
	printreg(1);
	printk("ECX: ", row, column);
	printreg(2);
	printk("EDX: ", row, column);
	printreg(3);
}


uint32_t putch(char c){
	return kputch(c, row, column);
}

uint32_t println(const char* str){
	int i = printk(str, row, column);
	i &= kputch('\n', row, column);
	return i;
}

uint32_t print(const char* str){
	return printk(str, row, column);
}

uint32_t warn(const char* str){
	uint32_t t_color = text_color;
	set_text_color(VGA_LIGHT_CYAN);
	int i = printk("[WARNING] ", row, column);
	set_text_color(t_color);
	int j = printk(str, row, column);
	return i & j;
}

uint32_t error(const char* str){
	uint32_t t_color = text_color;
	set_text_color(VGA_RED);
	int i = printk("[ERROR] ", row, column);
	set_text_color(VGA_LIGHT_RED);
	int j = printk(str, row, column);
	set_text_color(t_color);
	return i & j;
}

void panic(const char* message){
	error("KERNEL PANICED! With message: ");
	set_text_color(VGA_RED);
	println(message);
	set_text_color(VGA_WHITE);

	while(1);
}

void cls(){
	for(int i = 0; i <= width * height; i++){
		*((uint16_t*) 0xb8000 + i) = generate_entry(' ', text_color_attrib);
	}
	row = 0;
	column = 0;
}
