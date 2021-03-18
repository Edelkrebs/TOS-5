#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <terminal.h>
#include <printk.h>
#include <stdio.h>

void kmain(void) 
{

	init_terminal(VGA_WHITE, VGA_BLACK);
	printk("Hello W\norld!\0", 0, 10);	
	
}