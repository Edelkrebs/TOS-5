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
	mov ebp, esp

	call init_gdt

	extern kmain
	call kmain

	cli
.hang:
	hlt
	jmp .hang
.end:

init_gdt:
	cli

	lgdt [gdt_attribs]

	mov eax, cr0
	or eax, 1
	mov cr0, eax

	ret

gdt:
null:
	dd 0x0
	dd 0x0
code:
	dw 0xFFFF
	dw 0
	db 0
	db 10011010b
	db 01001111b
	db 0
data:
	dw 0xFFFF
	dw 0
	db 0
	db 10010010b
	db 1001111b
	db 0
gdt_end:

gdt_attribs:
	dw gdt_end - gdt - 1
	dd gdt