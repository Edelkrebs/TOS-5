#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdint.h>

uint32_t kputch(char c, uint32_t row, uint32_t column);
uint32_t printk(const char* str, uint32_t row, uint32_t column);
uint32_t printhex(uint32_t number);
uint32_t printhex64(uint64_t number);
void printreg(uint8_t reg);
void printregs();

uint32_t warn(const char* str);
uint32_t error(const char* str);

void cls();
uint32_t putch(char c);
uint32_t print(const char* str);
uint32_t println(const char* str);

#endif
