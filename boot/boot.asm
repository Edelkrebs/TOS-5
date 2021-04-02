MBALIGN equ 1 << 0
MEMINFO equ 1 << 1
FLAGS equ MBALIGN | MEMINFO
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM


section .bss
align 16
stack_bottom:
resb 16384
stack_top:


section .text
global _start:function (_start.end - _start)
_start:

	mov esp, stack_top

	cli
	
	mov eax, cr0
	or eax, 1
	mov cr0, eax

	lgdt [gdt_attribs - 0xC0000000]

	jmp 0x8:_start.pm - 0xC0000000
.pm:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

;	lea eax, [page_directory - 0xC0000000]
;	mov cr3, eax

;	mov eax, cr0
;	or eax, 0x80010001
;	mov cr0, eax

;	push ebx
;	extern kmain
;	call kmain

.hang:
	hlt
	jmp .hang
.end:

gdt:
null:
	dd 0
	dd 0
code:
	dw 0xFFFF
	dw 0
	db 0
	db 10011010b
	db 11001111b
	db 0
data:
	dw 0xFFFF
	dw 0
	db 0
	db 10010010b
	db 11001111b
	db 0
gdt_end:

gdt_attribs:
	dw gdt_end - 0xC0000000 - gdt - 0xC0000000 - 1
	dd gdt - 0xC0000000

page_directory: 
	times 1024 dd 0

	