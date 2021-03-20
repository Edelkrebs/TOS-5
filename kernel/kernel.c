#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <terminal.h>
#include <debug.h>

void kmain(void) 
{

	init_terminal(VGA_WHITE, VGA_BLACK);
	cls();
	printregs();
	error("KERNEL PANICED!");

}