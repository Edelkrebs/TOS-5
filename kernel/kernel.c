#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

void kmain(void) 
{

	uint8_t c = 'E';
	uint8_t bg = 0x0F;
	uint16_t* mem = (uint16_t*) 0xb8000;

	uint16_t entry = (bg << 8) | c;

	*mem = entry;

}