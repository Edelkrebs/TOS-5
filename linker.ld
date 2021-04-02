ENTRY(_start)

SECTIONS{

	. = 0xC0100000;

	_kernel_start = .;

	.text : AT(ADDR(.text) - 0xC0000000){
		*(.multiboot)
		*(.text)
	}

	.rodata : AT(ADDR(.rodata) - 0xC0000000){
		*(.rodata)
	}

	.data : AT(ADDR(.data) - 0xC0000000){
		*(.data)
	}

	.bss : AT(ADDR(.bss) - 0xC0000000){
		*(COMMON)
		*(.bss)
	}

	_kernel_end = .;
	
}